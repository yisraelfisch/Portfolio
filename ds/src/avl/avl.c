/*************************************** 
file name: avl.h
Author: yisrael fisch
*reviewer: sara
******************************************/

#include <stdlib.h> /*malloc, free*/
#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/
#include "avl.h"

typedef struct avl_node
{
    size_t height;
    void *data;
    struct avl_node *child[2];/*0 - left, 1- right*/
}avl_node_t;

struct avl
{
    struct avl_node* root;
    avl_compare_func_t compare_func;
    void *user_param;
};



static avl_node_t *RecursiveFind(avl_t *avl, avl_node_t *root, void *data);
static void RecursiveRemove(avl_t *avl, avl_node_t *node, void *data);
static int RecursiveForEach(avl_node_t *node, avl_action_func_t action_func, void *param, int result);
static void RecursiveUpdateHeight(avl_t *avl, avl_node_t *node, const void *data);
static void RecursiveDestroy(avl_node_t *node);
static size_t RecursiveSize(avl_node_t *curr);

static avl_node_t *CreateNode(void);
static void RemoveNode(avl_node_t *node);
static int CompareData(avl_t *avl, avl_node_t *node, const void *data);
static int FindIndex(avl_t *avl, avl_node_t *node, const void *data);

static int NodeHeight(avl_node_t *node);
static void UpdateNodeHeight(avl_node_t *node);
static int MaxHeightOfChildren(avl_node_t *node);
static size_t Max2(size_t a, size_t b);

static int GetBalanceFactor(avl_node_t *node);
static void AvlBalance(avl_t *avl, avl_node_t *node);
static void RotateOnce(avl_t *avl, avl_node_t *node, int index);
static void RotateTwice(avl_t *avl, avl_node_t *node, int index);

static void RemoveLeaf(avl_t *avl, avl_node_t *node, void *data);
static void RemoveNodeOneChild(avl_t *avl, avl_node_t *node, void *data);
static void RemoveNodeTwoChilds(avl_t *avl, avl_node_t *node, void *data);
static int NumOfChildren(avl_node_t *node);
static avl_node_t *AvlFindParentRecur(avl_t *avl, avl_node_t *root, void *data);
static avl_node_t *AvlFindLeftSuccessorRecur(avl_node_t *node);

typedef void (avl_remove_func_t)(avl_t *avl, avl_node_t *node, void *data);
avl_remove_func_t *g_remove_funcs_array[] = {RemoveLeaf,
                        RemoveNodeOneChild,
                        RemoveNodeTwoChilds};


avl_t *AvlCreate(avl_compare_func_t compare_func, void *user_param) 
{
    avl_t *avl = NULL;
    
    assert(compare_func);

    
    avl = (avl_t *)malloc(sizeof(avl_t));
    if(!avl)
    {
        return NULL;
    }
    avl->root = NULL;
    avl->compare_func = compare_func;
    avl->user_param = user_param;
    
    return avl;
}

void AvlDestroy(avl_t *avl)
{
    assert(avl);

    RecursiveDestroy(avl->root);

    free(avl);
    avl = NULL;
}

static void RecursiveDestroy(avl_node_t *node)
{
    if (NULL == node)
    {
        return;     
    }
    
    RecursiveDestroy(node->child[0]);
    RecursiveDestroy(node->child[1]);

    free(node);
    node = NULL;
}

size_t AvlSize(avl_t *avl)
{

        assert(avl);
    return RecursiveSize(avl->root);
}

static size_t RecursiveSize(avl_node_t *curr)
{
    if(!curr)
    {
        return 0;
    }

    return 1 + RecursiveSize(curr->child[0])
             + RecursiveSize(curr->child[1]);

}

int AvlIsEmpty(avl_t *avl)
{
    return avl->root == NULL;
}

int AvlInsert(avl_t *avl, const void *data)
{
    avl_node_t *parent = NULL, *new_node = NULL;
    assert(avl);
    assert(data);

    new_node = CreateNode();
    if(!new_node)
    {
        return 1;
    }

    if(AvlIsEmpty(avl))
    {
        new_node->data = (void *)data;
        avl->root = new_node;
        return 0;
    }

    
    parent = RecursiveFind(avl, avl->root, (void *)data);
    
    
    if(0 == CompareData(avl, parent, data))
    {
        free(new_node);
        new_node = NULL;
        return 1;
    }

    parent->child[FindIndex(avl, parent, data)] = new_node;
    new_node->data = (void *)data;

    RecursiveUpdateHeight(avl, avl->root, data);
    

    return 0;
}

static avl_node_t *RecursiveFind(avl_t *avl, avl_node_t *root, void *data)
{

    if((0 == CompareData(avl, root, data)) || (0 != CompareData(avl, root, data) &&
                    NULL == root->child[FindIndex(avl, root, data)]))
    {
        return root;
    }
    
    return RecursiveFind(avl, root->child[FindIndex(avl, root, data)], data);
}

void AvlRemove(avl_t *avl, void *data)
{
    avl_node_t *node = NULL;
    assert(avl);
    assert(data);
    
    node = RecursiveFind(avl, avl->root, data);

    /* if data is not found in the tree, do nothing */
    if(0 != CompareData(avl, node, data))
    {
        return;
    }

    RecursiveRemove(avl, node, data);

}

static void RecursiveRemove(avl_t *avl, avl_node_t *node, void *data)
{
    g_remove_funcs_array[NumOfChildren(node)](avl, node, data);
}

void *AvlFind(avl_t *avl, const void *data)
{
    avl_node_t *node = NULL;
    assert(avl);
    assert(data);

    node = RecursiveFind(avl, avl->root, (void *)data);
    
    if(0 == CompareData(avl, node, data))
    {
        return node->data;
    }

    return NULL;

}

int AvlForEach(avl_t *avl, avl_action_func_t action_func, void *param)
{
    avl_node_t *node = avl->root;
    int result = 0;

    assert(avl);
    assert(action_func);

    if (NULL == node)
    {
        return 0;
    }

    return RecursiveForEach(node, action_func, param, result);
}

static int RecursiveForEach(avl_node_t *node, avl_action_func_t action_func, void *param, int result)
{   
    if (NULL == node)
    {
        return 0;
    }

    if(result)
    {
        return result;
    }    
    
    result = RecursiveForEach(node->child[0], action_func, param, result);

    result = action_func(node->data, param);
    
    result = RecursiveForEach(node->child[1], action_func, param, result);

    return result;
}

size_t AvlHeight(const avl_t *avl)
{
    assert(avl);
    
    return avl->root->height;
}

static avl_node_t *CreateNode(void)
{
    avl_node_t *node = NULL;

    node = (avl_node_t *)malloc(sizeof(avl_node_t));
    if(!node)
    {
        return NULL;
    }

    node->data = NULL;
    node->child[0] = NULL;
    node->child[1] = NULL;
    node->height = 0;

    return node;
}

static void RemoveNode(avl_node_t *node)
{

    node->data = NULL;
    node->child[0] = NULL;
    node->child[1] = NULL;
    node->height = 0;

    free(node);
    node = NULL;
}

static int CompareData(avl_t *avl, avl_node_t *node, const void *data)
{
    return (avl->compare_func(node->data, data, avl->user_param));
}

static int FindIndex(avl_t *avl, avl_node_t *node, const void *data)
{
    return ((avl->compare_func(node->data, data, avl->user_param)) > 0);
}

static void RecursiveUpdateHeight(avl_t *avl, avl_node_t *node, const void *data)
{
    if(!node)   
    {
        return;
    }
    
    if(0 == CompareData(avl, node, data))
    {
        UpdateNodeHeight(node);
        return;
    }

    RecursiveUpdateHeight(avl, node->child[FindIndex(avl,node,data)], data);

    if(2 == GetBalanceFactor(node) || -2 == GetBalanceFactor(node))
    {
        AvlBalance(avl, node);  
    }
    
    UpdateNodeHeight(node);
}

static void UpdateNodeHeight(avl_node_t *node)
{
    node->height = 1 + MaxHeightOfChildren(node);
}

static int GetBalanceFactor(avl_node_t *node)
{

    if (!node)
    {
        return 0;
    }

    return NodeHeight(node->child[0]) - NodeHeight(node->child[1]);
}


static int NodeHeight(avl_node_t *node)
{
    if (!node) 
    {
        return -1;
    }

    return node->height;
}

static size_t Max2(size_t a, size_t b)
{
    return (a > b ? a : b);
}

static int MaxHeightOfChildren(avl_node_t *node)
{
    
    if(node->child[0] && node->child[1])
    {
        
        return Max2(NodeHeight(node->child[0]), NodeHeight(node->child[1]));
    }

    if(node->child[0] && !node->child[1])
    {
        return node->child[0]->height;
    }

    if(!node->child[0] && node->child[1])
    {
        return node->child[1]->height;
    }

    return -1;
}


static void AvlBalance(avl_t *avl, avl_node_t *node)
{
    if(2 == GetBalanceFactor(node))
    {
        if(0 <= GetBalanceFactor(node->child[0]))
        {
            RotateOnce(avl, node, 0);   
        }
        else
        {
            RotateTwice(avl, node, 0);  
        }
    }

    if(-2 == GetBalanceFactor(node))
    {
        if(0 >= GetBalanceFactor(node->child[1]))
        {
            RotateOnce(avl, node, 1);   
        }
        else
        {
            RotateTwice(avl, node, 1);  
        }
    }

    RecursiveUpdateHeight(avl, node, node->data);
}

static void RotateOnce(avl_t *avl, avl_node_t *node, int index)
{
    avl_node_t *parent = NULL, *rotated_node = NULL;

    rotated_node = node->child[index];

    node->child[index] = rotated_node->child[!index];
    
    parent = AvlFindParentRecur(avl, avl->root, node->data);
    
    if(!parent)
    {
        avl->root = rotated_node;
    }

    else
    {
        if(parent->child[index] == node)
        {
            parent->child[index] = rotated_node;
        }

        else
        {
            parent->child[!index] = rotated_node;
        }
    }

    rotated_node->child[!index] = node;
    UpdateNodeHeight(node);
    UpdateNodeHeight(rotated_node);
}

static void RotateTwice(avl_t *avl, avl_node_t *node, int index)
{
    RotateOnce(avl, node->child[index], !index);
    RotateOnce(avl, node, index);
}


static avl_node_t *AvlFindParentRecur(avl_t *avl, avl_node_t *root, void *data)
{

    if((NULL != root->child[FindIndex(avl, root, data)]) &&
        0 == CompareData(avl, root->child[FindIndex(avl, root, data)], data))
    {
        return root;
    }

    
    if(NULL == root->child[FindIndex(avl, root, data)])
    {
        return NULL;
    }

    return AvlFindParentRecur(avl, root->child[FindIndex(avl, root, data)], data);
}


static int NumOfChildren(avl_node_t *node)
{
    return (NULL != node->child[0]) + (NULL != node->child[1]);
}

static void RemoveLeaf(avl_t *avl, avl_node_t *node, void *data)
{
    avl_node_t *parent = NULL;
    parent = AvlFindParentRecur(avl, avl->root, data);
    
    if(!parent)
    {
        
        RemoveNode(node);
        return;
    }

    parent->child[FindIndex(avl, parent, data)] = NULL;
    RemoveNode(node);
    RecursiveUpdateHeight(avl, parent, data);
}

static void RemoveNodeOneChild(avl_t *avl, avl_node_t *node, void *data)
{
    avl_node_t *parent = NULL;
    parent = AvlFindParentRecur(avl, avl->root, data);
    /* check if the node has no parent, it's the root node */
    if(!parent)
    {
        if(NULL != node->child[0])
        {
            avl->root = node->child[0];
        }

        else
        {
            avl->root = node->child[1];
        }

        RemoveNode(node);
        RecursiveUpdateHeight(avl, avl->root, data);
        return;
    }

    if(NULL != node->child[0])
    {
        parent->child[FindIndex(avl, parent, node->data)] = node->child[0];
    }

    else
    {
        parent->child[FindIndex(avl, parent, node->data)] = node->child[1];
    }

    RemoveNode(node);
    RecursiveUpdateHeight(avl, parent, data);
}

static void RemoveNodeTwoChilds(avl_t *avl, avl_node_t *node, void *data)
{
    avl_node_t *successor = NULL;

    successor = AvlFindLeftSuccessorRecur(node->child[1]);
    data = successor->data;
    AvlRemove(avl, data);
    node->data = data;
}


static avl_node_t *AvlFindLeftSuccessorRecur(avl_node_t *node)
{

    if(NULL == node->child[0])
    {
        return node;
    }

    return AvlFindLeftSuccessorRecur(node->child[0]);
}

