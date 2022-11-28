#ifndef STACK_H_terminika
#define STACK_H_terminika

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <assert.h>
#include <math.h>

#define POISON 0xBADDEDBADl
#define POISON_PTR 0x11
#define CANARY 0xDEADDEDBADDED32F

const double UP_MEM_STEP = 1.7;
const double DOWN_MEM_STEP = pow(1.5, -1);
size_t MIN_MEM_SIZE = 8;

enum STACK_STATUS
{
    OK = 0,
    NULL_PTR = 1,
    NULL_DATA_PTR = 2,
    POISON_DATA_PTR = 4,
    DAMAGED_STACK = 8,
    VERIFICATION_ERROR = 16,
    MEMORY_ERROR = 32
};

typedef long double Elem_t;
typedef unsigned long long Canary_t;

typedef struct
{
    Canary_t left_canary;
    size_t size;
    size_t capacity;

    Elem_t* data; 

    unsigned int status;
    Canary_t right_canary;
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
