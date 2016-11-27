#include "tabelaSimbolo_LO.h"

#include "str.h"
#include "linkedlist.h"
#include "types.h"

#include <stdlib.h>

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

void destroy_LO()
{
    node *currnode = list, *nextnode;
    while (currnode)
    {
        nextnode = currnode->next;
        str_delete(&currnode->key);
        free(currnode);
        currnode = nextnode;
    }  
}
