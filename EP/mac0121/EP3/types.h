#ifndef TYPES_H
#define TYPES_H

/* Struct do objeto de stack.         *
 * data: Dados armazenados na stack   *
 * top: Topo atual na stack           *
 * max: Tamanho maximo atual da stack */
struct stack_s {
    int *data;
    int top, max;
};

/* Struct do objeto do vetor circular. *
 *                                     *
 * data: Dados do vetor                *
 * sx: Tamanho do vetor                */
struct cvector_s {
    int *data;
    int sz;
};

typedef struct cvector_s *cvector;
typedef struct stack_s *stack;
#endif
