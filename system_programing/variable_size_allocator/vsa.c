/*********************************
 * Reviewer: 
 * Author: yisrael fisch
 * File Name: vsa.c
 * ******************************/

#include <assert.h> /* assert */
#include "vsa.h"


#define ALIGN_TO sizeof(size_t)
#define META_DATA ((size_t)(Align(sizeof(meta_data_t), ALIGN_TO)))
#define OFFSET ((size_t)(Align(sizeof(vsa_t), ALIGN_TO)))


static void *Defragmentation(vsa_t *vsa, size_t aligned_variable_size);
static void *Align(size_t what, size_t to);

struct vsa
{
    size_t act_pool_size;
};

typedef struct vsa_meta_data
{
    size_t next_block_data;
    #ifndef NDEBUG
    void *magic_num;
    #endif
}meta_data_t;



vsa_t *VSAInit(void *pool, size_t pool_size)
{
    vsa_t *vsa = NULL;
    meta_data_t *start_point = NULL;
        

    vsa = (vsa_t *)Align((size_t)pool, ALIGN_TO);
    start_point = (meta_data_t *)((char *)vsa + OFFSET);
    pool_size -= (char *)start_point - (char *)pool;
    pool_size = pool_size % ALIGN_TO ? ((size_t)Align(pool_size, ALIGN_TO) - ALIGN_TO) : pool_size;

    if((long)pool_size < (long)(META_DATA + ALIGN_TO))
    {
        return NULL;
    }
    
    vsa->act_pool_size = pool_size;
    start_point->next_block_data = pool_size - META_DATA;

    #ifndef NDEBUG
    start_point->magic_num = (void *)-1;
    #endif

    return vsa;
}

static void *Align(size_t what, size_t to)
{
    return (void *)((what - 1 + to) & -to);
}


void *VSAAlloc(vsa_t *vsa, size_t variable_size)
{
    size_t mask = 1;
    meta_data_t *tmp = NULL;
  
    size_t aligned_variable_size = (size_t)Align(variable_size, ALIGN_TO);
    tmp = Defragmentation(vsa, aligned_variable_size);

    if(!tmp)
    {
        return NULL;
    }

    if(tmp->next_block_data >= ALIGN_TO + aligned_variable_size + META_DATA)
    {
        ((meta_data_t *)((char *)tmp + META_DATA + aligned_variable_size))->next_block_data = tmp->next_block_data - META_DATA - aligned_variable_size; 
        #ifndef NDEBUG
        ((meta_data_t *)((char *)tmp + META_DATA + aligned_variable_size))->magic_num = (void *)-1;
        #endif

        tmp->next_block_data = aligned_variable_size | mask;

    }
    else
    {
        tmp->next_block_data = tmp->next_block_data | mask;
    }
        
    
    return (void *)((char *)tmp + META_DATA) ;

}



static void *Defragmentation(vsa_t *vsa, size_t aligned_variable_size)
{
    size_t mask = 1;
    meta_data_t *curr = (meta_data_t *)((char *)vsa + OFFSET);
    meta_data_t *next = (meta_data_t *)((char *)curr + META_DATA + (curr->next_block_data & ~mask));
    meta_data_t *end_of_pool = (meta_data_t *)((char *)curr + vsa->act_pool_size);

    while(next < end_of_pool && ((curr->next_block_data & mask) || curr->next_block_data < aligned_variable_size))
    {

        if(!(curr->next_block_data & mask) && !(next->next_block_data & mask))
        {
            curr->next_block_data += next->next_block_data + META_DATA;
        }
        else
        {
            curr = next;
            next = (meta_data_t *)((char *)curr + META_DATA + (curr->next_block_data & ~mask));
        }
    }
    
    if(next == end_of_pool && ((curr->next_block_data & mask) || curr->next_block_data < aligned_variable_size))
    {
        return NULL;
    }

    return (void *)(curr);    
}


size_t VSALargestChunckAvailable(vsa_t *vsa)
{
    size_t mask = 1;
    size_t largest = 0;
    meta_data_t *curr = (meta_data_t *)((char *)vsa + OFFSET);
    meta_data_t *next = (meta_data_t *)((char *)curr + META_DATA + (curr->next_block_data & ~mask));
    meta_data_t *end_of_pool = (meta_data_t *)((char *)curr + vsa->act_pool_size);
    meta_data_t *tmp = NULL;

    tmp = Defragmentation(vsa, vsa->act_pool_size - META_DATA);
    if(!tmp)
    {
        while(next < end_of_pool)
        {
            if(!(curr->next_block_data & mask) && curr->next_block_data > largest)
            {
                largest = curr->next_block_data;
            }

            curr = next;
            next = (meta_data_t *)((char *)curr + META_DATA + (curr->next_block_data & ~mask));
        }
    
        return largest < curr->next_block_data && !(curr->next_block_data & mask) ? curr->next_block_data : largest;
    }
  
    return tmp->next_block_data;
}



void VSAFree(void *block)
{
    size_t mask = 1;

    assert(((meta_data_t *)block - 1)->magic_num == (void *)-1);

    
    ((meta_data_t *)block - 1)->next_block_data = (((meta_data_t *)block - 1)->next_block_data) & ~mask;
   
}
