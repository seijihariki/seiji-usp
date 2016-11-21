#include "linkedlist.h"

#include <stdlib.h>

node *newNode (char *key)
{
    node *nd = malloc(sizeof(node));
    nd->key = makeString(key);
    nd->cnt = 0;
    nd->next = 0;
    nd->last = 0;
    return nd;
}

node *findByKey (llist list, char *key)
{
    node *currnode = list;
    string key_str = makeString(key);
    
    while (currnode && str_compare(currnode->key, key_str))
        currnode = currnode->next;
    str_delete(&key_str);
    return currnode;
}

node *insertNodeLast (llist *list, char *key)
{
    if (*list)
    {
        string key_str = makeString(key);
        node *currnode = *list;
        node *lastnode = 0;
        
        while (currnode && str_compare(currnode->key, key_str))
        {
            lastnode = currnode;
            currnode = currnode->next;
        }

        if (currnode)
        {
            currnode->cnt++;
            str_delete(&key_str);
            return currnode;
        } else {
            lastnode->next = newNode(key);
            lastnode->next->cnt++;
            lastnode->next->last = lastnode;
            str_delete(&key_str);
            return lastnode->next;
        }
    } else {
        *list = newNode(key);
        (*list)->cnt++;
        return *list;
    }
}

node *insertNodeByKey (llist *list, char  *key)
{
    if (*list)
    {
        string key_str = makeString(key);
        node *currnode = *list;
        node *lastnode = 0;
        int lastcmp = -1;
        
        while (currnode && (lastcmp = str_compare(currnode->key, key_str)) < 0)
        {
            lastnode = currnode;
            currnode = currnode->next;
        }

        if (!lastcmp)
        {
            str_delete(&key_str);
            currnode->cnt++;
            return currnode;
        } else {
            if (lastnode)
            {
                lastnode->next = newNode(key);
                str_delete(&key_str);
                lastnode->next->cnt++;
                lastnode->next->next = currnode;
                if (lastnode->next->next)
                    lastnode->next->next->last = lastnode->next;
                lastnode->next->last = lastnode;
                return lastnode->next;
            } else {
                *list = newNode(key);
                str_delete(&key_str);
                (*list)->cnt++;
                (*list)->next = currnode;
                if ((*list)->next)
                    (*list)->next->last = *list;
                (*list)->last = (*list);
                return *list;
            }
        }
    } else {
        *list = newNode(key);
        (*list)->cnt++;
        return *list;
    }
}

node *insertNodeByCnt (llist *list, char *key)
{
    if (*list)
    {
        node *result = findByKey(*list, key);
        node *currnode = 0;
        if (!result)
        {
            currnode = *list;
            while (currnode->next) currnode = currnode->next;
            currnode->next = newNode(key);
            currnode->next->last = currnode;
            currnode->next->cnt++;
            return *list;
        } else {
            result->cnt++;
            while (result->last && (result->cnt > result->last->cnt))
            {
                node *prev2, *prev, *next;
                prev2 = result->last->last;
                prev = result->last;
                next = result->next;

                if (!prev2) *list = result;
                else prev2->next  = result;

                if (next)
                    next->last = prev;

                prev->last = result;
                prev->next = next;

                result->last = prev2;
                result->next = prev;
            }
            return result;
        }
    } else {
        *list = newNode(key); 
        (*list)->cnt++;
        return *list;
    }
}

