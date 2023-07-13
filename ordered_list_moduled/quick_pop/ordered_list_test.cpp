/********************************* 
 * Author: yisrael fisch            
 * File: ordered_list_test.hpp 
 * 
 * ******************************/

#include "quick_pop_ordered_list.hpp"
#include <iostream> //cout
#include <string>
#include <unistd.h>

using namespace myspace;
using namespace std;

const int num_of_elemnt = 1000;
const int num__persons = 6;
const int num_of_threads = 12;
mutex mutex_lock;
int g_pop_counter = 0;


struct Person
{
    string name;
    int id;
};

void IntTest();
void ThreadSafeTest();
bool IntCompare(const int &a, const int &b);
bool PersonCompare(const Person &a, const Person &b);
void *PushPerson(void *person);
void *PopPerson(void *person);

Ordered_List<Person> person_list(PersonCompare);
Person p_arr[num__persons] = {{"ani", rand()% 1000},{"ray",rand()% 1000},
                                    {"con",rand()% 1000},{"shon", rand()% 1000},
                                     {"mat", rand()% 1000},{"dan",rand()% 1000}};
Person p_arr_res[num__persons];





int main()
{
    //IntTest();
    ThreadSafeTest();

    return 0;
}

void IntTest()
{
    cout << "test for ints" << endl;

    Ordered_List<int> list(IntCompare);
    int arr[num_of_elemnt] = {0};
    int arr_res[num_of_elemnt] = {0};
    
    for(int i = 0; i < num_of_elemnt; ++i)
    {
        arr[i] = rand() % 1000;
    }
    for(int i = 0; i < num_of_elemnt; ++i)
    {
        list.Push(arr[i]);
    }

    for(int i = 0; i < num_of_elemnt; ++i)
    {    
        arr_res[i] = list.Pop();
    }

    for(int i = 0; i < num_of_elemnt; ++i)
    {    
        cout << arr_res[i] << endl;
    }
}

void ThreadSafeTest()
{
    pthread_t thread_id[num_of_threads];
    cout << "test for struct with multy threads" << endl    ;
    int i = 0;


    for(i = 0; i < 6; ++i)
    {
        pthread_create(&thread_id[i], NULL, PushPerson, static_cast<void*>(&(p_arr[i])));
    }
    
    for(i = 0; i < 6; ++i)
    {
        pthread_join(thread_id[i], NULL);
    }
    
    for(i = 6; i < num_of_threads; ++i)
    {
        pthread_create(&thread_id[i], NULL, PopPerson, static_cast<void*>(&(p_arr_res[i-6])));
    }

    for(i = 6; i < num_of_threads; ++i)
    {
        pthread_join(thread_id[i], NULL);
    }
    

    for(int i = 0; i < num__persons; ++i)
    {    
        cout << "person"<< i+1<< endl << p_arr_res[i].id << endl << p_arr_res[i].name << endl;
    }

}

bool IntCompare(const int &a, const int &b)
{
    return a <= b;
}


bool PersonCompare(const Person &a, const Person &b)
{
    
    return a.id <= b.id;
}

void *PushPerson(void *person)
{
    person_list.Push(*(static_cast<Person *>(person)));
    return NULL;
}

void *PopPerson(void *person)
{
    (void*)person;
    unique_lock<mutex> lock(mutex_lock);
    p_arr_res[g_pop_counter]= person_list.Pop();
    ++g_pop_counter;
    lock.unlock();
    return NULL;
}
