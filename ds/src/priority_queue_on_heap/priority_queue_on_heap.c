/*********************************
 * Reviewer: 				
 * Author: Yisrael Fisch 			
 * File: priority_queue_on_heap.c					
 * ******************************/
 
 /**/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc & free*/

#include "priority_queue.h"
#include "heap.h"
#include "vector.h"
/*******Defines******/



/*******Structs******/
struct p_queue
{
    heap_t *heap;
    PQcompare_t priority_func;
    void *user_param;
};

typedef struct pq_node
{
    ilrd_uid_t uid;
    void *data;
}pq_node_t;


/*******Service Funcs******/
static int PQCompare(const void *pq1, const void *pq2, void *pq)
{
    assert(pq1);
    assert(pq2);
    assert(pq);
    return ((pri_queue_t *)pq)->priority_func(((pq_node_t *)pq1)->data,
                        ((pq_node_t *)pq2)->data, ((pri_queue_t *)pq)->user_param);
}

static int MatchFunc(const void *PQ_data, const void *data, void *user_param)
{
    assert(PQ_data);
    assert(data);
    (void *)user_param;
    return UIDIsSame(((pq_node_t *)PQ_data)->uid, *(ilrd_uid_t *)data);
}

/*******Funcs Funcs******/
pri_queue_t *PQueueCreate(PQcompare_t priority_func, void *user_param)
{
    pri_queue_t *pq = NULL;
    assert(priority_func);
    /*assert(user_param):*/
    pq = (pri_queue_t *)malloc(sizeof(pri_queue_t));
    if(!pq)
    {
        return NULL;
    }

    pq->heap = HeapCreate(PQCompare, pq);
    if(!pq->heap)
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
    HeapDestroy(pq->heap);

    pq->heap = NULL;
    pq->priority_func = NULL;
    pq->user_param = NULL;
    
    free(pq);
    pq = NULL;
}

ilrd_uid_t PQueueEnQueue(pri_queue_t *pq, void *data)
{
    pq_node_t *new_node;
    
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
    if (HeapPush(pq->heap, new_node))
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
    
    assert(pq);
    assert(data);

    new_node = (pq_node_t *)malloc(sizeof(pq_node_t));
    if(!new_node)
    {
        return 1;
    }

    new_node->data = data;
    new_node->uid = old_uid;

    
    if (HeapPush(pq->heap, new_node))
    {
        new_node->uid = UIDGetNull();
        new_node->data = NULL;
        free(new_node);
        return 1;
    }
    
    return 0;

}

ilrd_uid_t PQueueDeQueue(pri_queue_t *pq)
{
    pq_node_t *temp_node = NULL;
    ilrd_uid_t temp_uid = UIDGetNull();

    assert(pq);
    temp_node = (pq_node_t *)HeapPeek(pq->heap);
    temp_uid = temp_node->uid;

    temp_node->uid = UIDGetNull();
    temp_node->data = NULL;

    HeapPop(pq->heap);
    free(temp_node);

    return temp_uid;
}

void *PQueuePeek(pri_queue_t *pq)
{
    assert(pq);
    return ((pq_node_t *)HeapPeek(pq->heap))->data;
}

size_t PQueueSize(pri_queue_t *pq)
{
    assert(pq);
    return HeapSize(pq->heap);
}

int PQueueIsEmpty(pri_queue_t *pq)
{
    assert(pq);
    return HeapIsEmpty(pq->heap);
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

    pq_node_t *pq_node = NULL;
    void *data = NULL;
    assert(pq);
    pq_node = (pq_node_t *)HeapRemove(pq->heap, &uid, MatchFunc ,pq->user_param);
    
    if(!pq_node)
    {
        return NULL;
    }

    data = pq_node->data;
    
    pq_node->uid = UIDGetNull();
    pq_node->data = NULL;
    free(pq_node);
    pq_node = NULL;

    return data;
}
