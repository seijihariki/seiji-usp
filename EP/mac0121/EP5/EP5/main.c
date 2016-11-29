#include "game.h"
#include "player.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char color = 0;
    char print = 0;
    int k;
    char won = 0;
    Game game, aux;

    if (argc > 1)
        color = (argv[1][0] == 'P' || argv[1][0] - 0x20 == 'P')?'B':'W';
    if (argc == 3)
        print = (argv[2][0] == 'd');
    if (argc < 2 || argc > 3)
    {
        printf("Usage: %s <color:[B:W]> [d]\n", argv[0]);
        return 0;
    }

    game = makeGame();
    aux = makeGame();

    if (color == 'W')
    {
        while (1)
        {
            int x, y;
            playerNext(game, &x, &y);
            if (!play(x, y, game)) exit(-1);
            printf("%d %d\n", y, x);
            if (print) printGame(game);
            if ((won = wonGame(game, aux)))
                break;
            k = scanf("%d %d", &y, &x);
            if (!k) break;
            if (!play(x, y, game)) exit(-1);
            if (print) printGame(game);
            if ((won = wonGame(game, aux)))
                break;
        }
    } else {
        while (1)
        {
            int x, y;
            if (print) printGame(game);
            if ((won = wonGame(game, aux)))
                break;
            k = scanf("%d %d", &y, &x);
            if (!k) break;
            if (!play(x, y, game)) exit(-1);
            if (print) printGame(game);
            if ((won = wonGame(game, aux)))
                break;
            playerNext(game, &x, &y);
            if (!play(x, y, game)) exit(-1);
            printf("%d %d\n", y, x);
        }
    }

    printf("%c venceu\n", won);

    freeGame(game);
    freeGame(aux);
    playerFree();
    return 0;
}
