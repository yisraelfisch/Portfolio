#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void Swap(char* a, char * b)
{
    char temp = '\n';
    temp = *a;
    *a = *b;
    *b = temp;
}

void ReverseString(char *str)
{
    size_t start = 0;
    size_t end = strlen(str) -1;

    for(start = 0; start <= end; ++start, --end)
    {
        str[start] = tolower(str[start]);
        str[end]   = tolower(str[end]);
        Swap(&str[start], &str[end]);
    } 
}


int main()
{
    
    char test[] = "HelLo wORLd";
    printf("%s\n", test);
    ReverseString(test);
    printf("%s\n", test);
    return 0;
}