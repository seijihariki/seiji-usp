#include "tabelaSimbolo_LD.h"

#include "str.h"
#include "linkedlist.h"
#include "types.h"

#include <stdlib.h>

llist list;

void insert_LD(char* key, int order)
{
    insertNodeLast(&list, key);
}

void visit_LD(void (*exec)(char*, int), int order)
{
    node *i, *j, *tmp;
    node *ci, *cj;
    node *liptr, *niptr, *ljptr, *njptr;
    node *currnode;
    for (i = list; i->next; i = i->next)
    {
        for (j = i->next; j; j = j->next)
        {
            if (((!order && str_compare(i->key, j->key) > 0)
                        || (order && i->cnt < j->cnt)))
            {
                ci = i;
                cj = j;
                liptr = i->last;
                njptr = j->next;

                if (njptr)
                    njptr->last = ci;
                if (liptr)
                    liptr->next = cj;

                if (i->next == j)
                {
                    ci->last = cj;
                    cj->next = ci;
                ci->next = njptr;
                cj->last = liptr;
                } else {
                    niptr = i->next;
                    ljptr = j->last;

                    ci->last = ljptr;
                ci->next = njptr;
                cj->last = liptr;
                    cj->next = niptr;

                    if (ljptr)
                        ljptr->next = ci;
                    if (niptr)
                        niptr->last = cj;
                }
                tmp = i;
                i = j;
                j = tmp;
            }
        }
    }

    currnode = list;

    while (currnode)
    {
        exec(currnode->key.c_str, currnode->cnt);
        currnode = currnode->next;
    }
}

void destroy_LD()
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
