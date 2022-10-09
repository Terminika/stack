#include <stdio.h>
#include <cstdlib>
#include <locale.h>
#include <assert.h>

#define UP_MEM_STEP 20
#define DOWN_MEM_STEP -40

enum {
    OVERLOAD = -1,
    ALL_RIGHT = 1
};

typedef struct
{
    // elem_t * data;
    size_t size;
    size_t capacity;
    int data[]; 

} Stack;

typedef int elem_t[];

int stack_Ctor(Stack* stk, int capacity)
{
    stk = (Stack*) calloc(capacity, sizeof(int));
    //(*stk).size = 0;
    //(*stk).capacity = capacity;
    return 1;
}

int stack_Dtor(Stack* stk)
{
    return 0;
}

int Stack_Push(Stack* stk, int elem)
{
    if ((*stk).size == (*stk).capacity)
    {
        stack_resize(stk, UP_MEM_STEP);
    }
    assert(int ((*stk).size <= (*stk).capacity));
    (*stk).data[(*stk).size] = elem;
    (*stk).size++;
    
    //printf("size before push: %lu\n", (*stk).size);
    //printf("elem, capacity: %i %lu\n", (*stk).data[0], (*stk).capacity);
    return ALL_RIGHT;
}

void stack_pop(Stack* stk, int* value)
{
    *value = (*stk).data[(*stk).size - 1];
    if ((*stk).capacity - (*stk).size >= DOWN_MEM_STEP && (*stk).size != 0)
    {
        stack_resize(stk, DOWN_MEM_STEP);
    }
    (*stk).data[--(*stk).size] = NULL;
}

void stack_resize(Stack* stk, int value)
{
    realloc(stk, ((*stk).capacity + value) * sizeof(int)); // ДА КТО ЭТОТ ВАШ RECALLOC
}

int main()
{
    Stack stk = {0, 5};
    int pop = 0;
    stack_Ctor(&stk, 5);
    Stack_Push(&stk, 37);
    printf("result: %i\n", stk.data[0]);
    stack_pop(&stk, &pop);
    printf("pop: %i\n", pop);
    printf("after pop: %i\n", stk.data[stk.size - 1]);
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