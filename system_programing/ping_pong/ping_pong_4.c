#define _DEFAULT_SOURCE
#include <stdio.h>   /*printf*/
#include <unistd.h>   /*pid_t*/
#include <signal.h>   /*sigaction, kill*/
#include <sys/wait.h> /*wait*/

volatile int child_flag = 1;
volatile int parent_flag = 0;
pid_t child_pid = 0;

static void Sigusr1Handler(int signum);
static void Sigusr2Handler(int signum, siginfo_t *siginfo, void *context);


int main()
{
    
    struct sigaction sig1 ;
    struct sigaction sig2 ;

    sig1.sa_handler = Sigusr1Handler;
    /*in order to get info you need to build another func and
     assign it in sa_sigaction insted of sig2.sa_handler = Sigusr2Handler;*/
    sig2.sa_sigaction = Sigusr2Handler;
    sig2.sa_flags = SA_SIGINFO;


    sigaction(SIGUSR1, &sig1, NULL);
    sigaction(SIGUSR2, &sig2, NULL);


    ("parent PID is: %d\n", getpid());

    while(1)
    {
        
        while (!parent_flag);
        parent_flag = 0;
        printf("parent SIGUSR2 pong!\n");
        kill(child_pid, SIGUSR1);
       
    }
}

static void Sigusr1Handler(int signum)
{
    (void)signum;
    child_flag = 1;
  
}

static void Sigusr2Handler(int signum, siginfo_t *siginfo, void *context)
{
    (void)context;
    (void)signum;
    child_pid = siginfo->si_pid;
    parent_flag = 1;
    
}