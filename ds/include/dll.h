/*********************************
 * Reviewer: roy mantel
 * Author: yisrael fisch       
 * File: dll.h
 * ******************************/

#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h>/*size_t*/

typedef struct dll dll_t;
typedef struct dll_node *dll_iterator_t;

typedef int(*action_func_t)(void *list_data, void *param);
typedef int(*is_match_t)(const void *list_data, const void *data);

/* description: creates new doubly linked list 
   params: 
   return value: ptr to head node or NULL if failed
   O(1)  */  
dll_t *DListCreate(void);

/* description: destroys doubly linked list 
   params: ptr to dll
   undefined behavior:
   O(n) */  
void DListDestroy(dll_t *dlist);

/* description: gives the current size of the doubly linked list 
   params: ptr to dll
   return value: size_t size of the list
   undefined behavior:
   O(n) */
size_t DListSize(const dll_t * dlist);

/* description:tells rather the doubly linked list is empty or not 
   params: ptr to dll
   return value: 1 if empty 0 if not
   undefined behavior:
   O(1) */
int DListIsEmpty(const dll_t *dlist);

/* description: returns the head 
   params: ptr to dll
   return value: dll_iterator with head node in case the list is empty returns
   the tail node
   undefined behavior:
   O(1)  */ 
dll_iterator_t DListBegin(const dll_t *dlist);

/* description: returns the tail
   params: ptr to dll
   return value: dll_iterator with tail node
   undefined behavior: 
   O(1) */ 
dll_iterator_t DListEnd(const dll_t *dlist);

/* description: returns the next node 
   params: dll_iterator
   return value: sll_iterator with next node
   undefined behavior: if it is the End node
   O(1)  */ 
dll_iterator_t DListNext(const dll_iterator_t curr);

/* description: returns the previous node 
   params: dll_iterator
   return value: sll_iterator with previous node
   undefined behavior: if it is the head node
   O(1)  */ 
dll_iterator_t DListPrev(const dll_iterator_t curr);

/* description: compers bitween 2 iterators  
   params:2 dll_iterator  
   return value: 1 if equal 0 if not
   undefined behavior: if it is the end or the list is empty
   O(1)  */ 
int DListIsSameIter(dll_iterator_t first, dll_iterator_t second);

/* description: returns the void pointer with the value of the curr node
   params: dll iterator
   return value: void pointer with value of the curr node
   undefined behavior: if it the End
   O(1) */ 
void* DListGetData(dll_iterator_t curr );

/* description: creates new node in the list before the head 
   params: ptr to dll, void *data of the new node
   return value: dll_iterator to inserted node if sucsses, end node if fails
   undefined behavior: 
   complexity: O(1)*/ 
dll_iterator_t DListPushFront(dll_t *dlist, void *data);

/* description: creates new node in the list at the end 
   params: ptr to dll, void *data of the new node
   return value: dll_iterator to inserted node if sucsses, end node if fails
   undefined behavior: 
   complexity: O(1)*/ 
dll_iterator_t DListPushBack(dll_t *dlist, void *data);

/* description: returns the void pointer with the value of the head node 
   end delete the current head node 
   params: ptr to dll
   return value: void pointer with the value of the head node
   undefined behavior: if it the dll is empty
   O(1) */ 
void *DListPopFront(dll_t *dlist);

/* description: returns void pointer with the value of the value of the end node
   end delete the current end node
   params: ptr to dll
   return value: void pointer with the value of the value of the end node
   undefined behavior: if it the dll is empty
   O(1) */ 
void *DListPopBack(dll_t *dlist);

/* description: creates new node in the list before the current 
   params: iterator, void *data of the new node
   return value: dll_iterator to inserted node if sucsses, end node if fails
   undefined behavior: 
   complexity: O(1)*/

dll_iterator_t  DListInsert(dll_t *dlist, dll_iterator_t curr, void *data);

/* description: remove the curr element 
   params: dll iterator
   return value: next elemnt if sucsses
   undefined behavior: if the current node is the tail.
   complexity: O(1)*/
dll_iterator_t DListRemove(dll_iterator_t curr);

/* description: change the reference of range of elements
   from begin to end(end not included)to the where destination
   params: ptr to where node, pointer to begin node and pointer to end node 
   return value: iterator to the node before destination
   complexity: O(1) */
dll_iterator_t DListSplice
(dll_iterator_t where, dll_iterator_t begin, dll_iterator_t end); 

/* description: implements the func on node from till to (not included)
   params: ptr to the start node,ptr to the end node, and ptr to the function, void pointer to param
   return value: 0 in case of success, none-zero in case of failure 
   action function returns 0 in case of success and none-zero in case of failure
   undefined behavior: if you cant implement the function on the nodes, if the end node does not exist
   O(n)*/  
int DListForEach
(dll_iterator_t from, dll_iterator_t to,
 void *param, action_func_t func);

/* description: search for a node, Start at from till to (not included)
   stops when findes the node.
   params: dll_iterator from, dll_iterator to , ptr to comper function, void pointer to data
   return value: dll_iterator of the found node in case of success and dll_iterator to if fails. 
   Match func returns 0 if matches and 1 otherwise
   undefined behavior: if the end node does not exict
   O(n) */  
dll_iterator_t DListFind
(dll_iterator_t from, dll_iterator_t to,
 const void *data, is_match_t func); 

/* description: searches for a match node in a range Starts at from till to (not included) 
   copy all matches nodes to a the user's dll list
   params: dll_iterator from, dll_iterator to , ptr to compare function, ptr to dll list
   void pointer to data
   return value: 0 in case of success 1 in case of no match or failur. 
   Match func returns 0 if matches and 1 otherwise
   undefined behavior: 
   complexity: O(n) */
int DListMultiFind
(dll_iterator_t from, dll_iterator_t to, dll_t *dlist_dest,
 const void *data, is_match_t func);

#endif/* __DLL_H__ */