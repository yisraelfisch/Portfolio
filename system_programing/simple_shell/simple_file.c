#include <stdio.h>/*fgets, perorr*/
#include <string.h>/*strcmp, strlen*/
#include <stdlib.h>/*exit*/
#include <unistd.h> /*fork*/
#include <sys/wait.h> /*wait*/


int main()
{
    int i = 0;
    int pid = 0;
    int execflag = 0;
    char *command[10] = {0};
    char buff[256] = {0};
    while(1)
    {
        printf("yisrael@thegreat:~/git/system_programing/simple_shell$ ");
        fgets(buff, 256, stdin);
        buff[strlen(buff) - 1] = '\0';/*insert \0 insted of \n (enter)*/
        if(0 == (strcmp(buff,"exit")))
        {
           exit(1);
        }
        
        pid = fork();

        if(pid == 0 )
        {
            printf("im child\n");
            command[i] = strtok(buff, " ");
            while(command[i])
            {
                ++i;
                command[i] = strtok(NULL, " ");
            }
            command[i] = NULL;
            
            execflag = execvp(command[0], command);
            perror("execvp");
            exit(1);
        }
        else
        {
            sleep(15);
            printf("im perent\n");
            wait(&execflag);

        } 
    }
}


/*int main()
{

    int pid = 0;
    int execflag = 0;
    char buff[1024] = {0};
    while(1)
    {
        scanf("%s", buff);
        
        if(0 == (strcmp(buff,"exit")))
        {
           exit(1);
        }

        pid = fork();

        if(pid != 0 )
        {
            wait(&execflag);
        }
        else
        {
            execflag = execlp(buff, buff, NULL);

        } 
    }
}*/