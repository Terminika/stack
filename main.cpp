#include <stdio.h>
#include <cstdlib>
#include <locale.h>

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
    printf("size ctor: %lu\n", (*stk).size);
    printf("capacity ctor: %lu\n", (*stk).capacity);
    stk = (Stack*) calloc(capacity, sizeof(int));
    (*stk).size = 0;
    (*stk).capacity = capacity;
    printf("size ctor: %lu\n", (*stk).size);
    printf("capacity ctor: %lu\n", (*stk).capacity);
    return 1;
}

int stack_Dtor(Stack* stk)
{
    return 0;
}

int Stack_Push(Stack* stk, int elem)
{
    printf("size before push: %lu\n", (*stk).size);
    printf("elem, capacity: %i %lu\n", elem, (*stk).capacity);
    if ((*stk).size == (*stk).capacity)
        return OVERLOAD;
    (*stk).data[(*stk).size] = elem;
    (*stk).size++;
    printf("size before push: %lu\n", (*stk).size);
    printf("elem, capacity: %i %lu\n", elem, (*stk).capacity);
    return ALL_RIGHT;
}

int Stack_Pop()
{
    return 0;
}

int main()
{
    Stack stk = {};
    stack_Ctor(&stk, 5);
    Stack_Push(&stk, 37);
    printf("result: %i\n", stk.data[0]);
    return 1;   
}