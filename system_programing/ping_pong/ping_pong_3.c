#define _DEFAULT_SOURCE
#include <stdio.h>   /*printf*/
#include <unistd.h>   /*pid_t*/
#include <signal.h>   /*sigaction, kill*/
#include <sys/wait.h> /*wait*/



static void Sigusr1Handler(int signum);
static void Sigusr2Handler(int signum);
volatile int child_flag = 1;
volatile int parent_flag = 0;


int main()
{
    pid_t child_pid = 0;
    struct sigaction sig1 ;
    struct sigaction sig2 ;

    sig1.sa_handler = Sigusr1Handler;
    sig2.sa_handler = Sigusr2Handler;

    sigaction(SIGUSR1, &sig1, NULL);/*During an execve(2), the dispositions  of  handled  signals
       are  reset to the default;*/


    while(1)
    {
        if (0 == child_pid) /* child process created*/
        {
            while (!child_flag);
            printf("child SIGUSR1 ping!\n");
            child_flag = 0;
            kill(getppid(), SIGUSR2);
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