/*********************************
 * Reviewer: 
 * Author: yisrael fisch       
 * File: task.h
 * ******************************/

#ifndef __TASK_H__
#define __TASK_H__

#include <time.h>/*time_t*/

                                

typedef int (*task_action_t)(void *arg);
/*return value: 0 if success, non-zero if faild*/
typedef struct task task_t;

task_t *TaskCreate(size_t interval_in_seconds, time_t exec_time, task_action_t action_func, void *arg);
/*
Descreption: create a new task
param: size_t interval_in_sec, time_t exec_time(absolut time since epoch in seconds), void *arg(arg for parameters),
task_action_t action_func. 
Return val: pointer to task, if fails NULL ptr/
Complexity:
*/

void TaskDestroy(task_t *task);
/*
Descreption: destroy a task
param: ptr to task
Return val: non
Complexity:
*/

time_t TaskGetExecTime(task_t *task);
/*
Descreption: gives the exe time of the task
param: ptr to task
Return val: time_t exe_time
Complexity:
*/

size_t TaskGetIntervalTime(task_t *task);
/*
Descreption: gives the interval time of the task
param: ptr to task
Return val: time_t exe_time
Complexity:
*/

void TaskSetExecTime(task_t *task, time_t new_exec_time);
/*
Descreption: change the exec time of the task
param: ptr to task, new exec
Return val: non
Complexity:
*/

void TaskSetIntervalTime(task_t *task, size_t new_interval_in_seconds);
/*
Descreption: change the interval time of the task
param: ptr to task, new interval time
Return val: non
Complexity:
*/

int TaskExec(task_t *task);
/*
Descreption: execute task func
param: ptr to task
Return val: zero if success, non-zero integer when fails.
Complexity:
*/

#endif /* __TASK_H__ */