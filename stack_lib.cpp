#include "stack_lib.h"
#include <stdio.h>
//#define NDEBUG  // disable asserts
#include <assert.h>

#define ASSERT_NULL_PTR(ptr)     \
do\
{\
    assert(ptr != NULL);\
    if (ptr == NULL)\
    {\
        return NULL_PTR;\
    }\
}\
while (0)


#define ASSERT_POISON_PTR(ptr)     \
do\
{\
    assert(ptr != (Elem_t*)POISON_PTR);\
    if (ptr == (Elem_t*)POISON_PTR)\
    {\
        return POISON_DATA_PTR;\
    }\
}\
while (0)


#define STACK_CHECK(ptr)     \
do\
{\
    if (stack_verificator(stk))\
        {\
            return VERIFICATION_ERROR;\
        }\
}\
while (0)


STACK_STATUS stack_ctor(Stack_t* stk, size_t capacity)
{
    stk->left_canary = CANARY;
    stk->right_canary = CANARY;
    stk->size = 0;
    stk->capacity = capacity;
    stk->status = 0;
    stk->data = (Elem_t*)calloc(capacity, sizeof(Elem_t));

    assert(stk->data != (Elem_t*)NULL);
    if (stk == NULL)
    {
        return NULL_PTR;
    }

    return OK;
}

STACK_STATUS stack_dtor(Stack_t* stk)
{
    STACK_CHECK(stk);

    free(stk->data);

    stk->capacity = 0;
    stk->size = 0;
    stk->data = (Elem_t*)POISON_PTR;
    return OK;
}

STACK_STATUS stack_resize(Stack_t* stk, float step)
{
    STACK_CHECK(stk);

    if (!stk->capacity)
    {
        stk->capacity = 8;
    } 

    size_t new_capacity = (stk->capacity * step);

    stk->data = (Elem_t*)realloc(stk->data, new_capacity * sizeof (Elem_t)); 
    for (size_t i = stk->capacity; i < new_capacity; i++)
    {
        stk->data[i] = POISON;
    }

    stk->capacity = new_capacity;

    return OK;
}

STACK_STATUS stack_push(Stack_t* stk, Elem_t elem)
{
    STACK_CHECK(stk);

    if (stk->size == stk->capacity)
    {
        stack_resize(stk, UP_MEM_STEP);
    }

    assert(stk->size <= stk->capacity);
    stk->data[stk->size++] = elem;
    
    return OK;
}

STACK_STATUS stack_pop(Stack_t* stk, Elem_t* value)
{   
    STACK_CHECK(stk);
    
    *value = stk->data[stk->size - 1];

    if (stk->size < stk->capacity / 2 && stk->size >= 0)
    {
        stack_resize(stk, DOWN_MEM_STEP);
    }

    stk->data[--stk->size] = POISON;

    return OK;
}

STACK_STATUS stack_top(Stack_t* stk, Elem_t* value)
{
    STACK_CHECK(stk);

    *value = stk->data[stk->size--];
    return OK;
}

void stack_dump(Stack_t* stk)
{
    const char* status = "ok";
    
    printf("Stack [%lu] (%s)\n", (long int)stk, status); 

    if (stk->data == (Elem_t*)POISON_PTR)
    {
        printf("\tStack was destructed\n");
    }
    else if (!stk->size)
    {
        printf("\tStack is empty\n");

        printf("\t{\n");
        printf("\t\tleft_canary = %p\n", (void*)stk->left_canary);

        printf("\t\tsize = %zu\n", stk->size);
        printf("\t\tcapacity = %zu\n", stk->capacity);

        if (stk->size)
        {
            printf("\t\tdata = %p\n", (void*)stk->data);
            printf("\t\t{\n");
            for (size_t i = 0; i < stk->size; i++)
            {
                printf("\t\t\t[%ld] = %Lf\n", i, stk->data[i]);
            }
            printf("\t\t}\n");
        }
        
        printf("\t\tright_canary = %p\n", (void*)stk->right_canary);
        printf("\t}\n\n\n\n");

    }
}

int stack_verificator(Stack_t *stk)
{
    printf("in verificator\n");
    if (stk == NULL)
    {
        printf("null ptr\n");
        return NULL_PTR;
    }
    if (stk->data == (Elem_t*) NULL)
    {
        printf("null data ptr\n");
        stk->status |= NULL_DATA_PTR;
    }
    if (stk->data == (Elem_t*) POISON_PTR)
    {
        printf("poison data ptr\n");
        stk->status |= POISON_DATA_PTR;
    }
    if (stk->left_canary != CANARY || stk->right_canary != CANARY)
    {
        printf("damaged stack\n");
        stk->status |= DAMAGED_STACK;
    }
    printf("%x\n\n\n", stk->status);
    if (!((stk->status & 0b1) || (stk->status & 0b10)))
        stack_dump(stk);

    return stk->status;
}
