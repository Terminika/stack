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

    Canary_t* temp_ptr = (Canary_t*)(&stk.data) - 1;
    *temp_ptr = 16;

    stack_dtor(&stk);
    return 0;
}

/*канарейки - 2 long long, выделются сразу при создании стека, в начало и конец  указатель на стек - начиная с данных
яд - то что в канарейках, большое шестнадцатиричное число*/


