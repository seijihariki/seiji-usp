#include "tabelaSimbolo_LD.h"

#include "str.h"
#include "linkedlist.h"
#include "types.h"

llist list;

void insert_LD(char* key, int order)
{
    insertNodeLast(&list, key);
}

void visit_LD(void (*exec)(char*, int), int order)
{
    node *i, *j;
    for (i = list; i->next; i = i->next)
    {
        for (j = i->next; j->next; j = j->next)
        {

        }
    }
    node *currnode = list;
    while (currnode)
    {
        exec(currnode->key.c_str, currnode->cnt);
        currnode = currnode->next;
    }
}
