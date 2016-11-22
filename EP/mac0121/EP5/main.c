#include "player.c"

int main(int argc, char **argv)
{
    char color = 0;
    char print = 0;
    if (argc > 1)
        color = (argv[1][0] == 'P')?'B':'W';
    if (argc == 3)
        print = argv[2][0];
}
