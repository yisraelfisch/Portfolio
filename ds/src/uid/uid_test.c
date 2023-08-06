#include <stdio.h>/*printf*/
#include "uid.h"

int main ()
{
	int x;
	ilrd_uid_t check1 = UIDGet();
	/*sleep(2);*/
	ilrd_uid_t check2 = UIDGet();
	ilrd_uid_t badcheck = g_bad_uid;
	printf("count check1 is %lu\n", check1.count);
	printf("count check2 is %lu\n", check2.count);
	printf("time check1 is %lu\n", check1.time);
	printf("time check2 is %lu\n", check2.time);
	printf("pid check1 is %u\n", check1.pid);
	printf("pid check2 is %u\n", check2.pid);

	printf("count badcheck is %lu\n", badcheck.count);
	printf("time badcheck is %lu\n", badcheck.time);
	printf("pid badcheck is %u\n", badcheck.pid);
	
	x = UIDIsSame(check1, check1);
	printf("is same = %d\n", x);
	return 0;
}
