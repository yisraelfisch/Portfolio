/*********************************
 * Reviewer: 
 * Author: yisrael fisch       
 * File: priority_queue.h
 * ******************************/

#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <stddef.h> /*size_t*/
#include "sorted_list.h" /*compare_t*/
#include "uid.h"


typedef struct p_queue pri_queue_t;
typedef int(* PQcompare_t)(const void *data1, const void *data2, void *user_param);

pri_queue_t *PQueueCreate(PQcompare_t priority_func, void *user_param);

void PQueueDestroy(pri_queue_t *pq);

ilrd_uid_t PQueueEnQueue(pri_queue_t *pq, void *data); 

int PQueueReEnQueue(pri_queue_t *pq, void *data, ilrd_uid_t old_uid);

/*void PQueueDeQueue(pri_queue_t *pq);*/

ilrd_uid_t PQueueDeQueue(pri_queue_t *pq);

void *PQueuePeek(pri_queue_t *pq); /* data, or null if empty */

int PQueueIsEmpty(pri_queue_t *pq); /* non-zero if empty */

size_t PQueueSize(pri_queue_t *pq);

void PQueueClear(pri_queue_t *pq);

void *PQueueErase(pri_queue_t *pq, ilrd_uid_t uid);

#endif /* __PRIORITY_QUEUE_H__ */