/*********************************
 * Reviewer: koby 				
 * Author: Yisrael Fisch 			
 * File: DHCP.c					
 * ******************************/
 
#include <math.h> /* pow */
#include <stdlib.h> /* malloc, free */
#include <arpa/inet.h> /* inet_network */
#include <assert.h>
#include "DHCP.h"

typedef struct dhcp_node
{
    struct dhcp_node *child[2];
    int is_occupied;
}dhcp_node_t;

struct dhcp
{
    dhcp_node_t *root;
    unsigned int net_address;
    int host_mask;
};

static dhcp_node_t *CreateNewNode();
static int ThreeAdressesInit(dhcp_t *dhcp, int level, int index);
static void RecursiveDestroy(dhcp_node_t *node);
static void RemoveNode(dhcp_node_t *node);
static ip_address_t RecursiveAlloc(dhcp_node_t *node,  int level, ip_address_t address);
static int IsChildrenOccupied(dhcp_node_t *node);
static size_t RecursiveCountFree(dhcp_node_t *node, int level);
static dhcp_node_t *RecursiveRenewIP(dhcp_node_t *node, ip_address_t ip, int level);
static int RecursiveFreeIp(dhcp_node_t *node, ip_address_t ip, int level);


dhcp_t *DHCPCreate(const char *net_address, int net_mask)
{
    dhcp_t *dhcp = NULL;

    if(!(dhcp = (dhcp_t *)malloc(sizeof(dhcp_t))))
    {
        return NULL;
    }

    if((dhcp->net_address = inet_network(net_address)) == (unsigned int)-1)
    {
        free(dhcp);
        return NULL;
    }

    dhcp->root = CreateNewNode();
    dhcp->host_mask = 32 - net_mask;
    
    if (ThreeAdressesInit(dhcp, dhcp->host_mask, 0) || ThreeAdressesInit(dhcp, dhcp->host_mask - 1, 1))
    {
        dhcp->root = NULL;
        dhcp->net_address = 0;
        dhcp->host_mask = 0;
        free(dhcp);
        dhcp = NULL;
        return NULL;
    }

    return dhcp;
}

static dhcp_node_t *CreateNewNode()
{
    dhcp_node_t *new_node = NULL;

    if(!(new_node = (dhcp_node_t *)malloc(sizeof(dhcp_node_t))))
    {
        return NULL;
    }

    new_node->child[0] = NULL;
    new_node->child[1] = NULL;
    new_node->is_occupied = 0;

    return new_node;
}

static int ThreeAdressesInit(dhcp_t *dhcp, int level, int index)
{
    dhcp_node_t *node = NULL;
    int i = 0;

    node = dhcp->root;
    for(i = 0; i < level; ++i)
    {
        if(!(node->child[index] = CreateNewNode()))
        {
            DHCPDestroy(dhcp);
            return 1; 
        }
        node = node->child[index];
    }
    node->is_occupied = 1;

    return 0;
}

void DHCPDestroy(dhcp_t *dhcp)
{
    assert(dhcp);

    RecursiveDestroy(dhcp->root);

    dhcp->root = NULL;
    dhcp->net_address = 0;
    dhcp->host_mask = 0;

    free(dhcp);
    dhcp = NULL;
}

static void RecursiveDestroy(dhcp_node_t *node)
{
    if(!node)
    {
        return;
    }

    RecursiveDestroy(node->child[0]);
    RecursiveDestroy(node->child[1]);

    RemoveNode(node);
}

static void RemoveNode(dhcp_node_t *node)
{
    node->child[0] = NULL;
    node->child[1] = NULL;
    node->is_occupied = 0;

    free(node);
    node = NULL;
}

ip_address_t DHCPAllocateIp(dhcp_t *dhcp)
{
    ip_address_t address = 0;

    assert(dhcp);

    address = RecursiveAlloc(dhcp->root, dhcp->host_mask, address);
    if(address == (ip_address_t)-1)
    {
        return (ip_address_t)-1;
    }

    return address | dhcp->net_address;
}

static ip_address_t RecursiveAlloc(dhcp_node_t *node,  int level, ip_address_t address)
{
    int child_index = 0;
    
    if(!level)
    {
        node->is_occupied = 1;
        return address;
    }

    /*check which way to go, left or right*/
    child_index = (node->child[0] && node->child[0]->is_occupied);

    if(!node->child[child_index])
    {
        if(!(node->child[child_index] = CreateNewNode()))
        {
            return -1;
        }
        address <<= 1;
        address |= child_index;

        address = RecursiveAlloc(node->child[child_index], --level, address);
        if(IsChildrenOccupied(node))
        {
            node->is_occupied = 1;
        }
        return address;
    }
    if(!(node->child[child_index]->is_occupied))
    {
        address <<= 1;
        address |= child_index;
        
        address = RecursiveAlloc(node->child[child_index], --level, address);
        if(IsChildrenOccupied(node))
        {
            node->is_occupied = 1;
        }
        return address;
    }

    return -1;
}


static int IsChildrenOccupied(dhcp_node_t *node)
{
    if(node->child[0] && node->child[1])
    {
        return node->child[0]->is_occupied && node->child[1]->is_occupied; 
    }

    return 0;
}



size_t DHCPCountFree(dhcp_t *dhcp)
{
    assert(dhcp);
    return pow(2, dhcp->host_mask) - (RecursiveCountFree(dhcp->root, dhcp->host_mask) + 2);
}

static size_t RecursiveCountFree(dhcp_node_t *node, int level)
{
    if(!node)
    {
        return 0;
    }
    
    if(!level)
    {
        return 1;
    }
    
    return RecursiveCountFree(node->child[0], level - 1) + RecursiveCountFree(node->child[1], level - 1);
}


int DHCPRenewIP(dhcp_t *dhcp, ip_address_t ip)
{
    assert(dhcp);
    return !RecursiveRenewIP(dhcp->root, ip, dhcp->host_mask);
}

static dhcp_node_t *RecursiveRenewIP(dhcp_node_t *node, ip_address_t ip, int level)
{
    if(!node)
    {
        return NULL;
    }
    
    if(!level)
    {
        return node;
    }

    return RecursiveRenewIP(node->child[(ip >> (level - 1)) & 1], ip, level -1);
}


int DHCPFreeIp(dhcp_t *dhcp, ip_address_t ip)
{
    assert(dhcp);
    return RecursiveFreeIp(dhcp->root, ip, dhcp->host_mask);
}

static int RecursiveFreeIp(dhcp_node_t *node, ip_address_t ip, int level)
{
    int index = (ip >> (level - 1)) & 1;
    int res = 0;

    if(!node->child[index])
    {
        return 1;
    }
    
    if(level == 1)
    {

        RemoveNode(node->child[index]);
        node->child[index] = NULL;
    
        return 0;
    }

    res = RecursiveFreeIp(node->child[index], ip, level -1);

    /* if my child still have child*/   
    if((node->child[index]->child[0] || node->child[index]->child[1]))
    {
        node->child[index]->is_occupied = 0;

        return res;
    }

    RemoveNode(node->child[index]);
    node->child[index] = NULL;

    return res;
}