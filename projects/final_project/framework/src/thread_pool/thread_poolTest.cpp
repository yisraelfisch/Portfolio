/*********************************
 * Reviewer: 
 * Author: yisrael fisch
 * File: thread_poolTest.cpp
 * ******************************/
#include <iostream>
#include <unistd.h>
#include <cstdio> 
#include "thread_pool.hpp"

const int NUMBER = 20;
int print = 0;
int ExampleFunc(int num)
{
    print +=num;    
    printf("yisrael %d\n", num);
    return 1;
}

using namespace ilrd;
int main()
{
    ThreadPool pool(10);
    for(int i = 0; i < NUMBER; ++i)
    {
        Function<int(void)> f1(ExampleFunc, i+1);
        pool.Async(f1);
    }

    /* sleep(2); */

   /*  while(1)
    {

    } */
    /* pool.Cancel(); */
    pool.ShutDown();
    std::cout << print << std::endl;

    
    return 0;
}