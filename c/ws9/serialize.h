/*************************************** 
file name: serialize.c
Author: yisrael fisch
*reviewer: daniel.b.
******************************************/
#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__
enum exits_status
{
	SUCCESS,
	ERR_OPEN,
	ERR_CLOSE,
	ERR_WRITE,
	ERR_READ
};
typedef struct humanistic_grades
{
	float sociology;
	float psychology;
	float literature;
}humanistic_t;

typedef struct real_grades
{
	float physics;
	float math;
}real_t;

typedef struct student_grades
{
humanistic_t humanistic_grade;
real_t real_grade;	
float sports;
}grades_t;

typedef struct std_grade
{
	char first_name[20];
	char last_name[20];
 	grades_t student;
}student_t;

int StudentWrite(student_t *std, char *filename);
int Studentread(student_t *std, char *filename);
#endif /* __SERIALIZE_H_ */