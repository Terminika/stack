#include <stdio.h>
#include <cstdlib>
#include <locale.h>
#include <assert.h>
#include <math.h>

#define UP_MEM_STEP 1.7F
#define DOWN_MEM_STEP pow(1.5, -1)
#define POISON 0xBADDEDBADl
enum {
    OVERLOAD = -1,
    ALL_RIGHT = 1
};

typedef long double elem_t;

typedef struct
{
    // elem_t * data;
    size_t size;
    size_t capacity;
    elem_t* data; 

} Stack;

int stack_Ctor(Stack* stk, int capacity)
{
    (*stk).data = (elem_t*)calloc(capacity, sizeof(elem_t));
    (*stk).size = 0;
    (*stk).capacity = capacity;
    return 1;
}

int stack_Dtor(Stack* stk)
{
    return 0;
}

void stack_resize(Stack* stk, float step)
{
    if (!(*stk).capacity)
    {
        (*stk).capacity = 1;
    } 
    long int new_capacity = ((*stk).capacity * step);
    (*stk).data = (elem_t*)realloc((*stk).data, new_capacity * sizeof(elem_t)); 
    for (long int i=(*stk).size; new_capacity; i++)
    {
        (*stk).data[i] = POISON;
    }
}

int Stack_Push(Stack* stk, elem_t elem)
{
    if ((*stk).size == (*stk).capacity)
    {
        stack_resize(stk, UP_MEM_STEP);
    }
    assert(int ((*stk).size <= (*stk).capacity));
    (*stk).data[(*stk).size] = elem;
    (*stk).size++;
    
    printf("size before push: %lu\n", (*stk).size);
    printf("elem, capacity: %Lf %lu\n", (*stk).data[0], (*stk).capacity);
    return ALL_RIGHT;
}

void stack_pop(Stack* stk, elem_t* value)
{   
    *value = (*stk).data[(*stk).size - 1];
    if ((*stk).size < (*stk).capacity / 2 && (*stk).size >= 0)
    {
        stack_resize(stk, DOWN_MEM_STEP);
    }
    (*stk).data[--(*stk).size] = POISON;
}

elem_t stack_top(Stack* stk, elem_t* value)
{
    elem_t top = (*stk).data[(*stk).size--];
    return top;
}


void stack_dump(Stack* stk, int st)
{
    char status[] = "ok";
    printf("Stack [%lu] (%s)\n {\n", (long int)stk, status); 
    printf("size=%lu\n", (*stk).size);
    printf("capacity=%lu\n", (*stk).size);
    //printf("data[%lu]\n", (long int)&(*stk).data);
    if ((*stk).size)
    {
        for (long int i=0; (*stk).size; i++)
        {
            printf("[%li]=%Lf\n", i, (*stk).data[i]);
        }
        printf("}\n");
        printf("\n\n\n");
    }
    else
        printf("empty");

}

int main()
{
    Stack stk = {};
    stk.size = 0;
    stk.capacity = 5;
    stk.data = (elem_t*)calloc(5, sizeof(elem_t));
    /*for (long int i=stk.size; 5; i++)
    {
        (stk.data[i]) = 22222222222222; //(elem_t)POISON;
    }*/

    //stack_dump(&stk, 1);
    elem_t pop = 0; 
    //stack_Ctor(&stk, 5);
    //stack_dump(&stk, 1);

    Stack_Push(&stk, 37);
    return 0;
    stack_dump(&stk, 1);

    //printf("result: %Lf\n", stk.data[0]);
    stack_pop(&stk, &pop);
    stack_dump(&stk, 1);


    printf("pop: %Lf\n", pop);
    printf("after pop: %Lf\n", stk.data[stk.size - 1]);
    stack_resize(&stk, UP_MEM_STEP);
    stack_dump(&stk, 1);
    return 1;   
}

/*канарейки - 2 long long, выделются сразу при создании стека, в начало и конец  указатель на стек - начиная с данных
яд - то что в канарейках, большое шестнадцатиричное число
stack top - возвращает последней элемент стека, не удаялет. поп удаляет и ничего не вовзращает
коэффициенты realloc - 1.7 возврастаняи , 1.5 если пуст на половину
верицикатор - if if if if  проверка корректности стека, яд для этого же нужен
elem_t - для удобности изменения типа данных которые лежат в стеке
dump - красивый вывод состояния стека и его содержимоо 

assert(int (условие) && dump)*/