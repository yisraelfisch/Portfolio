/*********************************
 * Reviewer: 
 * Author: yisrael fisch       
 * File: uid.c
 * ******************************/

#include <sys/types.h>/*time_t*, pid_t, size_t, getpid*/
#include <unistd.h>/*getpid*/
#include <time.h>/*time*/
#include "uid.h"


const ilrd_uid_t g_bad_uid = {-1,-1, -1};

ilrd_uid_t UIDGet(void)
{
	static size_t counter = 0;
	ilrd_uid_t new_UID;
	++counter;
	new_UID.count = counter; 
	new_UID.time = time(NULL);
   	new_UID.pid = getpid();
 
 	return new_UID;
}

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	return (uid1.count == uid2.count && uid1.time == uid2.time && uid1.pid == uid2.pid) ;
}

ilrd_uid_t UIDGetNull()
{
	ilrd_uid_t uid = {0 ,0, 0};
	return uid;
}