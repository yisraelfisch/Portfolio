#include <stdio.h>
#include <stdlib.h>
#define NEW(t)    ({ void* b = malloc(sizeof(t)); t##_Ctor((t*)b); b; })
#define DEL(t,p)  ({ t##_dtor((t*)p); free(p); })



int s_count;
typedef void(*func_ptr)();

typedef struct
{
    func_ptr *Base_vtab_ptr;
    int m_id;
}Animal;

typedef struct
{
    Animal animal;
    int m_numLegs;
}Centipede;

typedef struct
{
    Animal animal;
}Squirl;


void Animal_Ctor(Animal* const this);
void Animal_Dtor(Animal* const this);
void Animal_CCtor(Animal* const this, Animal* const other);
void Animal_Dislplay(Animal* const this);
void Animal_PrintCount();
int Animal_GetID(Animal* const this);
void Centipede_Ctor(Centipede* const this);
void Centipede_CCtor(Centipede* const this, Centipede* const other);
void Centipede_Dtor(Centipede* const this);
void Centipede_Display(Centipede* const this);
void Centipede_BuyShues(Centipede* const this);
void Squirl_Ctor(Squirl* const this);
void Squirl_CCtor(Squirl* const this, Squirl* const other);
void Squirl_Dtor(Squirl* const this);
void Squirl_Display(Squirl* const this);


func_ptr Base_vtab[] = 
{
	Animal_Dtor,
	Animal_Dislplay				
};

func_ptr Centipede_vtab[] = 
{
	Centipede_Dtor,
	Centipede_Display,
    Centipede_BuyShues				
};

func_ptr Squirl_vtab[] = 
{
	Squirl_Dtor,
	Squirl_Display				
};	

/* Animal------------------------------------- */

void Animal_Ctor(Animal* const this)
{
    this->Base_vtab_ptr = Base_vtab; 
    this->m_id = ++s_count;
    printf("Animal::Ctor() %d\n", this->m_id);
}

void Animal_Dtor(Animal* const this)
{
    --s_count;
    printf("Animal::Dtor() %d\n", this->m_id);
}

void Animal_CCtor(Animal* const this, Animal* const other)
{
    (void)other;
    this->Base_vtab_ptr = Base_vtab; 
    this->m_id = ++s_count;
    printf("Animal::CCtor() %d\n", this->m_id);
}

void Animal_Dislplay(Animal* const this)
{
    printf("Animal::Display(): %d\n", this->m_id);
}

void Animal_PrintCount()
{
    printf("s_count: %d\n", s_count);
}

int Animal_GetID(Animal* const this)
{
    return this->m_id;
}

/* Centipede------------------------------------- */




void Centipede_Ctor(Centipede* const this)
{
    Animal_Ctor(&(this->animal));
    this->animal.Base_vtab_ptr = Centipede_vtab;
    this->m_numLegs = 46;
    printf("Centipede::Ctor()\n");
}

void Centipede_CCtor(Centipede* const this, Centipede* const other)
{
    Animal_CCtor(&this->animal, &other->animal);
    this->animal.Base_vtab_ptr = Centipede_vtab;
    this->m_numLegs = other->m_numLegs;
    printf("Centipede::CCtor()\n");
}

void Centipede_Dtor(Centipede* const this)
{
    this->animal.Base_vtab_ptr = Base_vtab;
    printf("Centipede::dtor()\n");
    this->animal.Base_vtab_ptr[0](&(this->animal));   
}

void Centipede_Display(Centipede* const this)
{
    printf("Centipede::Display() ID: %d num legs: %d\n", Animal_GetID(&(this->animal)), this->m_numLegs);
}

void Centipede_BuyShues(Centipede* const this)
{
    printf("Centipede::BuyShues() ID: %d\n", Animal_GetID(&(this->animal)));
}


/* Squirl------------------------------------- */



void Squirl_Ctor(Squirl* const this)
{
    Animal_Ctor(&(this->animal));
    this->animal.Base_vtab_ptr = Squirl_vtab;
    printf("Squirl::Ctor()\n");
}

void Squirl_CCtor(Squirl* const this, Squirl* const other)
{
    Animal_CCtor(&this->animal, &other->animal);
    this->animal.Base_vtab_ptr = Squirl_vtab;
    printf("Squirl::CCtor()\n");
}

void Squirl_Dtor(Squirl* const this)
{
    this->animal.Base_vtab_ptr = Base_vtab;
    printf("Squirl::dtor()\n");
    this->animal.Base_vtab_ptr[0](&(this->animal));
}

void Squirl_Display(Squirl* const this)
{
    printf("Squirl::Display() ID: %d\n", Animal_GetID(&(this->animal)));
}


void Foo_Display(Animal* a)
{
    a->Base_vtab_ptr[1](a);
}

void Foo_PrintCount()
{
    Animal_PrintCount();
}

void Animal_Foo(Animal* ret, int i)
{
    Centipede tmp;
    Centipede_Ctor(&tmp);

    printf("Foo(int i)\n");

    tmp.animal.Base_vtab_ptr[1](&tmp);

    Animal_CCtor(ret, &(tmp.animal));

    tmp.animal.Base_vtab_ptr[0](&tmp);
}

/* CCtor */

void FiFi(Centipede* c)
{
    printf("FiFi\n");
    c->animal.Base_vtab_ptr[1](c);

    Centipede_Dtor(c);
}

int main(int argc, char **argv, char **envp)
{
    Centipede c;
    Centipede_Ctor(&c);
    Foo_Display(&(c.animal));

    Animal animal_temp;
    Animal_Foo(&animal_temp, 3);
    animal_temp.Base_vtab_ptr[1](&animal_temp);
    animal_temp.Base_vtab_ptr[0](&animal_temp);

    Centipede centipede_temp;
    Centipede_CCtor(&centipede_temp, &c);
    FiFi(&centipede_temp);       

    printf("--- array ---\n");

    Animal *array[] =
	{
		NEW(Centipede),
		NEW(Squirl),
		NEW(Centipede)
	};

    for(int i = 0; i < 3; ++i)
    {    
        ((Animal *)array[i])->Base_vtab_ptr[1](array[i]);
    }

    for(int i = 0; i < 3; ++i)
    {    
        ((Animal *)array[i])->Base_vtab_ptr[0](array[i]);
    }

    printf("--- arr2 ---\n");

    Animal arr[3];//dtor
    Centipede centipede_temp2;
    Centipede_Ctor(&centipede_temp2);
    Animal_CCtor(&arr[0], &centipede_temp2.animal);
    centipede_temp2.animal.Base_vtab_ptr[0](&centipede_temp2);

    Squirl Squirl_temp;
    Squirl_Ctor(&Squirl_temp);
    Animal_CCtor(&arr[1], &Squirl_temp.animal);
    Squirl_temp.animal.Base_vtab_ptr[0](&Squirl_temp);

    Animal_Ctor(&arr[2]);

    Animal_PrintCount();
    Centipede c2;
    Centipede_Ctor(&c2);//dtor
    Animal_PrintCount();

    printf("--- arr3/arr4 ---\n");

    Centipede arr3[4];
    for(int i = 0; i < 4; ++i)
    {
        Centipede_Ctor(&arr3[i]);
    }

    Squirl *arr4[4];
    for(int i = 0; i < 4; ++i)
    {
        arr4[i] = (Squirl *)malloc(sizeof(Squirl));
        Squirl_Ctor(arr4[i]);
    }

    for(int i = 3; i >= 0 ; --i)
    {
        Squirl_Dtor(arr4[i]);
        free(arr4[i]);
        arr4[i] = NULL;
    }


    puts("----------------dtors----------------");
    for(int i = 3; i >= 0 ; --i)
    {
        Centipede_Dtor(&arr3[i]);

    }

    c2.animal.Base_vtab_ptr[0](&c2);

    for(int i = 2; i >= 0 ; --i)
    {
        arr[i].Base_vtab_ptr[0](&arr[i]);
        //Animal_Dtor(&arr[i]);
    }
    c.animal.Base_vtab_ptr[0](&c);/*Centipede c dtor*/

    return 0;
}














/*
int main()
{
	Animal a;
    Animal_Ctor(&a);
    a.Base_vtab_ptr[0](&a);
	/*Animal b;
    Animal_CCtor(&b, &a);

    Animal_Dtor(&b);

    Animal_Dtor(&a);
	
	return 0;
}*/