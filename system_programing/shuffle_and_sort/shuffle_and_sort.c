#define _DEFAULT_SOURCE

#include <sys/mman.h>/* mmap */
#include <string.h> /*memchr, strlen, memcpy, strcmp*/
#include <stdlib.h> /* malloc, qsort, free */
#include <stdio.h> /* perror, printf */
#include <pthread.h> /* pthread_create, pthread_join */
#include <unistd.h>
#include <fcntl.h>
#include <time.h> /* clock_gettime */
#include <sys/stat.h>
#include <stdlib.h>/*malloc, free*/
#include <assert.h> /* assert */

#define NUM_OF_COPIES 1
#define NUM_OF_SHUFFELS 10;
#define NUM_OF_THREADS 2

typedef int(*compar_t)(const void *, const void *);

typedef struct work_range
{
    char **arr;
    size_t offset;
    size_t num_of_elements;
    compar_t cmp;
}work_range_t;

static void Prtdic(char **word_buff, size_t num_of_words);
static size_t NumOfWords(char *buff, size_t size);
static void CraeteArrayOfPtr(char *buff, char **ptr_arr, size_t num_of_ptrs);
static void Shuffle(char **ptr_arr, size_t num_of_ptrs, compar_t cmp);
static int Ptr_shuffle(const void *ptr1, const void *ptr2);
static void *Sort(void *arg);
static int Compare(const void *ptr1, const void *ptr2);
int MergeSort(void *arr_to_sort, size_t num_of_elem, size_t elem_size, compar_t is_before);
static void MergePartition(char *buffer, char *arr_to_sort, size_t start, size_t end, size_t elem_size, compar_t is_before, size_t num_of_elem);
static void SortNmerge(char *buffer, char *arr_to_sort, size_t start, size_t mid, size_t end, size_t elem_size, compar_t is_before);

int main(void) 
{
    int i = 0;
    struct stat file = {0};
    char *dictionary = NULL;
    char **word_buffer = NULL;
    int fd = 0, unmap_result = 0;
    size_t num_of_words = 0;
    work_range_t wr[NUM_OF_THREADS] = {0};
    pthread_t threads[NUM_OF_THREADS] = {0};
    struct timespec start = {0}, end = {0};
    double elapsed_time = 0;

    fd = open("/usr/share/dict/words", O_RDONLY);
    fstat(fd, &file);

    dictionary = mmap(NULL, file.st_size, PROT_READ|PROT_WRITE, MAP_FILE|MAP_PRIVATE, fd, 0);

    num_of_words  = NumOfWords(dictionary, file.st_size);

    if(!(word_buffer = (char **)malloc(sizeof(char *) * num_of_words * NUM_OF_COPIES)))
    {
        perror("malloc failed");
    }
    CraeteArrayOfPtr(dictionary, word_buffer, num_of_words);

    Shuffle(word_buffer, num_of_words, Ptr_shuffle);

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        wr[i].arr = word_buffer;
        wr[i].offset = i * (num_of_words * NUM_OF_COPIES / NUM_OF_THREADS);
        wr[i].num_of_elements = num_of_words * NUM_OF_COPIES / NUM_OF_THREADS;
        wr[i].cmp = Compare;
    }
    wr[NUM_OF_THREADS - 1].num_of_elements = num_of_words * NUM_OF_COPIES - wr[0].num_of_elements * (NUM_OF_THREADS - 1);

    clock_gettime(CLOCK_REALTIME, &start);
    
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        if(pthread_create(&threads[i], NULL, Sort, &wr[i]))
        {
            perror("Thread creation");
        }
    }

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        if(pthread_join(threads[i], NULL))
        {
            perror("Thread join");
        }
    }
    
    MergeSort(word_buffer, num_of_words * NUM_OF_COPIES, sizeof(char *), Compare);
    
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) / 1000000000;
    
    printf("elapsed_time: %f\n", elapsed_time);
    
    Prtdic(word_buffer, num_of_words);

    close(fd);
    free(word_buffer);

    return 0;
}

static size_t NumOfWords(char *buff, size_t size)
{
    size_t buff_size = size;
    char *temp = NULL;
    size_t word_counter = 0;
    temp = buff;

    while((temp = (char *)memchr(temp, '\n', buff_size)) && 0 < buff_size)
    {
        *temp ='\0';
        buff_size = size  - (temp - buff);
        ++temp;
        ++word_counter;
    }

    return word_counter;
}

static void CraeteArrayOfPtr(char *buff, char **ptr_arr, size_t num_of_ptrs)
{
    size_t i = 0, j = 0;
    char *temp = NULL;
    for(j = 0; j < NUM_OF_COPIES; ++j)
    {
        temp = buff;
        for(i = 0; i < num_of_ptrs; ++i )
        {
            *(ptr_arr + i + (j * num_of_ptrs)) = temp;
            temp += strlen(temp) + 1;
        }
    }
}

static void Shuffle(char **ptr_arr, size_t num_of_ptrs, compar_t cmp)
{
    size_t i = 0, j = 0, shuff = NUM_OF_SHUFFELS;
    while(shuff--)
    {
        qsort(ptr_arr, num_of_ptrs * NUM_OF_COPIES, sizeof(char *), cmp);
    }
}

static int Ptr_shuffle(const void *ptr1, const void *ptr2)
{
    int temp = rand() % 1000;
    (void)ptr1;
    (void)ptr2;

    if(temp > 800 || temp < 100)
    {
        return 1;
    }
    else if(temp < 800 && temp > 400)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

static void *Sort(void *arg)
{
    work_range_t *wr = (work_range_t *)arg;

    qsort(wr->arr + wr->offset, wr->num_of_elements, sizeof(char *), wr->cmp);

    return NULL;
}

static int Compare(const void *ptr1, const void *ptr2)
{
    int res = 0;

    return strcmp(*(char **)ptr1, *(char **)ptr2);
}

static void Prtdic(char **word_buff, size_t num_of_words)
{
    size_t i = 0, j = 0;

    for(j = 0; j < NUM_OF_COPIES; ++j)
    {
        for(i = 0; i < num_of_words; ++i)
        {
            printf("%s\n", *(word_buff + i + (j * num_of_words)));
        }
    }
}

int MergeSort(void *arr_to_sort, size_t num_of_elem, size_t elem_size, compar_t is_before)
{
    char *buffer = NULL;

    assert(arr_to_sort);
    assert(is_before);

    buffer = (char *)malloc(num_of_elem * elem_size);
    if(!buffer)
    {
        return 1;
    }

    MergePartition(buffer, (char *)arr_to_sort, 0, num_of_elem - 1, elem_size, is_before, num_of_elem);

    free(buffer);
    buffer = NULL;

    return 0;
}

static void MergePartition(char *buffer, char *arr_to_sort, size_t start, size_t end, size_t elem_size, compar_t is_before, size_t num_of_elem)
{
    size_t mid = 0;

    if((end - start) < num_of_elem / NUM_OF_THREADS)
    {
        return;
    }
    
    mid = start + (end - start) / 2;

    MergePartition(buffer, arr_to_sort, start, mid, elem_size, is_before, num_of_elem);
    MergePartition(buffer, arr_to_sort, mid + 1, end, elem_size, is_before, num_of_elem);

    SortNmerge(buffer, arr_to_sort, start, mid, end, elem_size, is_before);
}

static void SortNmerge(char *buffer, char *arr_to_sort, size_t start, size_t mid, size_t end, size_t elem_size, compar_t is_before)
{
    size_t size1 = 0, size2 = 0, i = 0, j = 0, k = 0;
    
    size1 = (mid + 1 - start) * elem_size;
    size2 = (end - mid) * elem_size;
    start *= elem_size;
    mid *= elem_size;
    end *= elem_size;

    memcpy(buffer + start, arr_to_sort + start, size1);
    memcpy(buffer + mid + elem_size, arr_to_sort + mid + elem_size, size2);

    for(i = 0, j = 0, k = start; i < size1 && j < size2; k += elem_size)
    {
        if(is_before(buffer + start + i, buffer + mid + elem_size + j))
        {
            memcpy(arr_to_sort + k, buffer + start + i, elem_size);
            i += elem_size;
        }
        else
        {
            memcpy(arr_to_sort + k, buffer + mid + elem_size + j, elem_size);
            j += elem_size;
        }
    }

    memcpy(arr_to_sort + k, buffer + start + i, size1 - i);
    memcpy(arr_to_sort + k, buffer + mid + elem_size + j, size2 - j);
}

