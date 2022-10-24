#ifndef STACK_H_terminika
#define STACK_H_terminika

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
    OK = 0,
    OVERLOAD = 1,
    NULL_PTR = 2,
    NULL_DATA_PTR = 3,
    POISON_DATA_PTR = 4,
    VERIFICATION_ERROR = 5
};

typedef long double Elem_t;

typedef struct
{
    // elem_t * data;
    size_t size;
    size_t capacity;
    Elem_t* data; 
    int status;
} Stack_t;



STACK_STATUS stack_ctor(Stack_t* stk, size_t capacity);
STACK_STATUS stack_dtor(Stack_t* stk);
STACK_STATUS stack_resize(Stack_t* stk, float step);
STACK_STATUS stack_push(Stack_t* stk, Elem_t elem);
STACK_STATUS stack_pop(Stack_t* stk, Elem_t* value);
STACK_STATUS stack_top(Stack_t* stk, Elem_t* value);
void stack_dump(Stack_t* stk);
int stack_verificator(Stack_t *stk);

#endif
