/*************************************** 
file name: 247.c
Author: yisrael fisch
*reviewer: 
******************************************/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "wd_lib.h"

#define TIME_TO_SLEEP 60

int main(int argc, char **argv)
{    
    resources_t *resources = NULL;
    int time_to_sleep = TIME_TO_SLEEP;

    if(!(resources = MakeMeImmortal(argc, argv)))
    {
        perror("MakeMeImmortal");
        return EXIT_FAILURE;
    }

    while(time_to_sleep)
    {
        time_to_sleep = sleep(time_to_sleep);
    }

    DoNotResuscitate(resources);

    return EXIT_SUCCESS;
}
