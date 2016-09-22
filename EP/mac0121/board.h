#ifndef BOARD_H
#define BOARD_H

#include "types.h"

board newBoard(int sx, int sy);

board copyBoard(board bd);

board delBoard(board bd);

void invertBoard(board bd);

char atBoard(board bd, int x, int y);

void setBoard(board bd, int x, int y, char v);

int getIBoard(board bd, int x, int y);

void getXYBoard(board bd, int i, int *x, int *y);

move getMove(board bd, int x, int y, int d);

int applyMove(board bd, move mv, int app);

int undoMove(board bd, move mv);

int eqBoard(board bd1, board bd2);

move nextMove(move mv);
#endif
