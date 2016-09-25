#ifndef CVECTOR_H
#define CVECTOR_H

#include "types.h"

/* Cria um novo vetor circular de  *
 * tamanho sz.                     *
 *                                 *
 * Retorna um ponteiro pro novo    *
 * vetor caso haja sucesso, 0 caso *
 * contrario.                      */
cvector newCVector(int sz);

/* Deleta a stack, dealocando *
 * a memoria usada.           */
void delCVector(cvector cv);

/* Valor de uma posicao do vetor. *
 *                                */
int atCVector(cvector cv, int i);

/* Mudar valor de uma posicao no vetor . *
 *                                       */
void setCVector(cvector cv, int i, int v);

/* Fazer uma 3-rotacao. *
 *                      */
void threeRotate(cvector cv, int i);
#endif
