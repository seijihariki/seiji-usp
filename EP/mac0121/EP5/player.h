#ifndef PLAYER_HPP
#define PLAYER_HPP

/* Gets computer player next move. Return 1 if successful, 0 if not.        *
 *                                                                          *
 * Params:                                                                  *
 * game: Game board where to play                                           *
 * x: Pointer to where it should store the x coordinate to the next play    *
 * y: Pointer to where it should store the y coordinate to the next play    *
 *                                                                          *
 * Returns 1 if successfuly found, 0 if an error occurred.                  */
int playerNext(Game game, int *x, int *y);

/* Frees globally allocated player variables.                               */
void playerFree();

#endif
