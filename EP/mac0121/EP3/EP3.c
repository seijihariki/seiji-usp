#include "cvector.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

#define swap int tmp;
typedef char bool;
const bool true = 1;
const bool false = 0;

void sortOdd(cvector list, stack moves)
{
    bool changed;
    int i, k;
    do {
        changed = false;
        for(i = 0; i < list->sz - 1; i++)
        {
            if(i < list->sz - 2 && atCVector(list, i) > atCVector(list, i + 2))
            {
                threeRotate(list, i);
                pushStack(moves, i);
                changed = true;
            }
            else if(atCVector(list, i) > atCVector(list, i + 1))
            {
                for(k = 0; k < (list->sz + 1)/2; k++)
                {
                    threeRotate(list, i + 2*k);
                    pushStack(moves, i + 2*k);
                    changed = true;
                }
                for(k -= 2; k >= 0; k--)
                {
                    threeRotate(list, i + 2*k);
                    pushStack(moves, i + 2*k);
                    changed = true;
                }
            }
        }
    } while(changed);
}

bool sortEven(cvector list, stack moves)
{
    int i, j;
    bool ordered = true;

    for(i = 0; i < list->sz - 2; i++)
    {
        for(j = i; j < list->sz - 2; j++)
        {
            if(atCVector(list, j) > atCVector(list, j + 2))
            {
                threeRotate(list, j);
                pushStack(moves, j);
            }
        }
    }
    for(i = 0; i < list->sz - 1; i++)
    {
        if(atCVector(list, i) > atCVector(list, i + 1))
            ordered = false;
    }
    return ordered;
}

int main()
{
    int sz, i;
    cvector list;
    stack moves;
    if(!scanf("%d", &sz)) return -1;

    moves = newStack(10);

    list = newCVector(sz);

    for (i = 0; i < sz; i++)
    {
        int tmp;
        if(!scanf("%d", &tmp)) return -1;
        setCVector(list, i, tmp);
    }

    if(sz % 2) sortOdd(list, moves);
    else
    {
        if(!sortEven(list, moves))
        {
            printf("Nao e possivel.\n");
            return 0;
        }
    }

    for(i = 0; i < moves->top; i++)
    {
        printf("%d\n", moves->data[i]);
    }
    return 0;
}
