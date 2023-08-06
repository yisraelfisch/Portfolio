/*********************************
 * Reviewer: 
 * Author: yisrael fisch       
 * File: sceduler.c
 * ******************************/

#include <stdlib.h>/*malloc, free*/
#include <time.h>/*time_t*/
#include <unistd.h>/*sleep*/
#include <assert.h>/*assert*/
#include"priority_queue.h"
#include "scheduler.h"
#include "task.h"

struct scheduler
{
	pri_queue_t *pq;
	task_t *running_task;/*store the cur running task*/
	int keep_running;	
};

static int SCCompare(const void *data1, const void *data2, void *user_param);

scheduler_t *SchedulerCreate(void)
{
	scheduler_t *scdlr = NULL;
	scdlr = (scheduler_t *)malloc(sizeof(scheduler_t));

	if(!scdlr)
	{
		return NULL;
	}

	scdlr->keep_running = 0;
	scdlr->running_task = NULL;
	scdlr->pq = PQueueCreate(SCCompare, scdlr);
	if(!(scdlr->pq))
	{
        #ifndef NDEBUG
        perror("Error");
        #endif

		free(scdlr);
		scdlr = NULL;
		return NULL;
	}

	return scdlr;
}

void SchedulerDestroy(scheduler_t *scdlr)
{
	assert(scdlr);

	SchedulerClearAll(scdlr);
	PQueueDestroy(scdlr->pq);
	scdlr->pq = NULL;
	free(scdlr);
	scdlr = NULL;
}


ilrd_uid_t SchedulerAddTask(scheduler_t *scdlr,  
            scheduler_action_t action_func,
            void *arg,
            size_t interval_in_sec)/*size_t interval_in_sec*/
{
	task_t *new_task = NULL;
	ilrd_uid_t uid = UIDGetNull();
	assert(scdlr);
	assert(action_func);
	
	new_task = TaskCreate(interval_in_sec, time(NULL) + interval_in_sec, action_func, arg);

	if(!new_task)
	{
        #ifndef NDEBUG
        perror("Error");
        #endif

		return UIDGetNull();
	}
	uid = PQueueEnQueue(scdlr->pq, new_task);
	if(UIDIsSame(uid, UIDGetNull()))
	{
		TaskDestroy(new_task);
	}

	return uid;

}

int SchedulerRemoveTask(scheduler_t *scdlr, ilrd_uid_t uid)
{	
	task_t *temp_task = NULL;
	assert(scdlr);
	
	temp_task = PQueueErase(scdlr->pq, uid);
	if(!temp_task)
    {
        return 1;
    }
	
	TaskDestroy(temp_task);

	return 0;
}

void SchedulerClearAll(scheduler_t *scdlr)
{
	task_t *temp_task = NULL;
	assert(scdlr);
	while(!SchedulerIsEmpty(scdlr))
	{
		temp_task = PQueuePeek(scdlr->pq);
		TaskDestroy(temp_task);
		PQueueDeQueue(scdlr->pq);
	}
}

int SchedulerIsEmpty(scheduler_t *scdlr)
{
	assert(scdlr);
	 return (PQueueIsEmpty(scdlr->pq) && !scdlr->running_task);

}

size_t SchedulerSize(scheduler_t *scdlr)
{
	assert(scdlr);
	return PQueueSize(scdlr->pq) + !!scdlr->running_task;
}


int SchedulerRun(scheduler_t *scdlr)
{
    
    ilrd_uid_t uid = UIDGetNull();    
    int time_to_sleep = 0;
    int re_enqueue_flag = 0;

    assert(scdlr);
    scdlr->keep_running = 1;

    while((!SchedulerIsEmpty(scdlr)) && scdlr->keep_running && !re_enqueue_flag)
    {
        scdlr->running_task = PQueuePeek(scdlr->pq);

        uid = PQueueDeQueue(scdlr->pq);
        
        time_to_sleep = TaskGetExecTime(scdlr->running_task) - time(NULL);
		
		while(time_to_sleep > 0)
        {
            time_to_sleep = sleep(time_to_sleep);/*we want sleep to continue when interrupt*/
        }
      
        if(TaskExec(scdlr->running_task))
        {
            TaskDestroy(scdlr->running_task);
        }
        else
        {
        	TaskSetExecTime(scdlr->running_task, TaskGetExecTime(scdlr->running_task) + TaskGetIntervalTime(scdlr->running_task));
        	re_enqueue_flag = PQueueReEnQueue(scdlr->pq, scdlr->running_task, uid);

        }

    }

    scdlr->keep_running = 0;
    scdlr->running_task = NULL;

    if(1 == re_enqueue_flag)
    {
    	TaskDestroy(scdlr->running_task);
    	return 1;
    }

    
    return 0;
}

void SchedulerStop(scheduler_t *scdlr)
{
	assert(scdlr);
	scdlr->keep_running = 0;
}


static int SCCompare(const void *data1, const void *data2, void *user_param)
{
	assert(data1);
	assert(data2);
	
	(void)user_param;	
	return (TaskGetExecTime((task_t *)data1) <= TaskGetExecTime((task_t *)data2));
	
}













