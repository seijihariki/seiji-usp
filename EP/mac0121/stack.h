#ifndef STACK_H
#define STACK_H

#include "types.h"

stack newStack(int sz);

void delStack(stack st);

int pushStack(stack st, move mv);

move popStack(stack st);

#endif
