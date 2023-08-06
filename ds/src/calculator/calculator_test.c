
#include<stdio.h>
#include<stdlib.h>
#include"calculator.h"

int main()
{
    char *str = "1/5";
    double num = 0;

    num = Calculate(str);

    printf ("%f\n", num);

    return 0;
}