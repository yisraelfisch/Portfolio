#define _DEFAULT_SOURCE
#include <stdio.h>   /*printf*/
#include <unistd.h>   /*pid_t*/
#include <signal.h>   /*sigaction, kill*/
#include <sys/wait.h> /*wait*/



static void Sigusr1Handler(int signum);
static void Sigusr2Handler(int signum);
volatile int child_flag = 0;
volatile int parent_flag = 1;


int main()
{
    char *file[2] = {"ping_pong_3.Debug.out", NULL};
    pid_t child_pid = 0;
    struct sigaction sig1 ;
    struct sigaction sig2 ;

    sig1.sa_handler = Sigusr1Handler;
    sig2.sa_handler = Sigusr2Handler;

    sigaction(SIGUSR1, &sig1, NULL);
    sigaction(SIGUSR2, &sig2, NULL);

    child_pid = fork();

    while(1)
    {
        if (0 == child_pid) /* child process created*/
        {
            execvp(file[0], file);   
        }
        else
        {
            while (!parent_flag);
            parent_flag = 0;
            printf("parent SIGUSR2 pong!\n");
            kill(child_pid, SIGUSR1);
        }

    }
}

static void Sigusr1Handler(int signum)
{
    (void)signum;
    child_flag = 1;
  
}

static void Sigusr2Handler(int signum)
{
    (void)signum;
    parent_flag = 1;
    
}