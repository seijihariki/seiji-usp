#include "game.h"
#include <stdlib.h>

#define s_x 14
#define s_y 14

Game B_BFS, W_BFS;

typedef struct {
    int x, y;
} coords;

const coords neighbors[] = {
    { .x = -1, .y = 0 },
    { .x = 0, .y = -1 },
    { .x = 1, .y = -1 },
    { .x = 1, .y = 0 },
    { .x = 0, .y = 1 },
    { .x = -1, .y = 1 }
};

const coords bridges[] = {
    { .x = -1, .y = -1 },
    { .x = 1, .y = -2 },
    { .x = 2, .y = -1 },
    { .x = 1, .y = 1 },
    { .x = -1, .y = 2 },
    { .x = -2, .y = 1 }
};


void add_zero_conn(Game game, int x, int y, char color)
{
    Game bfs = (color == 'W')?W_BFS:B_BFS;
}

void set_zero_conn(Game game)
{
    int i, j;

    reset(B_BFS);
    reset(W_BFS);

    /* Adjacent to black walls */
    for (i = 0; i < s_x; i++)
    {
        if (!atGame(game, i, 0))
            setGame(B_BFS, i, 0, 1);
        else if (atGame(game, i, 0) == 'B')
            add_zero_conn(game, i, 0, 'B');

        if (!atGame(game, i, s_y - 1))
            setGame(B_BFS, i, s_y - 1, 1);
        else if (atGame(game, i, s_y - 1) == 'B')
            add_zero_conn(game, i, s_y - 1, 'B');
    }

    /* Adjacent to white walls */
    for (i = 0; i < s_y; i++)
    {
        if (!atGame(game, 0, i))
            setGame(W_BFS, 0, i, 1);
        else if (atGame(game, 0, i) == 'W')
            add_zero_conn(game, 0, i, 'W');

        if (!atGame(game, s_x - 1, i))
            setGame(W_BFS, s_x - 1, i, 1);
        else if (atGame(game, s_x - 1, i) == 'W')
            add_zero_conn(game, s_x - 1, i, 'W');
    }
}

int playerNext(Game game, int *x, int *y)
{
    char ally, enemy;
    int i, j;

    if (!game)
        return 0;

    if (!B_BFS) B_BFS = malloc(sizeof(struct game_s));

    ally = game->next;
    enemy = (game->next == 'W')?'B':'W';

    for (i = 0; i < s_x; i++)
    {
        for (j = 0; j < s_y; j++)
        {

        }
    }
}

void playerFree()
{
}
