#include "game.h"
#include <stdlib.h>

Game makeGame()
{
    int i, j;
    Game gm = malloc(sizeof(struct game_s));
    for (i = 0; i < s_x; i++)
    {
        for (j = 0; j < s_y; i++)
            gm->board[i][j] = 0;
    }
    gm->next = 0;
    return gm;
}

int play(int x, int y, Game game)
{
    if (game->board[x][y])
        return 0;
    game->board[x][y] = game->next;
    game->next = (game->next == 'W')?'B':'W';
    return 1;
}

void undo(int x, int y, Game game)
{
    if (!game->board[x][y])
        return;
    game->board[x][y] = 0;
    game->next = (game->next == 'W')?'B':'W';
}

void reset(Game game)
{
    int i, j;
    for (i = 0; i < s_x; i++)
    {
        for (j = 0; j < s_y; i++)
            game->board[i][j] = 0;
    }
    game->next = 'W';
}

Game copyRawState(Game game)
{
    int i, j;
    Game gm = malloc(sizeof(struct game_s));
    for (i = 0; i < s_x; i++)
    {
        for (j = 0; j < s_y; i++)
            gm->board[i][j] = game->board[i][j];
    }
    return gm;
}

void freeGame(Game game)
{
    free(game);
}
