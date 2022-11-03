#include <stdio.h>
#include "stack_lib.h"


int main()
{
    Stack_t stk;
    Elem_t value;
    stack_ctor(&stk, 0);

    /*stack_push(&stk, 37);
    stack_verificator(&stk);

    stack_pop(&stk, &value);
    stack_verificator(&stk);
    for (int i = 0; i < 50; i++)
    {
        stack_push(&stk, i);
    }
    stack_verificator(&stk);

    for (int i = 0; i < 35; i++)
    {
        stack_pop(&stk, &value);
    }
    stack_verificator(&stk);*/

    stk.left_canary = 123;
    stack_push(&stk, 3);

    stack_dtor(&stk);
    return 0;
}

/*канарейки - 2 long long, выделются сразу при создании стека, в начало и конец  указатель на стек - начиная с данных
яд - то что в канарейках, большое шестнадцатиричное число*/


