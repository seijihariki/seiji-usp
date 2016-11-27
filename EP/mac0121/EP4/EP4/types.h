#ifndef TYPES_H
#define TYPES_H

#include "str.h"
#include <string.h>

typedef struct node_s node;

struct node_s 
{
    string key;
    int cnt;
    node *next, *last;
};

typedef node* llist;

typedef struct vect_i_s
{
    string key;
    int cnt;
} vector_item;

typedef struct vect_s
{
    vector_item *data;
    int top, max;
} vector;

enum implementation_e
{
    VO,
    VD,
    LO,
    LD,
    AB,
    NONE
};

typedef enum implementation_e implementation;

typedef struct b_node_s b_node;

struct b_node_s
{
    string key;
    int cnt;
    b_node *lchild, *rchild;
};

typedef b_node* bin_tree;
#endif
