#include <semaphore.h> /*sem_init, sem_wait, sem_post, sem_getvalue*/
#include <fcntl.h> /**/
#include <stdio.h> /*fgets, printf, puts*/
#include <string.h>/*strtok*/
#include <stdlib.h> /*atoi*/

#define SIZE 256
sem_t sem_name = {0};

int main()
{
    char buff[SIZE]= {0};
    char *operation = '\0';
    char *num = '\0';
    int number = 0;
    int i = 0;
    int sem_value = 0;
    
    if(sem_init(&sem_name, 0, 0))
    {
        puts("init failed");
        return -1; 
    }
    
    while(1)
    { 
        fgets(buff, SIZE, stdin);
        buff[strlen(buff) - 1] = '\0';/*insert \0 insted of \n (enter)*/
        operation = strtok(buff, " ");
        if(*operation == 'I' || *operation == 'D')
        {
            num = strtok(NULL, " ");
            number = atoi(num);
        }

        switch (*operation)
        {
        case 'D': 
                  for(i = 0; i < number; ++i)
                    {
                        sem_trywait(&sem_name);
                    }
        break;

        case 'I':
                    for( i = 0; i < number; ++i)
                    {
                       int err = sem_post(&sem_name);
                       if(err != 0)
                       {
                        printf("error: %d\n", err);
                       }
                    }
            break;
    
        case 'V':
                    sem_getvalue(&sem_name, &sem_value);
                    printf("value is %d\n", sem_value);
            break;
    
        case 'X':
            sem_destroy(&sem_name);
            exit(0);


            break;
    
    
        default: printf("try another command");

            break;
        }

    }
    return 0;
}