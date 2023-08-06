#include <pthread.h>/*pthread_ create*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *prod(void *param);
void *cons(void *param);

int buff = 0;
volatile int is_ready = 1;


int main()
{
    pthread_t thread1 = 0;
    pthread_t thread2 = 0;

    void *ret_val1 = NULL;
    void *ret_val2 = NULL;
    if(pthread_create(&thread1, NULL, prod, NULL))
    {
        puts("pthread_create faild");
        return 1;
    }

    if(pthread_create(&thread2, NULL, cons, NULL))
    {
        puts("pthread_create faild");
        return 1;
    }

    if(0 != (pthread_join(thread1, &ret_val1)))
    {
        puts("pthread_join faild");
        return 1;
    }

    if(0 != (pthread_join(thread1, &ret_val2)))
    {
        puts("pthread_join faild");
        return 1;
    }
    
    return 0;
}

void *prod(void *param)
{
    int temp = 0;
    
    (void)param;

    while(1)
    {
        
        while (__atomic_load_n(&is_ready, __ATOMIC_SEQ_CST) == 0);
        
        buff = 1;
        printf("%d\n", buff);
         __atomic_store (&is_ready, &temp, __ATOMIC_SEQ_CST);
        
    }
    return NULL;
}

void *cons(void *param)
{
    int temp = 1;
    
    (void)param;

    while(1)
    {
        
        while (__atomic_load_n(&is_ready, __ATOMIC_SEQ_CST) == 1);
        
        buff = 2;
        printf("%d\n", buff);
        __atomic_store (&is_ready, &temp, __ATOMIC_SEQ_CST);    
        
    }
    return NULL;
}
