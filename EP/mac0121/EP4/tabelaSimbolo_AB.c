#include "tabelaSimbolo_AB.h"

#include "str.h"
#include "linkedlist.h"
#include "types.h"

#include <stdlib.h>

bin_tree tree;

void insert_AB(char* key, int order)
{
    bin_tree current;
    b_node **to_change;
    int comp;
    string key_str = makeString(key);
    if (!tree)
    {
        tree = malloc(sizeof(b_node));
        tree->key = key_str;
        tree->cnt = 1;
        tree->lchild = tree->rchild = 0;
    }

    current = tree;

    comp = str_compare(key_str, current->key);
    while (comp)
    {
        if (comp > 0)
        {
            if (!current->rchild)
                break;
            current = current->rchild;
        }
        else
        {
            if (!current->lchild)
                break;
            current = current->lchild;
        }
        comp = str_compare(key_str, current->key);
    }

    if (!comp)
    {
        current->cnt++;
        str_delete(&key_str);
        return;
    }

    if (comp > 0)
        to_change = &current->rchild;
    else
        to_change = &current->lchild;

    *to_change = malloc(sizeof(b_node));
    (*to_change)->key = key_str;
    (*to_change)->cnt = 1;
    (*to_change)->lchild = (*to_change)->rchild = 0;

}

void visit_rec(void (*exec)(char*, int), bin_tree subtree)
{
    if (subtree->lchild)
        visit_rec(exec, subtree->lchild);
    if (exec)
        exec(subtree->key.c_str, subtree->cnt);
    if (subtree->rchild)
        visit_rec(exec, subtree->rchild);
}

int make_vec_rec(b_node ***nodes, int *cnt, int *max, bin_tree subtree)
{
    int loc_max = 0;
    int loc_cnt = 0;

    if (!max || !cnt)
    {
        max = &loc_max;
        cnt = &loc_cnt;
    }

    if (subtree->lchild)
        make_vec_rec(nodes, cnt, max, subtree->lchild);
    if (*cnt >= *max)
    {
        *max = 2**max + 1;
        **nodes = realloc(nodes, sizeof(b_node*)**max);
    }
    (*nodes)[*cnt++] = subtree;
    if (subtree->rchild)
        make_vec_rec(nodes, cnt, max, subtree->rchild);

    return loc_cnt;
}

int compare(const void* a, const void* b)
{
    return ((b_node*)a)->cnt - ((b_node*)b)->cnt;
}

void visit_AB(void (*exec)(char*, int), int order)
{
    int i;
    if (!order) visit_rec(exec, tree);
    else {
        b_node **nodevec;
        int sz = make_vec_rec(&nodevec, 0, 0, tree);
        qsort(nodevec, sz, sizeof(b_node*), compare);
        for (i = 0; i < sz; i++)
            exec(nodevec[i]->key.c_str, nodevec[i]->cnt);
    }
}
