/*************************************** 
file name: wd.c
Author: yisrael fisch
*reviewer: 
******************************************/

#define _DEFAULT_SOURCE
/*#define _POSIX_C_SOURCE 200112L*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "wd_lib.h"

int main(int argc, char **argv)
{
    resources_t *resources = NULL;

    if(!(resources = MakeMeImmortal(argc, argv)))
    {
        perror("MakeMeImmortal");
        return EXIT_FAILURE;
    }

    DoNotResuscitate(resources);
    
    return EXIT_SUCCESS;
}