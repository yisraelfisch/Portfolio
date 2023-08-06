/*********************************
 * Reviewer: 				
 * Author: Yisrael Fisch			
 * File: priority_queue_on_heap_test.c				
 * ******************************/

#include "priority_queue.h" 
#include "heap.h"
#include "vector.h"

#include <stdlib.h> /*malloc, free*/
#include <stdio.h> /*printf*/
#include <string.h> /*strcpy*/
#include <strings.h> /*strcasecmp*/


typedef struct class
{
    char *surname_of_teacher;
    char *dep_name;
    unsigned int num_of_students;
    unsigned int class_num; 
} class_t;

int PriorityFuncClass(const void *data1, const void *data2, void *user_param)
{
    /*if (0 == strcasecmp(((class_t *)data1)->dep_name, ((class_t *)data2)->dep_name))
    {
        return ((class_t *)data2)->class_num - ((class_t *)data1)->class_num;
    }

    (void)user_param;

    return strcasecmp(((class_t *)data1)->dep_name, ((class_t *)data2)->dep_name);*/
    return ((class_t *)data1)->num_of_students < ((class_t *)data2)->num_of_students;
}

class_t *ClassCreate(char *surname_of_teacher, char *dep_name, 
                     unsigned int num_of_students, unsigned int class_num)
{
    class_t *new_class = NULL;
    new_class = (class_t *) malloc(sizeof(class_t));
    if (!new_class)
    {
        printf("Failed to allocate memory on ClassCreate\n");
        return NULL;
    }

    memset(new_class, 0, sizeof(class_t));

    new_class->num_of_students = num_of_students;
    new_class->surname_of_teacher = surname_of_teacher;
    new_class->dep_name = dep_name;
    new_class->class_num = class_num;

    return new_class;
}

void ClassDestroy(class_t *class)
{
    class->surname_of_teacher = NULL;
    class->dep_name = NULL;
    class->num_of_students = 0;
    class->class_num = 0;

    free(class);
}

pri_queue_t *TestCreate(PQcompare_t user_func, void *user_param)
{
    pri_queue_t *pq = PQueueCreate(user_func, user_param);

    return pq;
}

void TestEnqueue()
{
    pri_queue_t *pq = TestCreate(PriorityFuncClass, "param");
    class_t *class1 = ClassCreate("Nahmani", "ol", 13, 135);
    class_t *class2 = ClassCreate("Someone", "CYB", 17, 4);
    class_t *class3 = ClassCreate("Else", "Cyb", 5, 2);
    class_t *empty = NULL;

    ilrd_uid_t uid1 = UIDGetNull();
    ilrd_uid_t uid2 = UIDGetNull();

    if (!PQueueIsEmpty(pq))
    {
        printf("TestEnqueue failed (isEmpty)\n");
    }

    uid1 = PQueueEnQueue(pq, class1);
    uid2 = PQueueEnQueue(pq, class2);

    if (UIDIsSame(uid1, uid2))
    {
        printf("TestEnqueue failed (UIDIsSame)\n");
    }

    if (2 != PQueueSize(pq))
    {
        printf("TestEnqueue failed (size)\n");
    }

    empty = PQueuePeek(pq);

    if (strcasecmp(empty->surname_of_teacher, class1->surname_of_teacher))
    {
        printf("TestEnqueue failed (peek1)\n");
    }

    PQueueEnQueue(pq, class3);

    empty = PQueuePeek(pq);

    if (strcasecmp(empty->surname_of_teacher, class3->surname_of_teacher))
    {
        printf("TestEnqueue failed (peek2)\n");
    }

    PQueueDeQueue(pq);
    PQueueDeQueue(pq);

    empty = PQueuePeek(pq);

    if (strcasecmp(empty->surname_of_teacher, class2->surname_of_teacher))
    {
        printf("TestEnqueue failed (peek2)\n");
    }

    PQueueClear(pq);

    if (!PQueueIsEmpty(pq))
    {
        printf("TestEnqueue failed (clear)\n");
    }

    PQueueEnQueue(pq, class1);
    PQueueEnQueue(pq, class2);

    PQueueDestroy(pq);

    ClassDestroy(class1);
    ClassDestroy(class2);
    ClassDestroy(class3);
}

void TestErase()
{
    pri_queue_t *pq = TestCreate(PriorityFuncClass, "test2");
    class_t *class1 = ClassCreate("Avi", "ol", 12, 3);
    class_t *class2 = ClassCreate("Beni", "ol", 11, 7);
    class_t *class3 = ClassCreate("Gila", "il", 20, 10);
    class_t *class4 = ClassCreate("Dvora", "jam", 9, 100);
    class_t *empty = NULL;

    ilrd_uid_t uid1 = PQueueEnQueue(pq, class1);
    ilrd_uid_t uid2 = PQueueEnQueue(pq, class2);
    ilrd_uid_t uid3 = PQueueEnQueue(pq, class3);
    ilrd_uid_t uid4 = PQueueEnQueue(pq, class4);
    ilrd_uid_t uid_test = UIDGet();

    if (4 != PQueueSize(pq))
    {
        printf("TestErase failed (size)\n");
    }

    PQueueErase(pq, uid4);

    if (3 != PQueueSize(pq))
    {
        printf("TestErase failed (erase)\n");
    }

    PQueueErase(pq, uid_test);

    if (3 != PQueueSize(pq))
    {
        printf("TestErase failed (erase non existing uid)\n");
    }

    PQueueDeQueue(pq);

    empty = PQueuePeek(pq);

    if (strcasecmp(empty->surname_of_teacher, class1->surname_of_teacher))
    {
        printf("TestErase failed (peek)\n");
    }

    ClassDestroy(class1);
    ClassDestroy(class2);
    ClassDestroy(class3);
    ClassDestroy(class4);

    (void)uid1;
    (void)uid2;
    (void)uid3;

    PQueueDestroy(pq);
}

int main()
{
    TestEnqueue();
    TestErase();

    return 0;
}
