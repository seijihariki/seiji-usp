#ifndef STACK_H
#define STACK_H

#include "types.h"

/* Cria uma nova pilha de tamanho  *
 * inicial sz.                     *
 *                                 *
 * Entrada:                        *
 * sz: tamanho inicial da pilha    *
 *                                 *
 * Retorna um ponteiro pra nova    *
 * pilha caso haja sucesso, 0 caso *
 * contrário.                      */
stack newStack(int sz);

/* Deleta a pilha, dealocando *
 * a memoria usada.           *
 *                            *
 * Entrada:                   *
 * st: pilha a ser deletada   */
void delStack(stack st);

/* Empilha um movimento na pilha,   *
 * aumentando ela caso necessario   *
 *                                  *
 * Entrada:                         *
 * st: pilha                        *
 * mv: movimento a ser empilhado    *
 *                                  *
 * Retorna 1 caso tenha conseguido; *
 * 0 caso nao foi possivel o rea-   *
 * locamento da pilha.              */
int pushStack(stack st, move mv);

/* Desempilha um movimento na pilha. *
 *                                   *
 * Entrada:                          *
 * st: pilha                         *
 *                                   *
 * Retorna o movimento retirado.     */
move popStack(stack st);
#endif
