#include "game.h"
#include <stdlib.h>

#define s_x 14
#define s_y 14

Game B_BFS, W_BFS;

typedef struct {
    int x, y;
} coords;

const coords neighbors[] = {
    { -1,  0 },
    {  0, -1 },
    {  1, -1 },
    {  1,  0 },
    {  0,  1 },
    { -1,  1 }
};

const coords bridges[] = {
    { -1, -1 },
    {  1, -2 },
    {  2, -1 },
    {  1,  1 },
    { -1,  2 },
    { -2,  1 }
};

const coords bridge_pre[][2] = {
    {{  0, -1 }, { -1,  0 }},
    {{  1, -1 }, {  0, -1 }},
    {{  1,  0 }, {  1, -1 }},
    {{  0,  1 }, {  1,  0 }},
    {{ -1,  1 }, {  0,  1 }},
    {{ -1,  0 }, { -1,  1 }}
};

const coords wall_patt[][10] = {
    {
        { -1, -2 },
        {  0, -2 },
        {  2, -2 },
        {  3, -2 },
        { -1, -1 },
        {  0, -1 },
        {  1, -1 },
        {  2, -1 },
        { -1,  0 },
        {  1,  0 }
    },
    {
        {  2, -3 },
        {  2, -2 },
        {  2,  0 },
        {  2,  1 },
        {  1, -2 },
        {  1, -1 },
        {  1,  0 },
        {  1,  1 },
        {  0, -1 },
        {  0,  1 }
    },
    {
        { -1,  0 },
        {  1,  0 },
        { -2,  1 },
        { -1,  1 },
        {  0,  1 },
        {  1,  1 },
        { -3,  2 },
        { -2,  2 },
        {  0,  2 },
        {  1,  2 }
    },
    {
        {  0, -1 },
        {  0,  1 },
        { -1, -1 },
        { -1,  0 },
        { -1,  1 },
        { -1,  2 },
        { -2, -1 },
        { -2,  0 },
        { -2,  2 },
        { -2,  3 }
    }
};

void add_conn(Game game, int x, int y, char color, int conn, int skip)
{
    int i, xoff, yoff, ok;
    char enemy = (color == 'W')?'B':'W';
    Game bfs = (color == 'W')?W_BFS:B_BFS;

    if (!skip)
    {
        if (atGame(game, x, y) < -1 || !atGame(game, x, y))
        {
            if (!atGame(bfs, x, y))
                setGame(bfs, x, y, conn);
            return;
        } else if (atGame(game, x, y) > 0 && atGame(game, x, y) != color)
        {
            if (!atGame(bfs, x, y))
                setGame(bfs, x, y, -2);
            return;
        }
    }

    setGame(bfs, x, y, -3);

    /* Expand to adjacent */
    for (i = 0; i < 6; i++)
    {
        xoff = neighbors[i].x;
        yoff = neighbors[i].y;

        if (atGame(game, x + xoff, y + yoff) >= 0
                && !atGame(bfs, x + xoff, y + yoff))
            add_conn(game, x + xoff, y + yoff, color, conn, 0);
    }

    /* Expand bridges */
    for (i = 0; i < 6; i++)
    {
        ok = 1;
        xoff = bridges[i].x;
        yoff = bridges[i].y;

        ok = ok && atGame(game,
                x + bridge_pre[i][0].x,
                y + bridge_pre[i][0].y) != enemy;
        ok = ok && atGame(game,
                x + bridge_pre[i][1].x,
                y + bridge_pre[i][1].y) != enemy;

        if (ok && atGame(game, x + xoff, y + yoff) >= 0
                && !atGame(bfs, x + xoff, y + yoff))
            add_conn(game, x + xoff, y + yoff, color, conn, 0);
    }
}

void set_zero_conn(Game game)
{
    int i, j, ok;
    char tmp;

    reset(B_BFS);
    reset(W_BFS);

    /* Adjacent && bridge to walls */
    for (i = 0; i < s_x; i++)
    {
        add_conn(game, i,  -1, 'W', 1, 0);
        add_conn(game, i, s_y, 'W', 1, 0);
    }

    for (i = 0; i < s_y; i++)
    {
        add_conn(game,  -1, i, 'B', 1, 0);
        add_conn(game, s_x, i, 'B', 1, 0);
    }

    /* Check for wall tower patterns */
    for (i = 0; i < s_x; i++)
    {
        ok = 1;
        for (j = 0; j < 10; j++)
        {
            tmp = atGame(game,
                    i + wall_patt[0][j].x,
                    2 + wall_patt[0][j].y);

            ok = ok && tmp != 'B' && tmp != -1;
        }

        if (ok) add_conn(game, i, 2, 'W', 1, 0);

        ok = 1;
        for (j = 0; j < 10; j++)
        {
            tmp = atGame(game,
                    i + wall_patt[2][j].x,
                    s_y - 3 + wall_patt[2][j].y);
            ok = ok && tmp != 'B' && tmp != -1;
        }
        if (ok) add_conn(game, i, s_y - 3, 'W', 1, 0);
    }

    for (i = 0; i < s_y; i++)
    {
        ok = 1;
        for (j = 0; j < 10; j++)
        {
            tmp = atGame(game,
                    2 + wall_patt[3][j].x,
                    i + wall_patt[3][j].y);
            ok = ok && tmp != 'W' && tmp != -1;
        }
        if (ok) add_conn(game, 2, i, 'B', 1, 0);

        ok = 1;
        for (j = 0; j < 10; j++)
        {
            tmp = atGame(game,
                    s_x - 3 + wall_patt[1][j].x,
                    i + wall_patt[1][j].y);
            ok = ok && tmp != 'W' && tmp != -1;
        }
        if (ok) add_conn(game, s_x - 3, i, 'B', 1, 0);
    }
}

void bfs(Game game, char color)
{
    int currcnt = 0, i, j;
    char b_dirty = 1;
    Game bfs_b = (color == 'W')?W_BFS:B_BFS;
    while (b_dirty)
    {
        b_dirty = 0;
        currcnt++;

        for (i = 0; i < s_x; i++)
        {
            for (j = 0; j < s_y; j++)
            {
                if (atGame(bfs_b, i, j) == currcnt)
                    add_conn(game, i, j, color, currcnt + 1, 1);
            }
        }

        for (i = 0; i < s_x; i++)
        {
            for (j = 0; j < s_y; j++)
            {
                if (!atGame(bfs_b, i, j))
                    b_dirty = 1;
            }
        }
    }
}

int playerNext(Game game, int *x, int *y)
{
    char ally, enemy;
    int i, j;

    if (!game)
        return 0;

    if (!B_BFS) B_BFS = malloc(sizeof(struct game_s));
    if (!W_BFS) W_BFS = malloc(sizeof(struct game_s));

    ally = game->next;
    enemy = (game->next == 'W')?'B':'W';

    set_zero_conn(game);
/*
    bfs(game, 'B');
    bfs(game, 'W');
*/
    printGame(B_BFS);

    *x = *y = 0;
}

void playerFree()
{
    if (B_BFS) freeGame(B_BFS);
    if (W_BFS) freeGame(W_BFS);
}
