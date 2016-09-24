#include "board.h"
#include "stack.h"
#include <stdio.h>

int solve(board bd, stack st)
{
    board target = copyBoard(bd);
 
    move pop, mv;
    int i, d, x, y;

    invertBoard(target);

    pop.i = 0;
    pop.d = 0;

    do {
        for(i = pop.i; i < bd.sx*bd.sy; i++)
        {
            for(d = pop.d; d < 4 && (bd.data[i] == 1 || 1); d++)
            {
				pop.d = 0;
                getXYBoard(bd, i, &x, &y);

                mv = getMove(bd, x, y, d);

                if(applyMove(bd, mv, 1))
                {
                    pushStack(st, mv);
                    if(eqBoard(target, bd))
					{
						delBoard(target);
						return 1;
					}
                    i = 0;
                    d = -1;
                }
            }
        }
        mv = popStack(st);
        undoMove(bd, mv);
        pop = nextMove(mv);
    } while (pop.i >= 0);
	delBoard(target);
    return 0;
}

void printStack(board bd, stack st)
{
    move mv;
    int i, x0, y0, x1, y1, x2, y2;
    for(i = 0; i < st->top; i++)
    {
        mv = st->data[i];
        moveCoords(bd, mv, &x0, &y0, &x1, &y1, &x2, &y2);
        printf("%d:%d-%d:%d\n", x0, y0, x2, y2);
    }
}

int main()
{
    int tmp, tmp2, sx, sy, x, y;
    board bd;
    stack st;
    tmp = scanf("%d %d", &sy, &sx);
    if (tmp < 0) return -1;
    bd = newBoard(sx, sy);
    for (y = 0; y < sy; y++)
    {
        for(x = 0; x < sx; x++)
        {
            tmp2 = scanf("%d", &tmp);
            if(tmp2 < 0) return -1;
            setBoard(bd, x, y, tmp);
        }
    }

	st = newStack(100);

    if(!solve(bd, st)) tmp = printf("Impossivel\n");
	else printStack(bd, st);
	delStack(st);
	delBoard(bd);
    return 0;
}
