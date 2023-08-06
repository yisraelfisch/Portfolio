/* A function that return sum of rows of a matrix*/
/* Author: yisrael fisch*/
/*reviewer: roy*/
#include <stdio.h>

void SumOfRowes(int *arr, int rows, int column, int *Sumofrows)
{
	int sum =0;
    int i = 0, j = 0;

    for (i = 0; i < rows; i++)
    {
      for (j = 0; j < column; j++)
      {	
      sum = sum + *((arr+i*column)+j);
  	  }
  	  *(Sumofrows + i) = sum;
      sum = 0;
    }
}

int main ()
{
int i =0;
int array[3][2] = {{1,2}, {3,4}, {5,6}};
int sum[3] = 0;

SumOfRowes((int *)array, 3, 2, sum);

for (i = 0; i< 3; ++i)
	{
		printf(" sum of row %d is:%d\n",(i+1), *(sum+i) );
	}
return 0;


}