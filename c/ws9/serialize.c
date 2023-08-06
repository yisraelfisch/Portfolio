/*************************************** 
file name: serialize.c
Author: yisrael fisch
*reviewer: daniel.b.
******************************************/
#include <stdio.h>/*fopen,fclose*/
#include<string.h>/*strlen*/
#include "serialize.h"
static int WriteString(const char *str, FILE *file);
static int WriteGrades(grades_t *grades, FILE* file);
static int WriteHuminstic(humanistic_t *grades, FILE* file);
static int WriteReal(real_t *grades, FILE* file);
static int WriteFloat(float num, FILE *file);

static int ReadString(char *str, FILE *file);
static int ReadGrades(grades_t *grades, FILE* file);
static int ReadHuminstic(humanistic_t *grades, FILE* file);
static int ReadReal(real_t *grades, FILE* file);
static int ReadFloat(float *num, FILE *file);

static int WriteString(const char *str, FILE *file)
{
	/* write the str len to the file
	 write the str*/
	int len = strlen(str);
	if(1 != fwrite(&len,sizeof(int), 1, file))
		{
			return ERR_WRITE;
		}
	if(1 != fwrite(str,len,1,file))
		{
			return ERR_WRITE;
		}
	return SUCCESS;
}

static int WriteGrades(grades_t *grades, FILE* file)
{
	WriteHuminstic(&grades->humanistic_grade, file);
	WriteReal(&grades->real_grade, file);
	WriteFloat(grades->sports, file);
	return SUCCESS;
}

static int WriteHuminstic(humanistic_t *grades, FILE* file)
{
	WriteFloat(grades->sociology, file);
	WriteFloat(grades->psychology, file);
	WriteFloat(grades->literature, file);
	return SUCCESS;
}

static int WriteReal(real_t *grades, FILE* file)
{
	WriteFloat(grades->physics, file);
	WriteFloat(grades->math, file);
	return SUCCESS;
}

static int WriteFloat(float num, FILE *file)
{
	/* write float to file*/
	if(1 != fwrite(&num,sizeof(float),1,file))
	{
		return ERR_WRITE;
	}
	return SUCCESS;
}

int StudentWrite(student_t *std, char *filename)
{
	
	FILE *file = fopen(filename, "wb");
	if(file == NULL)
	{
		return ERR_OPEN;
	}

	WriteString(std->first_name, file);
	WriteString(std->last_name, file);
	WriteGrades(&std->student, file);

	if(fclose(file))
	{
		return ERR_CLOSE;
	}
	return SUCCESS;	
}

static int ReadString(char *str, FILE *file)
{
/*read int
read string*/
	int len;
	if(1 != fread(&len, sizeof(int),1,file))
		{
			return ERR_READ;
		}
	if(1 !=fread(str, len,1,file))
	{
		return ERR_READ;
	}
	return SUCCESS;
}

static int ReadGrades(grades_t *grades, FILE* file)
{
	ReadHuminstic(&grades->humanistic_grade, file);
	ReadReal(&grades->real_grade, file);
	ReadFloat(&grades->sports, file);
	return SUCCESS;	
}

static int ReadHuminstic(humanistic_t *grades, FILE* file)
{
	ReadFloat(&grades->sociology, file);
	ReadFloat(&grades->psychology, file);
	ReadFloat(&grades->literature, file);
	return SUCCESS;

}

static int ReadReal(real_t *grades, FILE* file)
{
	ReadFloat(&grades->physics, file);
	ReadFloat(&grades->math, file);
	return SUCCESS;
}

static int ReadFloat(float *num, FILE *file)
{
/*read float from file to struct*/
	if(1 != fread(num, sizeof(float),1,file))
	{
		return ERR_READ;
	}
	return SUCCESS;
}
int Studentread(student_t *std, char *filename)
{
FILE *file = fopen(filename, "rb");
	if(file == NULL)
	{
		return ERR_OPEN;
	}

	ReadString(std->first_name, file);
	ReadString(std->last_name, file);
	ReadGrades(&std->student, file);

	if(fclose(file))
	{
		return ERR_CLOSE;
	}
	return SUCCESS;	
}