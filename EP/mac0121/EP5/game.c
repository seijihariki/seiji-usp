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
    {
        game->swap = 1;
        return game->round++;
    }
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

    if (game->round == 2 && game->swap)
    {
        game->swap = 0;
        game->round--;
        return;
    }

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
    game->swap = 0;
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
    int i, j, set_color = 1;
    char *format_str;
    char *color = "";
    char curr;

    for (j = 0; j < s_y; j++)
    {
        for (i = 0; i < j; i++)
            fprintf(stderr, " ");
        for (i = 0; i < s_x; i++)
        {
            curr = game->board[i][j];
            format_str = "%s%c%c";

            if (curr && curr != 'B' && curr != 'W')
            {
                if (curr == -3)
                    curr = 'A';
                else if (curr == -2)
                    curr = 'E';
                else if (curr == -4)
                    curr = 'C';
                else if (curr == -5)
                    curr = 'M';
                else
                    format_str = "%s%d%c";
            }

            if (format_str[3] == 'c' && set_color)
            {
                switch (curr)
                {
                case 0:
                    color = "\e[0;0m";
                    break;
                case 'B':
                    color = "\e[1;34m";
                    break;
                case 'W':
                    color = "\e[1;31m";
                    break;
                case 'M':
                case 'A':
                    color = "\e[1;92m";
                    break;
                case 'C':
                case 'E':
                    color = "\e[1;91m";
                    break;
                default:
                    color = "\e0;0m";
                }
            } else if (set_color) {
                switch (curr)
                {
                case 1:
                    color = "\e[2;31m";
                    break;
                case 2:
                    color = "\e[2;32m";
                    break;
                case 3:
                    color = "\e[2;33m";
                    break;
                case 4:
                    color = "\e[2;34m";
                    break;
                case 5:
                    color = "\e[2;35m";
                    break;
                case 6:
                    color = "\e[2;36m";
                    break;
                default:
                    color = "\e[0;0m";
                }
            }

            fprintf(stderr, format_str,
                    color,
                    (char)curr?curr:'-',
                    (i < s_x - 1)?' ':'\n');
        }
    }
    if (set_color)
        fprintf(stderr, "%s", "\e[0;0m");

}
