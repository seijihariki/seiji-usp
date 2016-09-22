#ifndef TYPES_H
#define TYPES_H

typedef struct board_s board;
typedef struct stack_s stack;
typedef struct move_s move;

struct stack_s {
    move *data;
    int top, max;
};

struct board_s {
    char *data;
    int sx, sy;
};

struct move_s {
    int i, d;
};

#endif
