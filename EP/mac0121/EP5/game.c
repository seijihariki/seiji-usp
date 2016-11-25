#include "game.h"
#include <stdlib.h>
#include <stdio.h>

Game makeGame()
{
    int i, j;
    Game gm = malloc(sizeof(struct game_s));
    reset(gm);
    return gm;
}

int atGame(Game game, int x, int y)
{
    if (x == -1 || x == s_x)
        return -1;
    if (y == -1 || y == s_y)
        return -1;
    if (x >= 0 && x < s_x && y >= 0 && y < s_y)
        return game->board[x][y];
    return -2;
}

void setGame(Game game, int x, int y, int v)
{
    if (x >= 0 && x < s_x && y >= 0 && y < s_y)
        game->board[x][y] = v;
}

int play(int x, int y, Game game)
{
    if (game->round == 1 && game->board[x][y])
        game->next = (game->next == 'W')?'B':'W'; 

    if (game->board[x][y])
        return 0;
    game->board[x][y] = game->next;
    game->next = (game->next == 'W')?'B':'W';
    game->round++;
    return 1;
}

void undo(int x, int y, Game game)
{
    if (!game->board[x][y])
        return;
    game->board[x][y] = 0;
    game->next = (game->next == 'W')?'B':'W';
    game->round--;
}

void reset(Game game)
{
    int i, j;
    for (i = 0; i < s_x; i++)
    {
        for (j = 0; j < s_y; j++)
            game->board[i][j] = 0;
    }
    game->next = 'W';
    game->round = 0;
}

Game copyRawState(Game game)
{
    int i, j;
    Game gm = malloc(sizeof(struct game_s));
    for (i = 0; i < s_x; i++)
    {
        for (j = 0; j < s_y; j++)
            gm->board[i][j] = game->board[i][j];
    }
    return gm;
}

void freeGame(Game game)
{
    free(game);
}

void printGame(Game game)
{
    int i, j;
    for (j = 0; j < s_y; j++)
    {
        for (i = 0; i < j; i++)
            fprintf(stderr, " ");
        for (i = 0; i < s_x; i++)
            fprintf(stderr, "%c%c",
                    game->board[i][j]?(char)game->board[i][j]:'-',
                    (i < s_x - 1)?' ':'\n');
    }
}
