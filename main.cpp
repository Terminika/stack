#include <stdio.h>
#include "stack_lib.h"


int main()
{
    Stack_t stk;
    Elem_t value;
    stack_ctor(&stk, 0);

    stack_push(&stk, 37);

    /*stack_pop(&stk, &value);
    for (int i = 0; i < 10; i++)
    {
        stack_push(&stk, i);
    }

    for (int i = 0; i < 35; i++)
    {
        stack_pop(&stk, &value);
    }
*/
    stk.left_canary = 123;
    stack_push(&stk, 3);
    printf("%p\n", stk.data);
    printf("%p\n", (Canary_t*)(stk.data) - 1);

    Canary_t* temp_ptr = (Canary_t*)(stk.data) - 1;
    *temp_ptr = 228;

    stack_dtor(&stk);
    return 0;
}
