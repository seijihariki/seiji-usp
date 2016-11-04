#include "tabelaSimbolo_VD.h"

#include "str.h"
#include "linkedlist.h"
#include "types.h"

llist list;

void insert_VD(char* key, int order)
{
    if (order) insertNodeByCnt(&list, key);
    else insertNodeByKey(&list, key);
}

void visit_VD(void (*exec)(char*, int), int order)
{
    node *currnode = list;
    while (currnode)
    {
        exec(currnode->key.c_str, currnode->cnt);
        currnode = currnode->next;
    }
}
