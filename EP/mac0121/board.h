#ifndef BOARD_H
#define BOARD_H

#include "types.h"

/* Cria uma nova mesa.    *
 *                        *
 * Retorna uma nova mesa. */
board newBoard(int sx, int sy);

/* Cria uma mesa a partir *
 * de uma original.       *
 *                        *
 * Retorna a nova mesa.   */
board copyBoard(board bd);

/* Deleta e libera a memoria *
 * de uma mesa.              *
 *                           *
 * Retorna a 'nova' board.   */
board delBoard(board bd);

/* Imprime mesa pra debugging. */
void printBoard(board bd);

/* Inverte mesa. */
void invertBoard(board bd);

/* Valor de (x, y) na mesa. *
 *                          *
 * Retorna o valor.         */
char atBoard(board bd, int x, int y);

/* Muda valor de (x, y) na mesa *
 * pra v.                       */
void setBoard(board bd, int x, int y, char v);

/* Como a mesa e representada por um *
 * unico vetor, converte de (x, y)   *
 * para o indice correspondente.     *
 *                                   *
 * Retorna indice do vetor.          */
int getIBoard(board bd, int x, int y);

/* Como a mesa e representada por um unico vetor, *
 * converte do indice i do vetor para (x, y).     */
void getXYBoard(board bd, int i, int *x, int *y);

/* Converte de coordenadas e direcao para um *
 * objeto de movimento.                      *
 *                                           *
 * Retorna o movimento correspondente.       */
move getMove(board bd, int x, int y, int d);

/* Aplica movimento na mesa. App precisa          *
 * receber 1. Caso receba -1, desfaz o movimento. *
 *                                                *
 * Retorna 1 caso sucesso, 0 caso contrario.      */
int applyMove(board bd, move mv, int app);

/* Usa a funcao applyMove para defazer o movimento. */
int undoMove(board bd, move mv);

/* Compara mesas.                           *
 *                                          *
 * Retorna 1 caso iguais, 0 caso contrario. */
int eqBoard(board bd1, board bd2);

/* Calcula proximo movimento.   *
 *                              *
 * Retorna o proximo movimento. */
move nextMove(move mv);

/* Calcula as coordenadas de certo movimento   *
 * numa mesa dada. 0: origem, 1: intermediario *
 * e 2: final                                  */
void moveCoords(board bd, move mv, int *x0, int *y0, int *x1, int *y1, int *x2, int *y2);
#endif
