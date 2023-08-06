/* A program to print data types*/
/* Author: yisrael fisch*/
/*reviewer: roy*/
#include <stdio.h>

int main () 
{
  printf("char %lu\n", sizeof(char));

  printf("int %lu\n", sizeof(int));

  printf("long int %lu\n", sizeof(long int));

  printf("float %lu\n", sizeof(float));

  printf("double %lu\n", sizeof(double));

  printf("long double %lu\n", sizeof(long double));

  printf("char* %lu\n", sizeof(char*));

  printf("char** %lu\n", sizeof(char**));

  printf("int* %lu\n", sizeof(int*));

  printf("int** %lu\n", sizeof(int**));

  printf("int*** %lu\n", sizeof(int***));

return 0;
}