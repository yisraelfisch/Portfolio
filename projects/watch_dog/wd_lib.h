/*************************************** 
file name: wd_lib.h
Author: yisrael fisch
*reviewer: 
******************************************/

#ifndef __WD_LIB_H__
#define __WD_LIB_H__

typedef struct resources resources_t;

resources_t *MakeMeImmortal(int argc, char **argv);
int DoNotResuscitate(resources_t *resources);

#endif /*__WD_LIB_H__*/