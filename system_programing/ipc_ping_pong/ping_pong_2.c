#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    // We use two pipes
    // First pipe to send input string from parent
    // Second pipe to send concatenated string from child
    char ping[] = "ping";
    char pong[] = "pong";
    int fd1[2];
    int fd2[2];
    pid_t pid;


    if (-1 == pipe(fd1))
    {
        perror("Pipe Failed");
        return 1;
    }
    if (-1 == pipe(fd2))
    {
        perror("Pipe Failed");
        return 1;
    }

    pid = fork();
 
    if (pid < 0)
    {
        perror("fork Failed");
        return 1;
    }

    if(pid)
    {
        while(1)
        {    
            char parent[15] = {'\0'};

            if(-1 == write(fd1[1], ping, strlen(ping) + 1))
            {
                perror("write failed");
            }

            if(-1 == read(fd2[0], parent, strlen(pong) + 1))
            {
                perror("read failed");
            }            
            printf("got %s message from child\n", parent);
            
        }
    }
    else
    {
        while(1)
        {
            char child[15] = {'\0'};
           
            if(-1 == read(fd1[0], child, strlen(ping) + 1))
            {
                perror("read failed");
            }            
            printf("got %s message from parent\n", child);
            if(-1 == write(fd2[1], pong, strlen(ping) + 1))
            {
                perror("write failed");
            }
        }

    }
    

}