#include "func.h"
#include <stdio.h>


STACK_STATUS stack_ctor(Stack_t* stk, int capacity)
{
    stk->data = (Elem_t*)calloc(capacity, sizeof(Elem_t));
    stk->size = 0;
    stk->capacity = capacity;
    return OK;
}

STACK_STATUS stack_dtor(Stack_t* stk)
{
    free(stk->data);
    stk->capacity = 0;
    stk->size = 0;
    stk->data = (Elem_t*)POISON_PTR;
    return OK;
}

STACK_STATUS stack_resize(Stack_t* stk, float step)
{
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
    if (stk->size == stk->capacity)
    {
        stack_resize(stk, UP_MEM_STEP);
    }
    assert(stk->size <= stk->capacity);
    stk->data[stk->size++] = elem;
    
    /*printf("size before push: %lu\n", stk->size);
    printf("elem, capacity: %Lf %lu\n", stk->data[0], stk->capacity);*/
    return OK;
}

STACK_STATUS stack_pop(Stack_t* stk, Elem_t* value)
{   
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
    *value = stk->data[stk->size--];
    return OK;
}

void stack_dump(Stack_t* stk)
{
    const char* status = "ok";
    
    printf("Stack [%lu] (%s)\n", (long int)stk, status); 
    printf("{\n");

    if (stk->size)
    {
        printf("\tsize = %zu\n", stk->size);
        printf("\tcapacity = %zu\n", stk->capacity);

        printf("\tdata = %p\n", (void*)stk->data);
        printf("\t{\n");
        for (size_t i = 0; i < stk->size; i++)
        {
            printf("\t\t[%ld] = %Lf\n", i, stk->data[i]);
        }
        printf("\t}\n");
    }
    else if (stk->capacity)
    {
        printf("\tStack is empty\n");
    }
    else if (!stk->capacity)
    {
        printf("\tStack was destructed\n");
    }

    printf("}\n\n\n\n");
}
