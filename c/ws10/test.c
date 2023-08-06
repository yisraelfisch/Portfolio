#include <stdio.h>
#include "wbo.h"
int main ()
{
char test = 'a';
char arr[20] = "yisraelfischruls";
char arr1[20] = {"source test"};
char arr2[20] = {"destanetion"};
size_t num = 6;

MemSet(arr, test, num);
printf("%s\n", arr);

MeMcpy(arr2, arr1, num);
printf("%s\n", arr2);

MemMove((arr2+1),arr2,  num);
printf("%s\n", arr2);

return 0;
}