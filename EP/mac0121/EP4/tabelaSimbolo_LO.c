#include "tabelaSimbolo_LO.h"

#include "str.h"
#include "linkedlist.h"
#include "types.h"

llist list;

void insert_LO(char* key, int order)
{
    if (order) insertNodeByCnt(&list, key);
    else insertNodeByKey(&list, key);
}

void visit_LO(void (*exec)(char*, int), int order)
{
    node *currnode = list;
    while (currnode)
    {
        exec(currnode->key.c_str, currnode->cnt);
        currnode = currnode->next;
    }
}
