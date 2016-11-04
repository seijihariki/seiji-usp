#include "tabelaSimbolo_VD.h"

#include "str.h"
#include "types.h"

#include <stdlib.h>

vector vect;

void insert_VD(char* key, int order)
{
    string key_str = makeString(key);
    for (int i = 0; i < vect.top; i++)
    {
        if (!str_compare(vect.data[i].key, key_str))
        {
            vect.data[i].cnt++;
            str_delete(&key_str);
            return;
        }
    }

    if (vect.max <= vect.top)
    {
        vect.max = 2*vect.max + 1;
        vector_item *new_v = realloc(vect.data, vect.max*sizeof(vector_item));
        vect.data = new_v;
    }
    
    vect.data[vect.top].key = key_str;
    vect.data[vect.top++].cnt = 0;
}

int cmpKey(const void *a, const void *b)
{
    const vector_item *i1, *i2;
    i1 = a;
    i2 = b;
    return str_compare(i1->key, i2->key);
}

int cmpCnt(const void *a, const void *b)
{
    const vector_item *i1, *i2;
    i1 = a;
    i2 = b;
    if (i1->cnt != i2->cnt)
       return i1->cnt - i2->cnt;
    return str_compare(i1->key, i2->key);
}

void visit_VD(void (*exec)(char*, int), int order)
{
    qsort(vect.data, vect.top, sizeof(vector_item), order?cmpCnt:cmpKey);
    for (int i = 0; i < vect.top; i++)
        exec(vect.data[i].key.c_str, vect.data[i].cnt);
}
