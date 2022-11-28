#include "stack_lib.h"


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

STACK_STATUS stack_calloc(Stack_t* stk, size_t capacity)
{

    Canary_t* temp_ptr = (Canary_t*)calloc(1, capacity * sizeof(Elem_t) + 2 * sizeof(Canary_t));
    
    if (!temp_ptr)
    {
        return MEMORY_ERROR;
    }

    *temp_ptr = CANARY;
    Elem_t* stk_data = (Elem_t*)(++temp_ptr);

    if (!stk_data)
    {
        return MEMORY_ERROR;
    }

    stk->data = stk_data;

    temp_ptr = (Canary_t*)(stk_data + capacity);
    *temp_ptr = CANARY;
    
    return OK;
}

STACK_STATUS stack_realloc(Stack_t* stk, size_t capacity)
{
    Canary_t* temp_ptr = (Canary_t*)(stk->data) - 1;
    
    temp_ptr = (Canary_t*)realloc(temp_ptr, capacity * sizeof(Elem_t) + 2 * sizeof(Canary_t));

    if (!temp_ptr)
    {
        return MEMORY_ERROR;
    }
    *temp_ptr = CANARY;
    Elem_t* stk_data = (Elem_t*)(++temp_ptr);

    if (!stk_data)
    {
        return MEMORY_ERROR;
    }

    stk->data = stk_data;

    temp_ptr = (Canary_t*)(stk_data + capacity);
    *temp_ptr = CANARY;

    return OK;
}

void stack_free(Stack_t* stk)
{
    Canary_t* temp_ptr = (Canary_t*)(stk->data) - 1;
    free(temp_ptr);
}

STACK_STATUS stack_ctor(Stack_t* stk, size_t capacity)
{
    stk->left_canary = CANARY;
    stk->right_canary = CANARY;
    stk->size = 0;
    stk->capacity = capacity ;
    stk->status = stack_calloc(stk, capacity);
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

    stack_free(stk);

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
        stk->capacity = MIN_MEM_SIZE;
    } 

    size_t new_capacity = (stk->capacity * step);

    stk->status |= stack_realloc(stk, new_capacity); 
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

void decode_error(unsigned int status, FILE* fp)
{
    if (status & VERIFICATION_ERROR)
    {
        fprintf(fp, "VERIFICATION ERROR\n");
    }
    if (status & DAMAGED_STACK)
    {
        fprintf(fp, "DAMAGED STACK\n");
    }
    if (status & POISON_DATA_PTR)
    {
        fprintf(fp, "POINTER OF STACK DATA WAS CHANGED WITH FORCE\n");
    }
    if (status & NULL_DATA_PTR)
    {
        fprintf(fp, "POINTER OF STACK DATA POINT TO NOTHING\n");
    }
    if (status & NULL_PTR)
    {
        fprintf(fp, "POINTER OF STACK POINT TO NOTHING\n");
    }
    if (status & MEMORY_ERROR)
    {
        fprintf(fp, "MEMORY ERROR (OVERLOADED)\n");
    }
}

void stack_dump(Stack_t* stk)
{
    FILE *fp;
    char file_name[] = "stack_log.txt";
    if ((fp = fopen(file_name, "a+")) == NULL)
        {
            return;
        }
    
    fprintf(fp, "Stack [%lu] (%s)\n", (long int)stk, stk->status == OK ? "ok": "failed"); 
    if (stk->status != OK)
    {
        decode_error(stk->status, fp);
    }
    fprintf(fp, "\tleft_canary = %llx\n", stk->left_canary);

    if (stk->data == (Elem_t*)POISON_PTR)
    {
        fprintf(fp, "\tStack was destructed\n");
    }
    else
    {
        if (!(stk->size))
        {
            fprintf(fp, "\tStack is empty\n\n");
        }

        fprintf(fp, "\t{\n");

        fprintf(fp, "\t\tsize = %zu\n", stk->size);
        fprintf(fp, "\t\tcapacity = %zu\n", stk->capacity);

        if (stk->size)
        {
            fprintf(fp, "\t\tleft_data_canary = %llx\n", *((Canary_t*)(stk->data) - 1));

            fprintf(fp, "\t\tdata = %p\n", (void*)stk->data);
            fprintf(fp, "\t\t{\n");
            for (size_t i = 0; i < stk->size; i++)
            {
                fprintf(fp, "\t\t\t[%ld] = %Lf\n", i, stk->data[i]);
            }
            fprintf(fp, "\t\t}\n");

            fprintf(fp, "\t\tright_data_canary = %llx\n", *(Canary_t*)(stk->data + stk->capacity));

        }
        
        fprintf(fp, "\t}\n");
    }
    fprintf(fp, "\tright_canary = %llx\n\n\n\n", stk->right_canary);

    fclose(fp);
}

int stack_verificator(Stack_t *stk)
{
    if (stk == NULL)
    {
        return NULL_PTR;
    }
    if (stk->data == (Elem_t*) NULL)
    {
        stk->status |= NULL_DATA_PTR;
    }
    if (stk->data == (Elem_t*) POISON_PTR)
    {
        stk->status |= POISON_DATA_PTR;
    }
    if (stk->left_canary != CANARY || stk->right_canary != CANARY)
    {
        stk->status |= DAMAGED_STACK;
    }


    if (!((stk->status & 0b1) || (stk->status & 0b10)))
    {
        stack_dump(stk);
    }

    return stk->status;
}
