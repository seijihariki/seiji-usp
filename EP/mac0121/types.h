#ifndef TYPES_H
#define TYPES_H

typedef struct board_s board;
typedef struct stack_s *stack;
typedef struct move_s move;

/* Struct do objeto de stack.         *
 * data: Dados armazenados na stack   *
 * top: Topo atual na stack           *
 * max: Tamanho maximo atual da stack */
struct stack_s {
    move *data;
    int top, max;
};

/* Struct do objeto de mesa.          *
 *                                    *
 * data: Dados da mesa                *
 * sx: Tamanho horizontal da mesa     *
 * sy: Tamanho vertical da mesa       */
struct board_s {
    char *data;
    int sx, sy;
};

/* Struct do objeto de movimento. *
 *                                *
 * i: Indice da posicao na mesa   *
 * d: Direcao do movimento        */
struct move_s {
    int i, d;
};

#endif
