#ifndef GAME_HPP
#define GAME_HPP

#define s_x 14
#define s_y 14

struct game_s {
    int board[s_x][s_y];
    char next;
    int round;
    int swap;
};

typedef struct game_s* Game;

Game makeGame();
int atGame(Game game, int x, int y);
void setGame(Game game, int x, int y, int v);
int play(int x, int y, Game game);
void undo(int x, int y, Game game);
void reset(Game game);
void freeGame(Game game);

void printGame(Game game);

#endif
