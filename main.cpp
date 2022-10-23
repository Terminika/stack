#include <stdio.h>
#include "func.h"


int main()
{
    Stack_t stk;
    Elem_t value;
    stack_ctor(&stk, 0);
    stack_dump(&stk);

    stack_push(&stk, 37);
    stack_dump(&stk);

    stack_pop(&stk, &value);
    stack_dump(&stk);
    for (int i = 0; i < 50; i++)
    {
        stack_push(&stk, i);
        stack_dump(&stk);
    }
    printf("value: %Lf\n\n", value);

    for (int i = 0; i < 35; i++)
    {
        stack_pop(&stk, &value);
        stack_dump(&stk);
    }
    stack_dtor(&stk);
    stack_dump(&stk);
    return 0;
}

/*канарейки - 2 long long, выделются сразу при создании стека, в начало и конец  указатель на стек - начиная с данных
яд - то что в канарейках, большое шестнадцатиричное число
stack top - возвращает последней элемент стека, не удаялет. поп удаляет и ничего не вовзращает
коэффициенты realloc - 1.7 возврастаняи , 1.5 если пуст на половину
верицикатор - if if if if  проверка корректности стека, яд для этого же нужен
elem_t - для удобности изменения типа данных которые лежат в стеке
dump - красивый вывод состояния стека и его содержимоо 

assert(int (условие) && dump)*/
