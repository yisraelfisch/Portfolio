/*********************************
 * Reviewer:  Daniel.n
 * Author: yisrael fisch       
 * File: sll_exercises.h
 * ******************************/

#ifndef __SLL_EXERCISES_H__
#define __SLL_EXERCISES_H__

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

/* reverses the order of a given slist.*/
node_t *Flip(node_t *head);

/* tells whether a given slist has loop.*/
int HasLoop(const node_t *head);

/* returns a pointer to a first node mutual to both slists, if any.*/
node_t *FindIntersection(node_t *head_1, node_t *head_2);

#endif /* __SLL_EXERCISES_H__ */