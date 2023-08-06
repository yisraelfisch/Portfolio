#include <stdio.h>
#include <stdlib.h>
#define NEW(t)    ({ void* b = malloc(sizeof(t)); t##_Ctor((t*)b); b; })
#define DEL(t,p)  ({ t##_Dtor((t*)p); free(p); })

int s_count;

typedef void(*func_ptr)();

/*---------------------------structs---------------------------------*/
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

typedef struct
{
    Animal animal;
    Centipede *m_a1;
    Squirl *m_a2;
    Centipede m_c;
    Squirl m_sq;

}LegendaryAnimal;

/*-------------------------func-declarations-------------------------------*/

void Animal_Ctor(Animal *const this);
void Animal_Dtor(Animal *const this);
void Animal_CCtor(Animal *const this, Animal* const other);
void Animal_Display(Animal *const this);
void Animal_PrintCount();
int Animal_GetID(Animal* const this);

void Centipede_Ctor(Centipede *const this);
void Centipede_Dtor(Centipede *const this);
void Centipede_CCtor(Centipede *const this, Centipede* const other);
void Centipede_Display(Centipede *const this);
void Centipede_BuyShues(Centipede *const this);


void Squirl_Ctor(Squirl *const this);
void Squirl_Dtor(Squirl *const this);
void Squirl_CCtor(Squirl *const this, Squirl* const other);
void Squirl_Display(Squirl *const this);

void LegendaryAnimal_Ctor(LegendaryAnimal *const this);
void LegendaryAnimal_Dtor(LegendaryAnimal *const this);
void LegendaryAnimal_Display(LegendaryAnimal *const this);
void LegendaryAnimal_CCtor(LegendaryAnimal *const this, LegendaryAnimal *const other);

/*------------------virtual-func-tables-------------------------*/

func_ptr Base_vtab[] = 
{
	Animal_Dtor,
	Animal_Display				
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

func_ptr LegendaryAnimal_vtab[] = 
{
	LegendaryAnimal_Dtor,
	LegendaryAnimal_Display				
};
/*-----------------animal func------------------*/
void Animal_Ctor(Animal *const this)
{
    this->Base_vtab_ptr = Base_vtab;
    this->m_id = ++s_count;
    printf("Animal::Ctor() %d\n", this->m_id);

}

void Animal_Dtor(Animal *const this)
{
    --s_count;
    printf("Animal::Dtor() %d\n", this->m_id);
}

void Animal_CCtor(Animal *const this, Animal* const other)
{
    this->Base_vtab_ptr = other->Base_vtab_ptr;
    this->m_id = ++s_count;
    printf("Animal::CCtor() %d\n", this->m_id);
}

void Animal_Display(Animal *const this)
{
    printf("Animal::Display() %d\n", this->m_id);
}

void Animal_PrintCount()
{
    printf("s_count %d\n", s_count);
}

int Animal_GetID(Animal* const this)
{
    return this->m_id;
}
/* ------------------------centipede func----------------------*/

void Centipede_Ctor(Centipede *const this)
{
    Animal_Ctor(&(this->animal));
    this->animal.Base_vtab_ptr = Centipede_vtab;
    this->m_numLegs = 46;
    printf("Centipede::Ctor()\n");
}

void Centipede_Dtor(Centipede *const this)
{
    printf("Centipede::Dtor()\n");
    this->animal.Base_vtab_ptr = Base_vtab;
    this->animal.Base_vtab_ptr[0](&(this->animal));
}

void Centipede_CCtor(Centipede *const this, Centipede* const other)
{
    Animal_CCtor(&(this->animal), &(other->animal));
    this->animal.Base_vtab_ptr = other->animal.Base_vtab_ptr;
    this->m_numLegs = other->m_numLegs;
    printf("Centipede::CCtor()\n");

}

void Centipede_Display(Centipede *const this)
{
    printf("Centipede::Display() ID: %d num legs: %d\n",
    Animal_GetID(&(this->animal)), this->m_numLegs);
}

void Centipede_BuyShues(Centipede *const this)
{
    printf("Centipede::BuyShues() ID:%d\n", Animal_GetID(&(this->animal)));
}

/*--------------squirl func--------------------*/

void Squirl_Ctor(Squirl *const this)
{
    Animal_Ctor(&(this->animal));
    this->animal.Base_vtab_ptr = Squirl_vtab;
    printf("Squirl::Ctor()\n");
}

void Squirl_Dtor(Squirl *const this)
{
    printf("Squirl::Dtor()\n");
    this->animal.Base_vtab_ptr = Base_vtab;
    this->animal.Base_vtab_ptr[0](&(this->animal));
}

void Squirl_CCtor(Squirl *const this, Squirl* const other)
{
    Animal_CCtor(&(this->animal), &(other->animal));
    this->animal.Base_vtab_ptr = other->animal.Base_vtab_ptr;
    printf("Squirl::CCtor()\n");

}

void Squirl_Display(Squirl *const this)
{
    printf("squirl::Display() ID: %d\n",
    Animal_GetID(&(this->animal)));
}

/*--------------legendary-animal-func------------------*/

void LegendaryAnimal_Ctor(LegendaryAnimal *const this)
{
    Animal_Ctor(&(this->animal));
    this->animal.Base_vtab_ptr = LegendaryAnimal_vtab;
    this->m_a1 = NEW(Centipede);
    this->m_a2 = NEW(Squirl);
    Centipede_Ctor((Centipede *const)(&(this->m_c)));
    Squirl_Ctor((Squirl *const)(&(this->m_sq)));
}

void LegendaryAnimal_Dtor(LegendaryAnimal *const this)
{
    DEL(Centipede, this->m_a1);
    DEL(Squirl, this->m_a2);
    this->m_sq.animal.Base_vtab_ptr[0](&(this->m_sq));
    this->m_c.animal.Base_vtab_ptr[0](&(this->m_c));
    this->animal.Base_vtab_ptr = Base_vtab;
    this->animal.Base_vtab_ptr[0](&(this->animal));
}

void LegendaryAnimal_CCtor(LegendaryAnimal *const this, LegendaryAnimal *const other)
{
    Animal_CCtor(&(this->animal), &(other->animal));
    this->animal.Base_vtab_ptr = other->animal.Base_vtab_ptr;
    
    this->m_a1 = malloc(sizeof(Centipede));
    this->m_a2 = malloc(sizeof(Squirl));
    Centipede_CCtor((Centipede *const)(this->m_a1), (Centipede *const)(other->m_a1));
    Squirl_CCtor((Squirl *const)(this->m_a2), (Squirl *const)(other->m_a2));
    
    Centipede_CCtor((Centipede *const)(&(this->m_c)), (Centipede *const)(&(other->m_c)));
    Squirl_CCtor((Squirl *const)(&(this->m_sq)), (Squirl *const)(&(other->m_sq)));
}

void LegendaryAnimal_Display(LegendaryAnimal *const this)
{
    this->m_a1->animal.Base_vtab_ptr[1](this->m_a1);
    this->m_a2->animal.Base_vtab_ptr[1](this->m_a2);
    this->m_c.animal.Base_vtab_ptr[1](&(this->m_c));
    this->m_sq.animal.Base_vtab_ptr[1](&(this->m_sq));
}

void Foo1(Animal *a)
{
    a->Base_vtab_ptr[1](a);
}

void Foo2()
{
    Animal_PrintCount();
}

void Foo3(Animal *ret, int i)
{
    Centipede temp;
    Centipede_Ctor(&temp);
    printf("Foo(int i)\n");

    temp.animal.Base_vtab_ptr[1](&(temp));

    Animal_CCtor(ret,&(temp.animal));
    ret->Base_vtab_ptr = Base_vtab;
    temp.animal.Base_vtab_ptr[0](&(temp));
}

void FiFi(const Centipede *c)
{
    printf("FiFi\n");
    c->animal.Base_vtab_ptr[1](c);
}

int main(int argc, char **argv, char **envp)
{
    Centipede c;
    Centipede_Ctor(&c);
    Foo1(&(c.animal));

    Animal a;
    Foo3(&a, 3);
    a.Base_vtab_ptr[1](&a);
    a.Base_vtab_ptr[0](&a);


    Centipede temp;
    Centipede_CCtor(&temp, &c);

    FiFi((const Centipede *)(&temp));
    temp.animal.Base_vtab_ptr[0](&temp);

    printf("--- array ---\n");

    void *array[] = 
    {
        NEW(Centipede),
        NEW(Squirl),
        NEW(Centipede)
    };

    for(int i = 0; i < 3; ++i)
    {
        ((Animal *)(array[i]))->Base_vtab_ptr[1](array[i]);
    }

    for(int i = 0; i < 3; ++i)
    {
        ((Animal *)(array[i]))->Base_vtab_ptr[0](array[i]);
        free(array[i]);
    }

    printf("--- arr2 ---\n");

    Animal arr2[3] = {0};
    
    Centipede c1;
    Centipede_Ctor(&c1);
    Animal_CCtor(&arr2[0], &c1.animal);
    c1.animal.Base_vtab_ptr[0](&c1);

    Squirl s1;
    Squirl_Ctor(&s1);
    Animal_CCtor(&arr2[1], &s1.animal);
    s1.animal.Base_vtab_ptr[0](&s1);

    Animal_Ctor(&arr2[2]);
    for(int i = 0; i < 2; ++i)
    {
        arr2[i].Base_vtab_ptr = Base_vtab ;
    }

    for(int i = 0; i < 3; ++i)
    {   
        arr2[i].Base_vtab_ptr[1](&arr2[i]);
    }

    Animal_PrintCount();
    Centipede c2; /*relaese*/
    Centipede_Ctor(&c2);
    Animal_PrintCount();

    printf("--- arr3/arr4 ---\n");

    Centipede arr3[4] = {0};

    for(int i = 0; i < 4; ++i)
    {   
        Centipede_Ctor(&arr3[i]);/*remember to free*/
    }

    Squirl *arr4 = malloc(sizeof(Squirl)*4);

    for(int i = 0; i < 4; ++i)
    {   
        Squirl_Ctor(&arr4[i]);
    }

    for(int i = 3; i >= 0; --i)
    {   
        Squirl_Dtor(&arr4[i]);
    }

    free(arr4);

    printf("--- LegendaryAnimal ---\n");

    LegendaryAnimal *la1 = NEW(LegendaryAnimal);
    printf("---\n");
    LegendaryAnimal *la2 = malloc(sizeof(LegendaryAnimal));
    LegendaryAnimal_CCtor(la2, la1);

    la1->animal.Base_vtab_ptr[1](la1);
    la2->animal.Base_vtab_ptr[1](la2);

    la1->animal.Base_vtab_ptr[0](la1);
    free(la1);

    la2->animal.Base_vtab_ptr[1](la2);
    la2->animal.Base_vtab_ptr[0](la2);
    free(la2);

    printf("--- THE END ---\n");

    for(int i = 3; i >= 0; --i)
    {   
        arr3[i].animal.Base_vtab_ptr[0](&arr3[i]);/*remember to free*/
    }

    c2.animal.Base_vtab_ptr[0](&c2);

    for(int i = 2; i >= 0; --i)
    {   
        arr2[i].Base_vtab_ptr[0](&arr2[i]);/*remember to free*/
    }

    c.animal.Base_vtab_ptr[0](&c);

}
