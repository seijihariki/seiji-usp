#include "board.h"
#include <stdlib.h>

board newBoard(int sx, int sy)
{
    board ret;
    ret.sx = ret.sy = 0;
    ret.data = 0;

    ret.data = (char*)malloc(sizeof(char)*sx*sy);

    if(ret.data)
    {
        ret.sx = sx;
        ret.sy = sy;
    }

    return ret;
}

board copyBoard(board bd)
{
    int i;
    board ret = newBoard(bd.sx, bd.sy);
    for(i = 0; i < bd.sx*bd.sy; i++) ret.data[i] = bd.data[i];
    return ret;
}

board delBoard(board bd)
{
    bd.sx = bd.sy = 0;
    free(bd.data);
    bd.data = 0;
    return bd;
}

void invertBoard(board bd)
{
    int i;
    for(i = 0; i < bd.sx*bd.sy; i++) bd.data[i] = -bd.data[i];
}

char atBoard(board bd, int x, int y)
{
    int i = getIBoard(bd, x, y);
    if(i < 0) return 0;
    return bd.data[i];
}

void setBoard(board bd, int x, int y, char v)
{
    int i = getIBoard(bd, x, y);
    if(i < 0) return;
    bd.data[i] = v;
}

int getIBoard(board bd, int x, int y)
{
    if(x < 0 || x >= bd.sx) return -1;
    if(y < 0 || y >= bd.sy) return -1;

    return x + y*bd.sx;
}

void getXYBoard(board bd, int i, int *x, int *y)
{
    if(i < 0 || i >= bd.sx*bd.sy)
    {
        *x = *y = -1;
        return;
    }

    *x = i%bd.sx;
    *y = i/bd.sx;
    return;
}

move getMove(board bd, int x, int y, int d)
{
    move ret;
    ret.i = getIBoard(bd, x, y);
    ret.d = d;
    return ret;
}

int applyMove(board bd, move mv, int app)
{
    int x, y, i, m;
    getXYBoard(bd, mv.i, &x, &y);
    if(x < 0 || bd.data[mv.i] == -app) return 0;
    switch(mv.d)
    {
    case 0:
        i = getIBoard(bd, x, y - 2);
        m = getIBoard(bd, x, y - 1);
        break;
    case 1:
        i = getIBoard(bd, x + 2, y);
        m = getIBoard(bd, x + 1, y);
        break;
    case 2:
        i = getIBoard(bd, x, y + 2);
        m = getIBoard(bd, x, y + 1);
        break;
    case 3:
        i = getIBoard(bd, x - 2, y);
        m = getIBoard(bd, x - 1, y);
        break;
    default:
        return 0;
    }
    if(i < 0 || m < 0 || bd.data[i] == app || bd.data[m] == -app) return 0;
    
    bd.data[mv.i] = -app;
    bd.data[i] = app;
    bd.data[m] = -app;

    return 1;
}

int undoMove(board bd, move mv)
{
    return applyMove(bd, mv, -1);
}

int eqBoard(board bd1, board bd2)
{
    int i;
    if(bd1.sx != bd2.sx || bd1.sy != bd2.sy) return 0;

    for(i = 0; i < bd1.sx*bd1.sy; i++)
    {
        if(bd1.data[i] != bd2.data[i]) return 0;
    }
    return 1;
}

move nextMove(move mv)
{
    if(mv.d == 3) mv.i++;
    mv.d = (mv.d + 4)%4;
    return mv;
}
