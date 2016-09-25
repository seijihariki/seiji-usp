#include "stack.h"
#include <stdlib.h>

stack newStack(int sz)
{
    stack st = (stack) malloc(sizeof(struct stack_s));
    if(!st)
        return 0;
    st->data = 0;
    st->top = 0;
    st->max = sz;

    st->data = (int*) malloc(sizeof(int)*sz);

    if(st->data)
        st->max = sz;

    return st;
}

void delStack(stack st)
{
    st->max = st->top = 0;
    free(st->data);
    free(st);
    st = 0;
}

int pushStack(stack st, int i)
{
    if(st->top >= st->max)
    {
        int *tmp = (int*) realloc(st->data, 2*st->max*sizeof(int));
        if (!tmp) return 0;
        else st->data = tmp;
    }

    st->data[st->top++] = i;
    return 1;
}

int popStack(stack st)
{
    int ret;
    ret.i = -1;
    ret.d = -1;

    if(!st->top) return ret;

    return st->data[--st->top];
}
