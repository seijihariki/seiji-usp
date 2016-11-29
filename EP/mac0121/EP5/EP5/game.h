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

/* Creates new game object. Allocated memory for it and returns pointer.    *
 *                                                                          *
 * Returns pointer to new instance of Game.                                 */
Game makeGame();

/* Returns current value in certain board position. Returns -1 if outside   *
 * bounds.                                                                  *
 *                                                                          *
 * Params:                                                                  *
 * game: Game board                                                         *
 * x: Board's x coordinate                                                  *
 * y: Board's y coordinate                                                  *
 *                                                                          *
 * Returns value at coordinates x, y in board given. -1 if outside bounds.  */
int atGame(Game game, int x, int y);

/* Sets specified board coordinate's value to v. Doesn't do anything if out *
 * of bounds.                                                               *
 *                                                                          *
 * Params:                                                                  *
 * game: Game board                                                         *
 * x: Board's x coordinate                                                  *
 * y: Board's y coordinate                                                  *
 * v: Value to put at (x, y)                                                */
void setGame(Game game, int x, int y, int v);

/* Plays at given coordinates. Swaps color when necessary, and returns 0 on *
 * failed play.                                                             *
 *                                                                          *
 * Params:                                                                  *
 * game: Game board                                                         *
 * x: Board's x coordinate to play at                                       *
 * y: Board's y coordinate to play at                                       *
 *                                                                          *
 * Returns 1 when play is sucessful, 0 if not.                              */
int play(int x, int y, Game game);

/* Undoes play played at x, y, effectively undoing a 'play' call with same  *
 * arguments.                                                               *
 *                                                                          *
 * Params:                                                                  *
 * game: Game board                                                         *
 * x: Board's x coordinate to undo                                          *
 * y: Board's y coordinate to undo                                          */
void undo(int x, int y, Game game);

/* Resets board object to initial state (all zeros, round 0, and player W)  *
 *                                                                          *
 * Params:                                                                  *
 * game: Game board to be reseted                                           */
void reset(Game game);

/* Frees alocated memory to given game pointer.                             *
 *                                                                          *
 * Params:                                                                  *
 * game: Game board to be freed                                             */
void freeGame(Game game);

/* Prints board to stderr. If __DEBUG__ is defined, prints with colors and  *
 * formatted output.                                                        *
 *                                                                          *
 * Params:                                                                  *
 * game: Game board to print                                                */
void printGame(Game game);

/* Returns which player won, or 0 if none.                                  *
 *                                                                          *
 * Params:                                                                  *
 * game: Game board                                                         *
 * aux: Auxiliar board                                                      *
 *                                                                          *
 * Returns P or B, depending on the winning player. Returns 0 is none won.  */
char wonGame(Game game, Game aux);

#endif
