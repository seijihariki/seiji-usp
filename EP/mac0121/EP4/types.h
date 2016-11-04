#ifndef TYPES_H
#define TYPES_H

#include "str.h"
#include <string.h>

typedef struct node_s node;

typedef struct node_s 
{
    string key;
    int cnt;
    node *next, *last;
} node;

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

#endif // TYPES_H
