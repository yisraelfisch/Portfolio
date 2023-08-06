/*********************************
 * Reviewer: 
 * Author: yisrael fisch       
 * File: task.h
 * ******************************/
#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/
#include "task.h"

struct task                    
{
	time_t exec_time_in_sec;
	size_t interval_in_sec;
	void *arg;
	task_action_t action_func;
};

task_t *TaskCreate(size_t interval_in_seconds, time_t exec_time, task_action_t action_func, void *arg)
{
	task_t *new_task = NULL;

	assert(action_func);

	if(!(new_task = (task_t *)malloc(sizeof(task_t))))
	{
		return NULL;
	}

	new_task->interval_in_sec = interval_in_seconds;
	new_task->exec_time_in_sec = exec_time;
	new_task->arg = arg;
	new_task->action_func = action_func;

	return new_task;
}

void TaskDestroy(task_t *task)
{
	task->interval_in_sec = 0;
	task->exec_time_in_sec = 0;
	task->arg = NULL;
	task->action_func = NULL;

	free(task);

    task = NULL;
}

time_t TaskGetExecTime(task_t *task)
{
	assert(task);
	return task->exec_time_in_sec;
}

size_t TaskGetIntervalTime(task_t *task)
{
    assert(task);

    return task->interval_in_sec;
}

void TaskSetExecTime(task_t *task, time_t new_exec_time)
{
	assert(task);
	task->exec_time_in_sec = new_exec_time;	
}

void TaskSetIntervalTime(task_t *task, size_t new_interval_in_seconds)
{
    assert(task);

    task->interval_in_sec = new_interval_in_seconds;
}

int TaskExec(task_t *task)
{
	assert(task);
	return task->action_func(task->arg);
}
