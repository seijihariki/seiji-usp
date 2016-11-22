#include "game.h"
#include <stdlib.h>

#define INF ((float)1/(float)0)

float min(float a, float b)
{
    return a > b?b:a;
}

float max(float a, float b)
{
    return a > b?a:b;
}

float avail_gamestate(Game game)
{
    return 1;
}

// Uses minimax to calculate next move.
// (depth 4, < 197 children each node)
//
// DEPTH:                  LAYER TYPE: 
//
// 1                 o     MAX
//                  / \
//                 /   \
// 2               o   o   MIN
//                / \ / \
// 3              o o o o  MAX
//                . . . .
//                . . . .
//                . . . .

float minimax_recursive (int depth, float alpha, float beta, char ismax, Game game, int *child)
{
    int i, j;
    int ismin = !ismax;
    float curr = ismin?INF:-INF;

    if (!depth) return avail_gamestate(game);
    
    for (i = 0; i < s_x; i++)
    {
        for (j = 0; j < s_y; i++)
        {
            if (alpha >= beta)
                return curr;
            if (!game->board[i][j])
            {
                play(i, j, game);
                float ret = minimax_recursive(depth - 1, alpha, beta, ismin, game, 0);
                if (child && ret > curr) 
                    *child = j + i*s_y;
                curr = ismin?min(ret, curr):max(ret, curr);
                if (ismin) beta = min(ret, beta);
                else alpha = max(ret, alpha);
                undo(i, j, game);
            }
        }
    }
    return curr;
}


int playerNext(Game game)
{
    int *child = malloc(sizeof(int));
    minimax_recursive (5, -INF, INF, 1, game, child);
    int c = *child;
    free(child);
    return c;
}
