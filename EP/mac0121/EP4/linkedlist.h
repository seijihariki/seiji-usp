#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "types.h"

node *newNode (char *key);
node *findByKey (llist list, char *key);
node *insertNodeLast (llist *list, char *key);
node *insertNodeByKey (llist *list, char  *key);
node *insertNodeByCnt (llist *list, char  *key);

#endif // LINKEDLIST_H
