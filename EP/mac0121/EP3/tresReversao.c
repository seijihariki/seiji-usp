#include "cvector.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>


typedef char bool;
const bool true = 1;
const bool false = 0;

/* Sorts the vector when it has an odd size *
 *                                          *
 * Param:                                   *
 * list: Circular vector                    *
 * moves: Stack of moves                    */
void sortOdd(cvector list, stack moves)
{
    bool changed;
    int i, j, k;

    for(i = 0; i < list->sz - 2; i++)
    {
        for(j = 0; j < list->sz - 2; j++)
        {
            if(atCVector(list, j) > atCVector(list, j + 2))
            {
                threeRotate(list, j);
                pushStack(moves, j);
            }
        }
    }

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

/* Sorts the vector when it has an even size    *
 *                                              *
 * Param:                                       *
 * list: Circular vector                        *
 * moves: Stack of moves                        *
 *                                              *
 * Returns:                                     *
 * True if could be ordered, false otherwise    */

bool sortEven(cvector list, stack moves)
{
    int i, j;
    bool ordered = true;

    for(i = 0; i < list->sz - 3; i++)
    {
        for(j = 0; j < list->sz - 3; j++)
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

/* Main function. Handles IO and executes the sorting functions */

int main()
{
    int sz, i;
    cvector list;
    stack moves;
    if(!scanf("%d", &sz)) return -1;
    if(sz < 0) return -1;

    moves = newStack(10);

    list = newCVector(sz);

    for (i = 0; i < sz; i++)
    {
        int tmp;
        if(!scanf("%d", &tmp)) return -1;
        setCVector(list, i, tmp);
    }

    if(sz % 2) sortOdd(list, moves);
    else if(!sortEven(list, moves))
    {
        printf("Nao e possivel.\n");
        return 0;
    }

    for(i = 0; i < moves->top; i++)
    {
        printf("%d\n", moves->data[i]%sz);
    }
    return 0;
}
