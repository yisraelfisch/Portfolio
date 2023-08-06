/*************************************** 
file name: wd_lib.c
Author: yisrael fisch
*reviewer: 
******************************************/

#define _DEFAULT_SOURCE

#include <stdarg.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h> 
#include <fcntl.h>              
#include <semaphore.h>
#include <string.h>
#include "scheduler.h"
#include "task.h"
#include "priority_queue.h"
#include "wd_lib.h"

#define SIG_INTERVAL 1
#define HEART_BEAT_INTERVAL 5
#define MAX_COUNTER 5
#define WD_EXEC_NAME "wd.Debug.out"
#define NON_ZERO 1
#define MAX_ATTEMPT_TO_SEND_SIG2 3

struct resources
{
    sem_t *child_is_ready;
    scheduler_t *scdlr;
    pthread_t thread;
    char **argv;
};

static int CleanUp(resources_t *resources);
static void *RunAppOrWD(void *arg);
static int CreateProcess(char **argv);
static int IsItTheFirstExec();
static resources_t *InitResources(char **argv);
static void ResetCounter(int sig_num);
static int SendSig(void *arg);
static int CheckHeartBeat(void *arg);
static void DebugPrint(const char* format, ...);
static void ShutDown(int sig_num);
static int AmIApp(char *filename);

int g_shut_down = 0;
pid_t g_partner_pid = 0;
sig_atomic_t g_counter = 0;
int g_is_it_first_exec = 0;




resources_t *MakeMeImmortal(int argc, char **argv)
{
    resources_t *resources = NULL;
    (void)argc;

    if(!(resources = InitResources(argv)))
    {
        perror("Initialization of Resources failed\n");
        return NULL;
    }

    if(AmIApp(argv[0]))
    {
        DebugPrint("I am APP and I was loaded by %s\n", IsItTheFirstExec() ? "TERMINAL" : "WD");
        
        if(IsItTheFirstExec()) 
        {
            g_is_it_first_exec = 1;
            
            setenv("IS_IT_THE_FIRST_TIME", "0", NON_ZERO);
            
            if(CreateProcess(argv) == EXIT_FAILURE)
            {
                perror("Failed CreateWDProcess\n");
                return NULL;
            }
        }
        else 
        {
            g_partner_pid = getppid();
        }

        if(pthread_create(&(resources->thread), NULL, RunAppOrWD, resources))
        {
            perror("Failed pthread_create\n");
            CleanUp(resources);
            return NULL;
        }
    }
    else
    {
        DebugPrint("I am WD and I was loaded by APP\n");

        g_partner_pid = getppid();

        if(pthread_create(&(resources->thread), NULL, RunAppOrWD, resources))
        {
            perror("Failed pthread_create\n");
            CleanUp(resources);
            return NULL;
        }
    }

    return resources;
}


static void *RunAppOrWD(void *arg)
{
    resources_t *resources = (resources_t *)arg;

    if(g_is_it_first_exec)
    {
        sem_wait(resources->child_is_ready);
    }
    else
    {
        sem_post(resources->child_is_ready);
    }

    while(1)
    {
        SchedulerRun(resources->scdlr); /* What about failure? */
        if(!g_shut_down)
        {
            DebugPrint("No HeartBeat---\nIM %s and i'm gonna resusicate %s\n", AmIApp(resources->argv[0]) ? "APP" : "WD", AmIApp(resources->argv[0]) ? "WD" : "APP");
            CreateProcess(resources->argv);
            if(waitpid(g_partner_pid, NULL, WNOHANG) == -1)
            {
                perror("wait");
                return NULL;
            }
            sem_wait(resources->child_is_ready);
        }
        else
        {
            sem_post(resources->child_is_ready);
            break;
        }
    }

    return NULL;
}


static int CreateProcess(char **argv)
{
    char *tmp[3] = {NULL};

    if(AmIApp(argv[0]))
    {
        tmp[0] = WD_EXEC_NAME;
        tmp[1] = argv[0];
    }
    else
    {
        tmp[0] = argv[1];
        tmp[1] = WD_EXEC_NAME;
    }

    if((g_partner_pid = fork()) == -1)
    {
        perror("Failed fork\n");
        return EXIT_FAILURE;
    }
    
    if(g_partner_pid == 0)
    {
        execvp(tmp[0], tmp); 
    }

    return EXIT_SUCCESS;
}

static int AmIApp(char *filename)
{
    return strcmp(filename, WD_EXEC_NAME);
}

static int IsItTheFirstExec()
{
    return !getenv("IS_IT_THE_FIRST_TIME"); /* check for secure_getenv */
}

static resources_t *InitResources(char **argv)
{
    resources_t *resources = NULL;
    struct sigaction sig_action1 = {0};
    struct sigaction sig_action2 = {0};
    int init_status = 0;
    sig_action1.sa_handler = ResetCounter;
    sig_action1.sa_flags = SA_RESTART;
    sig_action2.sa_handler = ShutDown;
    sig_action2.sa_flags = SA_RESTART;

    if(!(resources = (resources_t *)malloc(sizeof(resources_t))))
    {
        perror("malloc failed");
        return NULL;
    }

    resources->child_is_ready = NULL;
    resources->scdlr = NULL;
    resources->thread = 0;
    resources->argv = NULL;

    do
    {
        if(sigaction(SIGUSR1, &sig_action1, NULL))
        {
            perror("sigaction1 failed\n");
            init_status = 1;
            break;
        }

        if(sigaction(SIGUSR2, &sig_action2, NULL))
        {
            perror("sigaction2 failed\n");
            init_status = 1;
            break;
        }

        if(!(resources->scdlr = SchedulerCreate()))
        {
            perror("SchedulerCreate failed\n");
            init_status = 1;
            break;
        }

        if(UIDIsSame(SchedulerAddTask(resources->scdlr, SendSig, argv[0], SIG_INTERVAL), g_bad_uid)
        || UIDIsSame(SchedulerAddTask(resources->scdlr, CheckHeartBeat, resources, HEART_BEAT_INTERVAL), g_bad_uid))
        {
            perror("SchedulerAddTask failed\n");
            init_status = 1;
            break;
        }

        if((resources->child_is_ready = sem_open("CHILD_SEM", O_CREAT, 0666, 0)) == SEM_FAILED)
        {
            perror("sem_open failed\n");
            init_status = 1;
            break;
        }
        
        resources->argv = argv;
    }
    while(0);

    if(init_status)
    {
        CleanUp(resources);
        return NULL;
    }

    return resources;
}

static int CleanUp(resources_t *resources)
{
    if(resources->scdlr)
    {
        SchedulerDestroy(resources->scdlr);
    }

    if(resources->child_is_ready != SEM_FAILED)
    {
        if(sem_unlink("CHILD_SEM") == -1)
        {
            return EXIT_FAILURE;
        }
    }

    if(unsetenv("IS_IT_THE_FIRST_TIME"))
    {
        return EXIT_FAILURE;
    }

    resources->child_is_ready = NULL;
    resources->scdlr = NULL;
    resources->thread = 0;
    resources->argv = NULL;
    
    free(resources);

    resources = NULL;

    return EXIT_SUCCESS;
}

        
static void ResetCounter(int sig_num)
{
    (void)sig_num;
    g_counter = 0;
}

static int SendSig(void *arg)
{
    char *filename = (char *)arg;
    DebugPrint("SEND--- IM %s:\t Partner PID: %d\t COUNTER: %d\n", AmIApp(filename) ? "APP" : "WD", g_partner_pid, g_counter);
    ++g_counter;
    kill(g_partner_pid, SIGUSR1);

    return EXIT_SUCCESS;
}

static int CheckHeartBeat(void *arg)
{
    resources_t *resources = (resources_t *)arg;

    DebugPrint("CheckHeartBeat---\n");
    if(g_counter >= MAX_COUNTER || g_shut_down)
    {
        SchedulerStop(resources->scdlr);
    }

    return EXIT_SUCCESS;
}

static void ShutDown(int sig_num)
{
    (void)sig_num;
    g_shut_down = 1;
}

static void DebugPrint(const char* format, ...)
{
    va_list args;
    const char* dp = getenv("DEBUG_PRINT");

    if (dp != NULL && *dp == '1')
    {
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
    }
}


int DoNotResuscitate(resources_t *resources)
{
    int i = MAX_ATTEMPT_TO_SEND_SIG2;
    struct timespec ts = {0};
    

    if(!AmIApp(resources->argv[0]))/*WD part*/
    {
        if(pthread_join(resources->thread, NULL))
        {
            return EXIT_FAILURE;
        }
        DebugPrint("controlled shutdown---\nIM %s and i got shutdown signal from %s\n", AmIApp(resources->argv[0]) ? "APP" : "WD", AmIApp(resources->argv[0]) ? "WD" : "APP");
        CleanUp(resources);
        DebugPrint("WD Completed controlled shutdown\n");
        return EXIT_SUCCESS;
    }
    
    g_shut_down = 1;
    DebugPrint("controlled shutdown---\nIM %s and i'm gonna shutdown %s\n", AmIApp(resources->argv[0]) ? "APP" : "WD", AmIApp(resources->argv[0]) ? "WD" : "APP");
    
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 10;
    while(i--)
    {
        kill(g_partner_pid, SIGUSR2);

        if(!(sem_timedwait(resources->child_is_ready, &ts)))
        {
            puts("bye bye\n");
            break;
        }
    }

    if(pthread_join(resources->thread, NULL))
    {
        return EXIT_FAILURE;
    }

    CleanUp(resources);
    DebugPrint("APP Completed controlled shutdown\n");
    return EXIT_SUCCESS;
}


















































