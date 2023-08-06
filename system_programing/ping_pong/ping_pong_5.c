#define _DEFAULT_SOURCE

#include <stdio.h>   /*printf*/
#include <unistd.h>   /*pid_t*/
#include <signal.h>   /*sigaction, kill*/
#include <stdlib.h>    /* atoi*/
#include <sys/wait.h> /*wait*/

static void Sigusr1Handler(int signum);
static void Sigusr2Handler(int signum);

volatile int child_flag = 1;
volatile int parent_flag = 0;


int main(int argc, char **argv)
{
    struct sigaction sig1 ;
    struct sigaction sig2 ;
    
    pid_t child_pid = 0;
    pid_t parent_pid = 0;
    parent_pid = atoi(argv[1]);

    sig1.sa_handler = Sigusr1Handler;
    sig2.sa_handler = Sigusr2Handler;

    sigaction(SIGUSR1, &sig1, NULL);
    


    while(1)
    {    
        while (!child_flag);
        printf("child SIGUSR1 ping!\n");
        child_flag = 0;
        kill(parent_pid, SIGUSR2);          
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
