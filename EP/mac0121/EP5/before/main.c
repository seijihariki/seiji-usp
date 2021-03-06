#include "game.h"
#include "player.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    char color = 0;
    char print = 0;
    int k;
    Game game;
    if (argc > 1)
        color = (argv[1][0] == 'P')?'B':'W';
    if (argc == 3)
        print = argv[2][0];
    if (argc < 2)
    {
        printf("Usage: %s <color:[B:W]> [d]\n", argv[0]);
        return 0;
    }

    game = makeGame();

    if (color == 'W')
    {
        while (1)
        {
            int x, y;
            playerNext(game, &x, &y);
            play(x, y, game);
            printf("%d %d\n", y, x);
            if (print) printGame(game);
            k = scanf("%d %d", &y, &x);
            if (!k) break;
            play(x, y, game);
            if (print) printGame(game);
        }
    } else {
        while (1)
        {
            int x, y;
            k = scanf("%d %d", &y, &x);
            if (!k) break;
            play(x, y, game);
            playerNext(game, &x, &y);
            play(x, y, game);
            printf("%d %d\n", y, x);
        }
    }

    freeGame(game);
    return 0;
}
