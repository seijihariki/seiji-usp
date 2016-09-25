#ifndef STACK_H
#define STACK_H

#include "types.h"

/* Cria uma nova stack de tamanho  *
 * inicial sz.                     *
 *                                 *
 * Retorna um ponteiro pra nova    *
 * stack caso haja sucesso, 0 caso *
 * contrário.                      */
stack newStack(int sz);

/* Deleta a stack, dealocando *
 * a memoria usada.           */
void delStack(stack st);

/* Empilha um movimento na stack,  *
 * aumentando ela caso necessario  *
 *                                 *
 * Retorna 1 caso tenha conseguido *
 * 0 caso nao foi possivel o rea-  *
 * locamento da stack.             */
int pushStack(stack st, move mv);

/* Desempilha um movimento na stack. *
 *                                   *
 * Retorna o movimento retirado.     */
move popStack(stack st);
#endif
