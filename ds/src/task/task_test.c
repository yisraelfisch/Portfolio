/*********************************
 * Reviewer: 
 * Author: yisrael fisch       
 * File: task_test.c
 * ******************************/

#include <stdio.h> /* puts */
#include "task.h" 

typedef struct student
{
    char name[50];
    char id[10];
    int grade;
} st;

static int ActionTask(void *arg);
void TaskTest(void);

int main()
{
    TaskTest();
    return 0;
}

void TaskTest(void)
{
    task_t *task1 = NULL;
    task_t *task2 = NULL;
    task_t *task3 = NULL;
    task_t *task4 = NULL;
    task_t *task5 = NULL;

    st student1 = {"Koby", "123456789", 90};
    st student2 = {"Yossi", "123456789", 91};
    st student3 = {"Eli", "123456789", 92};
    st student4 = {"Shuki", "123456789", 93};
    st student5 = {"Bob", "123456789", 94};

    task1 = TaskCreate(0, 0, ActionTask, &student1);
    task2 = TaskCreate(1, 1, ActionTask, &student2);
    task3 = TaskCreate(2, 2, ActionTask, &student3);
    task4 = TaskCreate(3, 3, ActionTask, &student4);
    task5 = TaskCreate(4, 4, ActionTask, &student5);

    if (TaskGetIntervalTime(task1) != 0 || TaskGetIntervalTime(task2) != 1 || TaskGetIntervalTime(task3) != 2 || TaskGetIntervalTime(task4) != 3 ||TaskGetIntervalTime(task5) != 4)
    {
        puts("Error1");
    }
    
    if (TaskGetExecTime(task1) != 0 || TaskGetExecTime(task2) != 1 || TaskGetExecTime(task3) != 2 || TaskGetExecTime(task4) != 3 ||TaskGetExecTime(task5) != 4)
    {
        puts("Error2");
    }

    TaskSetIntervalTime(task1, TaskGetIntervalTime(task1) + 10);
    TaskSetIntervalTime(task2, TaskGetIntervalTime(task2) + 10);
    TaskSetIntervalTime(task3, TaskGetIntervalTime(task3) + 10);
    TaskSetIntervalTime(task4, TaskGetIntervalTime(task4) + 10);
    TaskSetIntervalTime(task5, TaskGetIntervalTime(task5) + 10);

    if (TaskGetIntervalTime(task1) != 0 + 10 || TaskGetIntervalTime(task2) != 1 + 10 || TaskGetIntervalTime(task3) != 2 + 10 || TaskGetIntervalTime(task4) != 3 + 10 ||TaskGetIntervalTime(task5) != 4 + 10)
    {
        puts("Error3");
    }

	TaskSetExecTime(task1, TaskGetExecTime(task1) + 10);
    TaskSetExecTime(task2, TaskGetExecTime(task2) + 10);
    TaskSetExecTime(task3, TaskGetExecTime(task3) + 10);
    TaskSetExecTime(task4, TaskGetExecTime(task4) + 10);
    TaskSetExecTime(task5, TaskGetExecTime(task5) + 10);

    if (TaskGetExecTime(task1) != 0 + 10 || TaskGetExecTime(task2) != 1 + 10 || TaskGetExecTime(task3) != 2 + 10 || TaskGetExecTime(task4) != 3 + 10 ||TaskGetExecTime(task5) != 4 + 10)
    {
        puts("Error4");
    }
    
    puts("");
    TaskExec(task1);
    TaskExec(task2);
    TaskExec(task3);
    TaskExec(task4);
    TaskExec(task5);

    TaskDestroy(task1);
    TaskDestroy(task2);
    TaskDestroy(task3);
    TaskDestroy(task4);
    TaskDestroy(task5);
}

static int ActionTask(void *arg)
{
    printf("Name: %s\nI.D: %s\nGrade: %d\n", ((st *)arg)->name, ((st *)arg)->id, ((st *)arg)->grade);
    puts("");
    return 0;
} 