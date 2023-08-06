/*************************************** 
file name: exercise2.c
Author: yisrael fisch
*reviewer: daniel.b.
******************************************/
#include <stdio.h> /*printf, fprintf, fgets, getc*/
#include <string.h>
#include <stdlib.h>

enum returns {stop, keep, error};


 int RemoveFile(const char *filename, char *str2)
 {
 	if(-1 == remove(filename))
 	{
 	 	printf("error remove file");
 	}
 	return keep;
 }

/*print the number of lines in a file*/
 int PrintFileLines(const char *filename, char *str2)
 {
 	int count = 0;
 	char c;
	FILE *file = fopen(filename, "r");
 
    if (file == NULL)
    {
        printf("error open file");
        return keep;
    }
 
  
    for (c = getc(file); c != EOF; c = getc(file))
    if ('\n' == c)
    { 
        count = count + 1;
	} 
    fclose(file);
    printf("The file has %d lines\n ", count);
    return keep;
 }

 int ExitProgram(const char *filename, char *str2)
 {
 	return stop;
 }

/*print words from the user to the head of a file*/
 int AddToTopFile(const char *filename, char *str2)
 {
 	char ch = 0;
 	FILE *temp_file = fopen("temp.txt", "w+");
  	FILE *file = fopen(filename, "r+");
 
    if (file == NULL)
    {
        printf("error open file");
        return keep;
    }
    if (temp_file == NULL)
    {
        printf("error open temp file");
        return keep;
    }
	while (EOF!=(ch=fgetc(file)))
	{
		fputc(ch,temp_file);
	}
	if(0!=fseek(file,0,SEEK_SET))
	{
		printf("Can't fseek file!");
		return keep;
	}
	if(0!=fseek(temp_file,0,SEEK_SET))
	{
		printf("Can't fseek temp file!");
		return keep;
	}
	if(fprintf(file, "%s\n",(str2+1)) < 0)
	{
		printf("Can't fprintf");
		return keep;
	}
	while (EOF!=(ch=fgetc(temp_file)))
	{
		fputc(ch,file);
	}
  
    if(fclose(file))
	{
		printf("error close file");
		return keep;
	}
	 if(fclose(temp_file))
	{
		printf("error close temp file");
		return keep;
	}
    return keep;
 }

/*basic struct for the array*/
typedef struct
{
	char *command;
	int(*fun_cmp)();
	int(*fun_oper)();
}print_me;

/*print words from the user to the end of a file*/
int printtofile(const char *f,char *input)
{
	FILE *file = fopen(f, "a+");
	if(NULL == file)
	{
		printf("error open");
	}
	fprintf(file,"%s\n",input);

	if(fclose(file))
	{
		printf("error close");
	}
	return keep;
}

int ReturnZero(const char *filename, char *str2)
{
	return 0;
}

/*initiate every struct in the array of structs*/
void InitArray(print_me arr[])
{
	arr[0].command = "-remove";
	arr[0].fun_cmp = strncmp;
	arr[0].fun_oper = RemoveFile;

	arr[1].command = "-count";
	arr[1].fun_cmp = strncmp;
	arr[1].fun_oper = PrintFileLines;

	arr[2].command = "<";
	arr[2].fun_cmp = strncmp;
	arr[2].fun_oper = AddToTopFile;

	arr[3].command = "-exit";
	arr[3].fun_cmp = strncmp;
	arr[3].fun_oper = ExitProgram;

	arr[4].command = "-print";
	arr[4].fun_cmp = ReturnZero;
	arr[4].fun_oper = printtofile;	
}



int main(int argc, char *argv[])
{
	int  state = keep;
	int i = 0;
	char *my_file = argv[1];
	char sinput[100];
	print_me arr[5];

	InitArray(arr);
	
		while(keep == state)
		{	
			printf("enter your string: ");
			fgets(sinput, 100, stdin);
			if('\n' == sinput[strlen(sinput)-1])
			{
				sinput[strlen(sinput)-1] = '\0';
			}
			
	
			i = 0;
			while(5 != i)
			{
			
				if(0 == arr[i].fun_cmp(arr[i].command, sinput, strlen(arr[i].command)))
				{
					state = arr[i].fun_oper(my_file, sinput);
					break;
				}			
				++i;
			}
		}	
return stop;
}
