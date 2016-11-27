#ifndef GAME_HPP
#define GAME_HPP

#define s_x 14
#define s_y 14

struct game_s {
    char board[s_x][s_y];
    char next;
};

typedef struct game_s* Game;

Game makeGame();
int play(int x, int y, Game game);
void undo(int x, int y, Game game);
void reset(Game game);
void freeGame(Game game);

void printGame(Game game);

#endif
