#include "board.h"
#include "stack.h"
#include <stdio.h>

int solve(board bd)
{
    board target = copyBoard(bd);

    stack st = newStack(100);
 
    move pop, mv;
    int i, d;

    invertBoard(bd);

    pop.i = 0;
    pop.d = 0;

    do {
        for(i = pop.i; i < bd.sx*bd.sy; i++)
        {
            for(d = pop.d; d < 4; d++)
            {
                int x, y;
                getXYBoard(bd, i, &x, &y);
                mv = getMove(bd, x, y, d);
                if(applyMove(bd, mv, 1))
                {
                    if(eqBoard(target, bd)) return 1;
                    pushStack(st, mv);
                    i = -1;
                    d = -1;
                }
            }
        }

        pop = nextMove(popStack(st));
    } while (pop.i >= 0);

    return 0;
}

int main()
{
    int tmp, sx, sy, x, y;
    board bd;
    scanf("%d %d", &sy, &sx);
    bd = newBoard(sx, sy);
    for (y = 0; y < sy; y++)
    {
        for(x = 0; x < sx; x++)
        {
            scanf("%d", &tmp);
            setBoard(bd, x, y, tmp);
        }
    }

    if(!solve(bd)) printf("Impossivel\n");
    return 0;
}
