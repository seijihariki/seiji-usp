#ifndef BOARD_H
#define BOARD_H

#include "types.h"

/* Cria uma nova mesa.    *
 *                        *
 * Entrada:               *
 * sx: Tamanho horizontal *
 * sy: Tamanho vertical   *
 *                        *
 * Retorna uma nova mesa. */
board newBoard(int sx, int sy);

/* Cria uma mesa igual a  *
 * uma original dada.     *
 *                        *
 * Entrada:               *
 * bd: mesa original      *
 *                        *
 * Retorna a nova mesa.   */
board copyBoard(board bd);

/* Deleta e libera a memoria *
 * de uma mesa.              *
 *                           *
 * Entrada:                  *
 * bd: mesa a deletar        *
 *                           *
 * Retorna o objeto board.   */
board delBoard(board bd);

/* Imprime mesa pra debugging. *
 *                             *
 * Entrada:                    *
 * bd: mesa a imprimir         */
void printBoard(board bd);

/* Inverte mesa.       *
 *                     *
 * Entrada:            *
 * bd: mesa a inverter */
void invertBoard(board bd);

/* Valor de (x, y) na mesa. *
 *                          *
 * Entrada:                 *
 * bd: mesa                 *
 * x: coordenada x na mesa  *
 * y: coordenada y na mesa  *
 *                          *
 * Retorna o valor.         */
char atBoard(board bd, int x, int y);

/* Muda valor de (x, y) na mesa *
 * pra v.                       *
 *                              *
 * Entrada:                     *
 * bd: mesa                     *
 * x: coordenada x na mesa      *
 * y: coordenada y na mesa      *
 * v: valor que (x, y) sera     */
void setBoard(board bd, int x, int y, char v);

/* Como a mesa e representada por um *
 * unico vetor, converte de (x, y)   *
 * para o indice correspondente.     *
 *                                   *
 * Entrada:                          *
 * bd: mesa                          *
 * x: coordenada x na mesa           *
 * y: coordenada y na mesa           *
 *                                   *
 * Retorna indice do vetor.          */
int getIBoard(board bd, int x, int y);

/* Como a mesa e representada por um unico vetor, *
 * converte do indice i do vetor para (x, y).     *
 *                                   *
 * Entrada:                          *
 * bd: mesa                          *
 * i: indice para a conversao        *
 * x: recebe coordenada x na mesa    *
 * y: recebe coordenada y na mesa    */
void getXYBoard(board bd, int i, int *x, int *y);

/* Converte de coordenadas e direcao para um *
 * objeto de movimento.                      *
 *                                           *
 * Entrada:                                  *
 * bd: mesa                                  *
 * x: coordenada x na mesa                   *
 * y: coordenada y na mesa                   *
 * d: direcao do movimento                   *
 *                                           *
 * Retorna o movimento correspondente.       */
move getMove(board bd, int x, int y, int d);

/* Aplica movimento na mesa.                       *
 *                                                 *
 * Entrada:                                        *
 * bd: mesa                                        *
 * mv: movimento a ser aplicado                    *
 * app: 1 caso precise executar movimento, -1 caso *
 * precise desfaze-lo                              *
 *                                                 *
 * Retorna 1 caso sucesso, 0 caso contrario.       */
int applyMove(board bd, move mv, int app);

/* Usa a funcao applyMove para defazer o movimento. *
 *                                                  *
 * Entrada:                                         *
 * bd: mesa                                         *
 * mv: movimento a ser desfeito                     *
 *                                                  *
 * Retorna 1 caso sucesso, 0 caso contrario.        */
int undoMove(board bd, move mv);

/* Compara mesas.                           *
 *                                          *
 * Entrada:                                 *
 * bd1: mesa 1 a ser comparada              *
 * bd2: mesa 2 a ser comparada              *
 *                                          *
 * Retorna 1 caso iguais, 0 caso contrario. */
int eqBoard(board bd1, board bd2);

/* Calcula proximo movimento a  *
 * partir de um dado.           *
 *                              *
 * Entrada:                     *
 * mv: movimento dado           *
 *                              *
 * Retorna o proximo movimento. */
move nextMove(move mv);

/* Calcula as coordenadas de certo movimento   *
 * numa mesa dada. 0: origem, 1: intermediario *
 * e 2: final                                  *
 *                                             *
 * Entrada:                                    *
 * bd: mesa                                    *
 * mv: movimento dado                          *
 * x0: coordenada x da peca a ser movida       *
 * y0: coordenada y da peca a ser movida       *
 * x1: coordenada x da peca a ser retirada     *
 * y1: coordenada y da peca a ser retirada     *
 * x2: coordenada x do local final da peca     *
 * y2: coordenada y do local final da peca     */
void moveCoords(board bd, move mv, int *x0, int *y0, int *x1, int *y1, int *x2, int *y2);
#endif
