/*********************************
 * Reviewer:  Daniel.n
 * Author: yisrael fisch       
 * File: sll_exercises.c
 * ******************************/
 #include <stddef.h>/*NULL*/
 #include <assert.h>
 #include "sll_exercises.h"

/*count the number of nodes in a SLL*/
 static size_t SLLCount(node_t *head)
 {
    size_t counter = 0;
    assert(head);

    while(NULL != head)
    {
        ++counter;
        head = head->next;
    }

    return counter;
 }

 node_t *Flip(node_t *head)
 {
    node_t *prev = NULL;
    node_t *curr = head;
    node_t *next = NULL;
    assert(head);

    while(NULL !=curr)
    {

    next = curr->next;
    curr->next = prev;

    prev = curr;
    curr = next;

    }
    

    return prev;
 } 

 int HasLoop(const node_t *head)
 {
    node_t *curr = (node_t *)head;
    node_t *next_node = (node_t *)head;
    
    assert(head);

    while(NULL != curr && NULL != next_node && NULL != next_node->next)
    {
        curr = curr->next;
        next_node = next_node->next->next;

        if(curr == next_node)
        {
            return 1;
        }
    }
    return 0;

 }

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
    node_t *big = head_1;
    node_t *small = head_2;
    /*count the size of both SLLs*/
    size_t counter1 = SLLCount(head_1);
    size_t counter2 = SLLCount(head_2);
    size_t difference = 0;
    assert(head_1);
    assert(head_2);

    /*find if one SLL is bigger*/
    if(counter1 > counter2)
    {
        difference = counter1 - counter2;
    }
    else
    { 
        difference = counter2 - counter1;
        big = head_2;
        small = head_1;
    }
    /*moves the bigger SLL forword to equal to the short SLL*/
    while(difference)
    {
        big = big->next;
        --difference;
    }

    /*check if node are equal*/
    while(NULL != big && NULL != small)
    {
        if(big == small)
        {
            return big;
        }
        big = big->next;
        small = small->next;
    }

    return NULL;
}
