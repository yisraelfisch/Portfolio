/*********************************
 * Reviewer: 
 * Author: yisrael fisch       
 * File: sceduler_test.c
 * ******************************/
#include <stdio.h>/*puts, printf*/
#include <stdlib.h> /*malloc, free*/
#include "scheduler.h"
static int ActionTask1(void *arg);
static int ActionTask2(void *arg);
static int ActionTask3(void *arg);
static int ActionTask4(void *arg);
static int ActionTask5(void *arg);
void SchedulerTest(void);

typedef struct tester
{
    scheduler_t *scdlr;
    ilrd_uid_t uid;
    int interval;
}tester_t;

int main()
{
    SchedulerTest();
    return 0;
}

void SchedulerTest(void)
{
    ilrd_uid_t uid = UIDGetNull();
    scheduler_t *scdlr = SchedulerCreate();
    tester_t tst1, tst2, tst3, tst4, tst5;

    if(!SchedulerIsEmpty(scdlr) || SchedulerSize(scdlr))
    {
        puts("Error 1");
    }

    tst1.scdlr = scdlr;
    tst1.interval = 1;
    tst1.uid = uid = SchedulerAddTask(scdlr, ActionTask1, &tst1, 1);

    tst2.scdlr = scdlr;
    tst2.interval = 2;
    tst2.uid = SchedulerAddTask(scdlr, ActionTask2, &tst2, 2); 

    tst3.scdlr = scdlr;
    tst3.interval = 5;
    tst3.uid = SchedulerAddTask(scdlr, ActionTask3, &tst3, 5);

    tst4.scdlr = scdlr;
    tst4.interval = 15;
    tst4.uid = SchedulerAddTask(scdlr, ActionTask4, &tst4, 15);

    tst5.scdlr = scdlr;
    tst5.interval = 10;
    tst5.uid = uid; SchedulerAddTask(scdlr, ActionTask5, &tst5, 10); 

    if(SchedulerIsEmpty(scdlr) || SchedulerSize(scdlr) != 5)
    {
        puts("Error 2");
    }

    SchedulerRun(scdlr);

    if(SchedulerIsEmpty(scdlr) || SchedulerSize(scdlr) != 2)
    {
        puts("Error 3");
    }
    
    SchedulerClearAll(scdlr);
    SchedulerRun(scdlr);

    if(!SchedulerIsEmpty(scdlr) || SchedulerSize(scdlr))
    {
        puts("Error 4");
    }

    SchedulerDestroy(scdlr);
}


static int ActionTask1(void *arg)
{
    puts("Type 1: Should run forever");
    printf("Interval: %d\n", ((tester_t *)arg)->interval);
    puts("");
    
    return 0;
}

static int ActionTask2(void *arg)
{
    static int counter = 0;
    puts("Type 2: Should run 3 times");
    printf("Interval: %d\n", ((tester_t *)arg)->interval);
    puts("");
    
    if(++counter == 3)
    {
        puts("Type 2: Should stop now");
        puts("");
        return 1;
    }

    return 0;
}

static int ActionTask3(void *arg)
{
    puts("Type 3: Should run once and be removed");
    printf("Interval: %d\n", ((tester_t *)arg)->interval);
    puts("");

    return SchedulerRemoveTask(((tester_t *)arg)->scdlr,  ((tester_t *)arg)->uid);
}

static int ActionTask4(void *arg)
{
    puts("Type 4: Should stop the scheduler");
    printf("Interval: %d\n", ((tester_t *)arg)->interval);
    puts("");

    SchedulerStop(((tester_t *)arg)->scdlr);
    
    return 0;
}

static int ActionTask5(void *arg)
{
    puts("Type 5: Should run once and remove type 1");
    printf("Interval: %d\n", ((tester_t *)arg)->interval);
    puts("");

    return SchedulerRemoveTask(((tester_t *)arg)->scdlr,  ((tester_t *)arg)->uid);
}
/*typedef struct args
{
    void *arg;
    scheduler_t *sch;
} args_t;

int FuncBoom(void *arg)
{
    static int count;
    printf("%s!\n", (char *)arg);
    ++count;
    count = count % 5;

    return (!count);
}

int Again(void *arg)
{
    int again = 1;
    scheduler_t *sch = (scheduler_t *)arg;

    printf("Run again? 1 for YES, 0 for NO: ");
    scanf("%d", &again);

    if (!again)
    {
        SchedulerStop(sch);
        return again;
    }

    SchedulerAddTask(sch, FuncBoom, "BOOM", 2);

    return again;
}

int Action1PrintStr(void *arg) 
{
    char arr[] = {'U', 'T', '!'};
    static int count;
    
    printf("%c\n", arr[count % sizeof(arr)]);
    ++count;

    (void)arg;

    
    return 0;
}

int Action2PrintStr(void *arg) 
{
    char arr[] = {'T', 'C', 'H', 'E', '!', '!'};
    static int count;
    printf("%c\n", arr[count % sizeof(arr)]);
    ++count;

    (void)arg;

    return 0;
}

int Action3PrintStr(void *arg) 
{
    char arr[] = {'E', 'S', 'E', 'W', ' ', 'S', '!'};
    static int count;
    printf("%c\n", arr[count % sizeof(arr)]);
    ++count;

    (void)arg;

    return 0;
}

int Action4PrintStr(void *arg) 
{
    char arr[] = {'T', 'S', ' ', 'C', 'S', 'S', 'A', 'A', 'M', 'S', '!', ';'};
    static int count;
    printf("%c\n", arr[count % sizeof(arr)]);
    ++count;

    if (0 == count % 6)
    {
        printf("\n");
        SchedulerAddTask(((args_t *)arg)->sch, Again, ((args_t *)arg)->sch, 0);
    }


    return 0;
}

scheduler_t *TestStart()
{
    scheduler_t *sch = SchedulerCreate();
    return sch;
    
} 

void TestDestroy(scheduler_t *sch)
{
    SchedulerDestroy(sch);
}

void TestCreateTask()
{
    scheduler_t *sch = TestStart();
    ilrd_uid_t task1 = SchedulerAddTask(sch, Action1PrintStr, "test 1", 10);
    ilrd_uid_t task2 = SchedulerAddTask(sch, Action1PrintStr, "test 2", 20);

    if (SchedulerIsEmpty(sch))
    {
        printf("TestCreateTask failed (not empty)\n");
    }

    if (2 != SchedulerSize(sch))
    {
        printf("TestCreateTask failed (size)\n");
    }

    SchedulerRemoveTask(sch, task1);
    SchedulerRemoveTask(sch, task2);

    if (!SchedulerIsEmpty(sch))
    {
        printf("TestCreateTask failed (is empty)\n");
    }

    TestDestroy(sch);
}


void TestClearAll()
{
    scheduler_t *sch = TestStart();
    ilrd_uid_t task1 = SchedulerAddTask(sch, Action1PrintStr, "test 1", 10);
    ilrd_uid_t task2 = SchedulerAddTask(sch, Action1PrintStr, "test 2", 20);

    SchedulerClearAll(sch);

    if (!SchedulerIsEmpty(sch))
    {
        printf("TestClearAll failed (is empty)\n");
    }

    TestDestroy(sch);

    (void)task1;
    (void)task2;
}

args_t *CreateArgs(scheduler_t *sch, void *data)
{
    args_t *arg = (args_t *) malloc(sizeof(args_t));
    if (!arg)
    {
        return NULL;
    }
    arg->arg = data;
    arg->sch = sch;

    return arg;
}

void DestroyArgs(args_t *arg)
{
    arg->arg = NULL;
    arg->sch = NULL;
    free(arg);
    arg = NULL;
}

void TestExecute()
{
    scheduler_t *sch = TestStart();
    args_t *args1 = CreateArgs(sch, "test 1");
    args_t *args2 = CreateArgs(sch, "test 2");
    args_t *args3 = CreateArgs(sch, "test 3");
    args_t *args4 = CreateArgs(sch, "test 4");

    ilrd_uid_t task1 = SchedulerAddTask(sch, Action1PrintStr, args1, 11);
    ilrd_uid_t task2 = SchedulerAddTask(sch, Action2PrintStr, args2, 7);
    ilrd_uid_t task3 = SchedulerAddTask(sch, Action3PrintStr, args3, 5);
    ilrd_uid_t task4 = SchedulerAddTask(sch, Action4PrintStr, args4, 3);

    SchedulerRun(sch);

    SchedulerRemoveTask(sch, task1);
    SchedulerRemoveTask(sch, task2);

    printf("****************second run*********************\n");
    SchedulerRun(sch);

    TestDestroy(sch);

    DestroyArgs(args1);
    DestroyArgs(args2);
    DestroyArgs(args3);
    DestroyArgs(args4);

    (void)task1;
    (void)task2;
    (void)task3;
    (void)task4;
}

int main()
{
    TestClearAll();
    TestCreateTask();
    TestExecute();
    return 0;
}*/

/*static int ActionTask1(void *arg);
static int ActionTask2(void *arg);
static int ActionTask3(void *arg);
static int ActionTask4(void *arg);
void SchedulerTest(void);

typedef struct student
{
    char name[50];
    char id[10];
    int interval;
}st;

typedef struct container
{
    scheduler_t *scdlr;
    ilrd_uid_t uid;
    int interval;
}container;

int main()
{
    SchedulerTest();
    return 0;
}

void SchedulerTest(void)
{
    ilrd_uid_t uid = UIDGetNull();
    scheduler_t *scdlr = SchedulerCreate();

	st student1 = {"Koby", "123456789",3};
    st student2 = {"Yossi", "123456789", 4};
	st student3 = {"yisrael", "123456789", 2};
    
    container cr;
    cr.scdlr = scdlr;
    cr.uid = g_bad_uid;
    cr.interval = 20;
    
    if(!SchedulerIsEmpty(scdlr))
    {
        puts("Error1");
    }

    if(SchedulerSize(scdlr))
    {
        puts("Error2");
    }


    SchedulerAddTask(scdlr, ActionTask4, &cr, cr.interval);
    uid = SchedulerAddTask(scdlr, ActionTask1, &student1, student1.interval);
    SchedulerAddTask(scdlr, ActionTask1, &student2, student2.interval);
	SchedulerAddTask(scdlr, ActionTask2, &student3, student3.interval);

    cr.uid = uid;
    SchedulerAddTask(scdlr, ActionTask3, &cr, 10);
    
    if(SchedulerSize(scdlr) != 5)
    {
        puts("Error5");
    }

    SchedulerRun(scdlr);

    if(SchedulerIsEmpty(scdlr))
    {
        puts("Error6");
    }

    if(SchedulerSize(scdlr) != 2)
    {
        puts("Error7");
    }

    SchedulerClearAll(scdlr);

    if(!SchedulerIsEmpty(scdlr))
    {
        puts("Error8");
    }

    if(SchedulerSize(scdlr))
    {
        puts("Error9");
    }

    SchedulerRun(scdlr);

    SchedulerDestroy(scdlr);
}


static int ActionTask1(void *arg)
{
    puts("action task1 Should run forever");
    printf("Name: %s\nI.D: %s\n \a\n", 
    	    ((st *)arg)->name, ((st *)arg)->id);
    printf("Interval: %d\n", ((st *)arg)->interval);
    puts("");
    
    return 0;
}

static int ActionTask2(void *arg)
{
    static int counter = 1;
    puts("yisrael Should run 3 times and removed");
    printf("Name: %s\nI.D: %s\n \atime num:%d\n", 
    	    ((st *)arg)->name, ((st *)arg)->id, counter);
    
    printf("Interval: %d\n", ((st *)arg)->interval);
    puts("");
    
    if(counter++ == 3)
    {
        return 1;
    }

    return 0;
}

static int ActionTask3(void *arg)
{
    puts("action task 3 Should run once and be removed with koby");
    printf("Interval: %d\n", 10);
    puts("");

    return (SchedulerRemoveTask(((container *)arg)->scdlr,  ((container *)arg)->uid));
    
}

static int ActionTask4(void *arg)
{
    puts("action task 4 Should stop the scheduler");
    printf("Interval: %d\n", ((container *)arg)->interval);
    puts("");

    SchedulerStop(((container *)arg)->scdlr);
    
    return 0;
}
*/