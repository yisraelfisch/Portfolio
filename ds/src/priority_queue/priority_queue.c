/*********************************
 * Reviewer: 
 * Author: yisrael fisch       
 * File: priority_queue.c
 * ******************************/

#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/
#include "priority_queue.h"

struct p_queue
{
    sorted_list_t *so_list;
    PQcompare_t priority_func;
    void *user_param;
};

typedef struct pq_node
{
    ilrd_uid_t uid;
    void *data;
}pq_node_t;

static int PQCompare(const void *pq1, const void *pq2, void *pq)
{
    assert(pq1);
    assert(pq2);
    assert(pq);
    return ((pri_queue_t *)pq)->priority_func(((pq_node_t *)pq1)->data,
                        ((pq_node_t *)pq2)->data, ((pri_queue_t *)pq)->user_param);
}

static int MatchFunc(const void *list_data, const void *data)
{
    assert(list_data);
    assert(data);
    return !UIDIsSame(((pq_node_t *)list_data)->uid, *(ilrd_uid_t *)data);
}

pri_queue_t *PQueueCreate(PQcompare_t priority_func, void *user_param)
{
    pri_queue_t *pq = NULL;
    assert(priority_func);
    assert(user_param);
    pq = (pri_queue_t *)malloc(sizeof(pri_queue_t));
    if(!pq)
    {
        return NULL;
    }

    pq->so_list = SortedListCreate(PQCompare, pq);
    if(!pq->so_list)
    {
        free(pq);
        pq = NULL;
        return NULL;
    }
    pq->priority_func = priority_func;
    pq->user_param = user_param;

    return pq; 
}

void PQueueDestroy(pri_queue_t *pq)
{
    assert(pq);
    PQueueClear(pq);
    SortedListDestroy(pq->so_list);

    pq->so_list = NULL;
    pq->priority_func = NULL;
    pq->user_param = NULL;
    
    free(pq);
    pq = NULL;
}

ilrd_uid_t PQueueEnQueue(pri_queue_t *pq, void *data)
{
    pq_node_t *new_node;
    sorted_list_iterator_t sorted_list_end = SortedListEnd(pq->so_list);
    assert(pq);
    assert(data);

    new_node = (pq_node_t *)malloc(sizeof(pq_node_t));
    if(!new_node)
    {
        return UIDGetNull();
    }

    new_node->data = data;
    new_node->uid = UIDGet();

    /*check if sorted list insert failed */
    if (SortedListIsSameIter(SortedListInsert(pq->so_list, new_node),
                                                    sorted_list_end))
    {
        new_node->uid = UIDGetNull();
        new_node->data = NULL;
        free(new_node);
        return UIDGetNull();
    }
    
    return new_node->uid;
   
}

int PQueueReEnQueue(pri_queue_t *pq, void *data, ilrd_uid_t old_uid)
{
    pq_node_t *new_node;
    sorted_list_iterator_t sorted_list_end = SortedListEnd(pq->so_list);
    assert(pq);
    assert(data);

    new_node = (pq_node_t *)malloc(sizeof(pq_node_t));
    if(!new_node)
    {
        return 1;
    }

    new_node->data = data;
    new_node->uid = old_uid;

    
    if (SortedListIsSameIter(SortedListInsert(pq->so_list, new_node),
                                                    sorted_list_end))
    {
        new_node->uid = UIDGetNull();
        new_node->data = NULL;
        free(new_node);
        return 1;
    }
    
    return 0;

}

/*void PQueueDeQueue(pri_queue_t *pq)
{
    
    pq_node_t *temp_node = NULL;

    assert(pq);
    temp_node = SortedListPopFront(pq->so_list);
    

    temp_node->uid = UIDGetNull();
    temp_node->data = NULL;

    free(temp_node);
}*/

ilrd_uid_t PQueueDeQueue(pri_queue_t *pq)
{
    pq_node_t *temp_node = NULL;
    ilrd_uid_t temp_uid = UIDGetNull();

    assert(pq);
    temp_node = SortedListPopFront(pq->so_list);
    temp_uid = temp_node->uid;

    temp_node->uid = UIDGetNull();
    temp_node->data = NULL;

    free(temp_node);

    return temp_uid;
}

void *PQueuePeek(pri_queue_t *pq)
{
    assert(pq);
    return ((pq_node_t *)SortedListGetData(SortedListBegin(pq->so_list)))->data;
}

size_t PQueueSize(pri_queue_t *pq)
{
    assert(pq);
    return SortedListSize(pq->so_list);

}

int PQueueIsEmpty(pri_queue_t *pq)
{
    assert(pq);
    return SortedListIsEmpty(pq->so_list);
}

void PQueueClear(pri_queue_t *pq)
{
    assert(pq);

    while (!PQueueIsEmpty(pq))
    {
        PQueueDeQueue(pq);
    }
}

void *PQueueErase(pri_queue_t *pq, ilrd_uid_t uid)
{
    sorted_list_iterator_t sl_node = SortedListIterInit();
    pq_node_t *pq_node = NULL;
    void *data = NULL;
    assert(pq);

    sl_node = SortedListFindIf(SortedListBegin(pq->so_list),SortedListEnd(pq->so_list), &uid, MatchFunc);

    if(SortedListIsSameIter(sl_node, SortedListEnd(pq->so_list)))
    {
        return NULL;
    }
    pq_node = SortedListGetData(sl_node);
    data = pq_node->data;
    SortedListRemove(sl_node);

    pq_node->uid = UIDGetNull();
    pq_node->data = NULL;
    free(pq_node);
    pq_node = NULL;

    return data;
}









