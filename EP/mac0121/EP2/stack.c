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

    st->data = (move*) malloc(sizeof(move)*sz);

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

int pushStack(stack st, move mv)
{
    if(st->top >= st->max)
    {
        move *tmp = (move*) realloc(st->data, 2*st->max*sizeof(move));
        if (!tmp) return 0;
        else st->data = tmp;
    }

    st->data[st->top++] = mv;
    return 1;
}

move popStack(stack st)
{
    move ret;
    ret.i = -1;
    ret.d = -1;

    if(!st->top) return ret;

    return st->data[--st->top];
}
