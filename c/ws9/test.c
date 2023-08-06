#include "serialize.h"
#include <stdio.h>
int main()
{
	student_t student1 = {"yisrael", "fisch",{{75.5,85,100},{80,90},100}};
	student_t student_new;
	StudentWrite(&student1, "hello");
	Studentread(&student_new, "hello");
	printf("first name is:%s\n",student_new.first_name);
	printf("first name is:%s\n",student_new.last_name);
	printf("sport is:%.2f\n",student_new.student.sports);
	printf("sociology is:%.2f\n",student_new.student.humanistic_grade.sociology);
	printf("psychologyis:%.2f\n",student_new.student.humanistic_grade.psychology);
	printf("literature is:%.2f\n",student_new.student.humanistic_grade.literature);
	printf("physics is:%.2f\n",student_new.student.real_grade.physics);
	printf("math is:%.2f\n",student_new.student.real_grade.math);	

	return 0;
}