#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define s_x 14
#define s_y 14

#define B_ENEMY     -2
#define B_ALLY      -3
#define B_CENEMY    -4
#define B_CALLY     -5
#define B_TO_PROT   -6
#define B_TO_ATT    -7

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

int mark_bridges(Game game)
{
    int i, j, k, ok, fst, scd, xoff, yoff, has_to_protect = 0;

    for (i = 0; i < s_x; i++)
    {
        for (j = 0; j < s_y; j++)
        {
            if (atGame(game, i, j))
            {
                for (k = 0; k < 6 && atGame(game, i, j) == 'B'; k++)
                {
                    ok = fst = scd = 0;
                    xoff = bridges[k].x;
                    yoff = bridges[k].y;
                    if (atGame(game, i + xoff, j + yoff) == 'B')
                    {
                        if (!atGame(game,
                                i + bridge_pre[k][0].x,
                                j + bridge_pre[k][0].y))
                        {
                            setGame(W_BFS, i + bridge_pre[k][0].x,
                                    j + bridge_pre[k][0].y, B_CENEMY);
                            setGame(B_BFS, i + bridge_pre[k][0].x,
                                    j + bridge_pre[k][0].y, B_CALLY);
                            fst = 1;
                            ok++;
                        }

                        if (!atGame(game,
                                i + bridge_pre[k][1].x,
                                j + bridge_pre[k][1].y))
                        {
                            setGame(W_BFS, i + bridge_pre[k][1].x,
                                    j + bridge_pre[k][1].y, B_CENEMY);
                            setGame(B_BFS, i + bridge_pre[k][1].x,
                                    j + bridge_pre[k][1].y, B_CALLY);
                            scd = 1;
                            ok++;
                        }

                        if (ok == 1)
                        {
                            if (fst) {
                                setGame(W_BFS, i + bridge_pre[k][0].x,
                                        j + bridge_pre[k][0].y, B_TO_ATT);
                                setGame(B_BFS, i + bridge_pre[k][0].x,
                                        j + bridge_pre[k][0].y, B_TO_PROT);
                                has_to_protect++;
                            } else {
                                setGame(W_BFS, i + bridge_pre[k][1].x,
                                        j + bridge_pre[k][1].y, B_TO_ATT);
                                setGame(B_BFS, i + bridge_pre[k][1].x,
                                        j + bridge_pre[k][1].y, B_TO_PROT);
                                has_to_protect++;
                            }
                        }
                    }
                }

                for (k = 0; k < 6 && atGame(game, i, j) == 'W'; k++)
                {
                    ok = fst = scd = 0;
                    xoff = bridges[k].x;
                    yoff = bridges[k].y;
                    if (atGame(game, i + xoff, j + yoff) == 'W')
                    {
                        if (!atGame(game,
                                i + bridge_pre[k][0].x,
                                j + bridge_pre[k][0].y))
                        {
                             setGame(W_BFS, i + bridge_pre[k][0].x,
                                     j + bridge_pre[k][0].y, B_CALLY);
                             setGame(B_BFS, i + bridge_pre[k][0].x,
                                     j + bridge_pre[k][0].y, B_CENEMY);
                             fst = 1;
                             ok++;
                        }

                        if (!atGame(game,
                                i + bridge_pre[k][1].x,
                                j + bridge_pre[k][1].y))
                        {
                            setGame(W_BFS, i + bridge_pre[k][1].x,
                                     j + bridge_pre[k][1].y, B_CALLY);
                            setGame(B_BFS, i + bridge_pre[k][1].x,
                                     j + bridge_pre[k][1].y, B_CENEMY);
                            scd = 1;
                            ok++;
                        }

                        if (ok == 1)
                        {
                            if (fst) {
                                setGame(W_BFS, i + bridge_pre[k][0].x,
                                        j + bridge_pre[k][0].y, B_TO_PROT);
                                setGame(B_BFS, i + bridge_pre[k][0].x,
                                        j + bridge_pre[k][0].y, B_TO_ATT);
                                has_to_protect++;
                            } else {
                                setGame(W_BFS, i + bridge_pre[k][1].x,
                                        j + bridge_pre[k][1].y, B_TO_PROT);
                                setGame(B_BFS, i + bridge_pre[k][1].x,
                                        j + bridge_pre[k][1].y, B_TO_ATT);
                                has_to_protect++;
                            }
                        }
                    }
                }
            }
        }
    }
    return has_to_protect;
}

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
    if (!atGame(bfs, x, y))
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

    /* Adjacent && bridge to walls */
    for (i = 0; i < s_x; i++)
    {
        add_conn(game, i,  -1, 'W', 1, 0);
        /*add_conn(game, i, s_y, 'W', 1, 0);*/
    }

    for (i = 0; i < s_y; i++)
    {
        add_conn(game,  -1, i, 'B', 1, 0);
        /*add_conn(game, s_x, i, 'B', 1, 0);*/
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

        /*

        ok = 1;
        for (j = 0; j < 10; j++)
        {
            tmp = atGame(game,
                    i + wall_patt[2][j].x,
                    s_y - 3 + wall_patt[2][j].y);
            ok = ok && tmp != 'B' && tmp != -1;
        }
        if (ok) add_conn(game, i, s_y - 3, 'W', 1, 0);
        */
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

        /*
        ok = 1;
        for (j = 0; j < 10; j++)
        {
            tmp = atGame(game,
                    s_x - 3 + wall_patt[1][j].x,
                    i + wall_patt[1][j].y);
            ok = ok && tmp != 'W' && tmp != -1;
        }
        if (ok) add_conn(game, s_x - 3, i, 'B', 1, 0);
        */
    }
}

int minor_from(Game field, int x, int y)
{
    int min = 999999, i, xoff, yoff;

    for (i = 0; i < 6; i++)
    {
        xoff = neighbors[i].x;
        yoff = neighbors[i].y;

        if (atGame(field, x + xoff, y + yoff) > 0
                && atGame(field, x + xoff, y + yoff) < min)
            min = atGame(field, x + xoff, y + yoff);
    }

    for (i = 0; i < 6; i++)
    {
        xoff = bridges[i].x;
        yoff = bridges[i].y;

        if (atGame(field, x + xoff, y + yoff) > 0
                && atGame(field, x + xoff, y + yoff) < min)
            min = atGame(field, x + xoff, y + yoff);
    }

    return min;
}

int64_t state_quality(char color)
{
    int i;
    int64_t sum_w = 9999999999;
    int64_t sum_b = 9999999999;
    int64_t min = 0;

    for (i = 0; i < s_x; i++)
    {
        min = minor_from(W_BFS, i, s_y - 1);
        if (min < sum_w) sum_w = min;
        /*sum_w += min*(197 - min)*(197 - min);*/
    }

    for (i = 0; i < s_y; i++)
    {
        min = minor_from(B_BFS, s_x - 1, i);
        if (min < sum_b) sum_b = min;
        /*sum_w += min*(197 - min)*(197 - min);*/
    }

    if (color == 'W') sum_w = -sum_w;
    else sum_b = -sum_b;

    return sum_w + sum_b;
}

void BFS(Game game, char color)
{
    int currcnt = 0, i, j;
    char b_dirty = 1;
    Game bfs_b = (color == 'W')?W_BFS:B_BFS;
    while (b_dirty && currcnt < 197)
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

int64_t play_quality(Game game, char color)
{
    reset(B_BFS);
    reset(W_BFS);

    mark_bridges(game);
    set_zero_conn(game);

    BFS(game, 'B');
    BFS(game, 'W');
    return state_quality(color);
}

int playerNext(Game game, int *x, int *y)
{
    char ally;
    int i, j;
    int64_t max = -99999999999, quality;
    Game bfs = 0;

    *x = *y = -1;

    if (!game)
        return 0;

    if (!B_BFS) B_BFS = malloc(sizeof(struct game_s));
    if (!W_BFS) W_BFS = malloc(sizeof(struct game_s));

    ally = game->next;
    bfs = (ally == 'W')?W_BFS:B_BFS;

    for (i = 0; i < s_x; i++)
    {
        for (j = 0; j < s_y; j++)
        {
            if (play(i, j, game))
            {
                quality = play_quality(game, ally);

                undo(i, j, game);

                if (quality > max)
                {
                    max = quality;
                    *x = i;
                    *y = j;
                }
            }
        }
    }

    mark_bridges(game);

    max = -9999999999999;

    for (i = 0; i < s_x; i++)
    {
        for (j = 0; j < s_y; j++)
        {
            if (atGame(bfs, i, j) == B_TO_ATT)
            {
                if (play(i, j, game))
                {
                    quality = play_quality(game, ally);

                    undo(i, j, game);

                    if (quality > max)
                    {
                        max = quality;
                        *x = i;
                        *y = j;
                    }
                }
            }

            if (atGame(bfs, i, j) == B_TO_PROT)
            {
                if (play(i, j, game))
                {
                    quality = play_quality(game, ally);

                    undo(i, j, game);

                    if (quality > max)
                    {
                        max = quality;
                        *x = i;
                        *y = j;
                    }
                }

            }
        }
    }

#ifdef __DEBUG__
    reset(B_BFS);
    reset(W_BFS);
    mark_bridges(game);
    play(*x, *y, game);
    set_zero_conn(game);

    BFS(game, 'B');
    BFS(game, 'W');

    undo(*x, *y, game);

    printGame(B_BFS);
    printGame(W_BFS);
#endif
    if (*x < 0) *x = *y = 0;
    return 1;
}

void playerFree()
{
    if (B_BFS) freeGame(B_BFS);
    if (W_BFS) freeGame(W_BFS);
}
