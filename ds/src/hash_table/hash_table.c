/*********************************
* Reviewer: shani
 * Author: yisrael fisch 
 * File Name: hash_table.c
 * ******************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /*assert*/
#include "dll.h"
#include "hash_table.h"

struct hash
{
    hash_is_match_t is_match_func;
    hash_func_t hash_func;
    size_t table_size;
    dll_t *table[1];    
};

static void FreeLists(hash_t *table, size_t end);
static dll_iterator_t FindDLIterator(hash_t *hash, void *data);

hash_t *HashCreate(hash_is_match_t is_match_func,
                    hash_func_t hash_func,size_t table_size)
{
    hash_t *hash = NULL;
    dll_t *list = NULL;
    size_t index = 0;

    assert(is_match_func);
    assert(hash_func);

    hash = malloc(sizeof(hash_t) + ((table_size - 1) * sizeof(dll_t *)));
    if(!hash)
    {
        return NULL;
    }

    for(index = 0; index < table_size; ++index)
    {
       list = DListCreate();
        hash->table[index] = list;

        if(!list)
        {
            FreeLists(hash, index);
            hash->is_match_func = NULL;
            hash->hash_func = NULL;
            free(hash);
            hash = NULL;
            return NULL;
        }
    }

    hash->is_match_func = is_match_func;
    hash->hash_func = hash_func;
    hash->table_size = table_size;

    return hash;
}

void HashDestroy(hash_t *hash)
{
    assert(hash);

    FreeLists(hash, hash->table_size);
    hash->is_match_func = NULL;
    hash->hash_func = NULL;
    free(hash);
    hash = NULL;

}

size_t HashSize(hash_t *hash)
{
        size_t index = 0;
        size_t size = 0;
        
        assert(hash);

        for (index = 0; index < hash->table_size; index++)
        {
            size += DListSize(hash->table[index]);
        }

        return size;    

}

int HashIsEmpty(hash_t *hash)
{
    size_t index = 0; 
    assert(hash);

        for (index = 0; index < hash->table_size; index++)
        {
            if(!DListIsEmpty(hash->table[index]))
            {
                return 0;
            }
        }

        return 1;    
}

int HashInsert(hash_t *hash, const void *data)
{
    size_t index = 0;
    dll_t *list = NULL;

    assert(hash);
    assert(data);

    index = hash->hash_func((void *)data) % hash->table_size;
    list = hash->table[index];

    if(DListIsSameIter(DListEnd(list), DListPushFront(list, (void *)data)))
    {
        return 1;
    }

    return 0;

}

void HashRemove(hash_t *hash, void *data)
{

    dll_iterator_t iter= NULL;

    assert(hash);
    assert(data);

    iter = FindDLIterator(hash, (void *)data);

    if(!iter)
    {
        return; 
    }
    DListRemove(iter); 
}

void *HashFind(hash_t *hash, const void *data)
{

    dll_iterator_t iter= NULL;
    void *found_data = NULL;
    assert(hash);
    assert(data);

    iter = FindDLIterator(hash, (void *)data);

    if(!iter)
    {
        return NULL; 
    }
    found_data = DListGetData(iter);
    HashRemove(hash ,found_data);
    HashInsert(hash, found_data);
    return found_data;
     
}


int HashForEach(hash_t *hash, hash_action_func_t action_func, void *param)
{
    size_t index = 0; 
    int result = 0;

    assert(hash);
    assert(action_func);

        for (index = 0; index < hash->table_size && 0 == result ; index++)
        {
            result = DListForEach(DListBegin(hash->table[index]),
                                     DListEnd(hash->table[index])
                                            , param, action_func); 
       
        }

        return result;

}

static void FreeLists(hash_t *hash, size_t end)
{
        size_t i = 0;

        for (i = 0; i < end; i++)
        {
             DListDestroy(hash->table[i]);
        }
}

static dll_iterator_t FindDLIterator(hash_t *hash, void *data)
{
    size_t index = 0;
    dll_t *list = NULL;
    dll_iterator_t iter= NULL;

    assert(hash);
    assert(data);

    index = hash->hash_func(data) % hash->table_size; 
    list = hash->table[index]; 
    iter = DListFind(DListBegin(list),DListEnd(list),
                             data, hash->is_match_func);

    if(DListIsSameIter(DListEnd(list), iter))
    {
        return NULL; 
    } 

    return iter;
}
