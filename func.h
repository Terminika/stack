#ifndef FUNC_H_terminika
#define FUNC_H_terminika

#include <stdlib.h>
#include <locale.h>
#include <assert.h>
#include <math.h>

#define UP_MEM_STEP 1.7F
#define DOWN_MEM_STEP pow(1.5, -1)
#define POISON 0xBADDEDBADl
#define POISON_PTR 0x11
enum STACK_STATUS
{
    OVERLOAD = -1,
    OK = 0
};

typedef long double Elem_t;

typedef struct
{
    // elem_t * data;
    size_t size;
    size_t capacity;
    Elem_t* data; 

} Stack_t;



STACK_STATUS stack_ctor(Stack_t* stk, int capacity);
STACK_STATUS stack_dtor(Stack_t* stk);
STACK_STATUS stack_resize(Stack_t* stk, float step);
STACK_STATUS stack_push(Stack_t* stk, Elem_t elem);
STACK_STATUS stack_pop(Stack_t* stk, Elem_t* value);
STACK_STATUS stack_top(Stack_t* stk, Elem_t* value);
void stack_dump(Stack_t* stk);
#endif
