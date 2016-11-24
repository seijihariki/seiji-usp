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

void expand_from(Game game, Game distances, int x, int y)
{
    char color = game->board[x][y];
    if (!color || distances->board[x][y])
        return;

    if (game->board[x - 1][y] == color)
        expand_from(game, distances, x - 1, y);
    if (game->board[x + 1][y] == color)
        expand_from(game, distances, x + 1, y);
    if (game->board[x][y - 1] == color)
        expand_from(game, distances, x, y - 1);
    if (game->board[x][y + 1] == color)
        expand_from(game, distances, x, y + 1);
    if (game->board[x + 1][y - 1] == color)
        expand_from(game, distances, x + 1, y - 1);
    if (game->board[x - 1][y + 1] == color)
        expand_from(game, distances, x - 1, y + 1);
}

float avail_gamestate_B(Game game, Game distances)
{
    int i, j;
    for (i = 0; i < s_y; i++)
    {
        game->board[0][i] = 1;
    }

    for (i = 0; i < s_x; i++)
    {
        for (j = 0; j < s_y; j++)
        {

        }
    }
}

float avail_gamestate_W(Game game, Game distances)
{
    int i, j, dist;
    for (i = 0; i < s_x; i++)
    {
        game->board[i][0] = 1;
    }

    for (i = 0; i < s_x; i++)
    {
        for (j = 0; j < s_y; j++)
        {
            if ()
            {
                expand();
            }
        }
    }
}

float avail_gamestate(Game game, Game distances)
{
    if (!distances) return 1;
    return avail_gamestate(game, distances);
}

/* Uses minimax to calculate next move.                                     *
 * (depth 4, < 197 children each node)                                      *
 *                                                                          *
 * DEPTH:                  LAYER TYPE:                                      *
 *                                                                          *
 * 1                 o     MAX                                              *
 *                  / \                                                     *
 *                 /   \                                                    *
 * 2               o   o   MIN                                              *
 *                / \ / \                                                   *
 * 3              o o o o  MAX                                              *
 *                . . . .                                                   *
 *                . . . .                                                   *
 *                . . . .                                                   */

float minimax_recursive (int depth, float alpha, float beta, char ismax, Game game, int *x, int *y, Game distances)
{
    int i, j;
    int ismin = !ismax;
    float curr = ismin?INF:-INF;

    if (!depth) return avail_gamestate(game, distances);

    for (i = 0; i < s_x; i++)
    {
        for (j = 0; j < s_y; j++)
        {
            if (alpha >= beta)
                return curr;
            if (!game->board[i][j])
            {
                play(i, j, game);
                float ret = minimax_recursive(depth - 1, alpha, beta, ismin, game, 0, 0, distances);

                if (x && y && ret > curr)
                {
                    *x = i;
                    *y = j;
                }

                curr = ismin?min(ret, curr):max(ret, curr);
                if (ismin) beta = min(ret, beta);
                else alpha = max(ret, alpha);
                undo(i, j, game);
            }
        }
    }
    return curr;
}


void playerNext(Game game, int *x, int *y)
{
    minimax_recursive (3, -INF, INF, 1, game, x, y, 0);
}
