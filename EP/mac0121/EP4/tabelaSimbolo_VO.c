#include "tabelaSimbolo_VO.h"

#include "str.h"
#include "types.h"

#include <stdlib.h>

vector vect;

void insert_VO(char* key, int order)
{
    string key_str = makeString(key);
    int i, j;
    vector_item *new_v;
    int first_gt1 = -1;

    for (i = 0; i < vect.top; i++)
    {
        int compar_result = str_compare(vect.data[i].key, key_str);

        if (first_gt1 < 0 && vect.data[i].cnt > 1)
            first_gt1 = i;

        if (!compar_result)
        {
            vect.data[i].cnt++;
            str_delete(&key_str);
            while (order && i < vect.top - 1
                    && vect.data[i + 1].cnt < vect.data[i].cnt)
            {
                vector_item item = vect.data[i];
                vect.data[i] = vect.data[i + 1];
                vect.data[i + 1] = item;
                i++;
            }
            return;
        } else if (compar_result > 0 && !order)
            break;
    }

    if (vect.max <= vect.top)
    {
        vect.max = 2*vect.max + 1;
        new_v = realloc(vect.data, vect.max*sizeof(vector_item));
        vect.data = new_v;
    }

    if (order && first_gt1 >= 0)
        i = first_gt1;

    for (j = vect.top++ - 1; j >= i; j--)
        vect.data[j + 1] = vect.data[j];
    
    vect.data[i].key = key_str;
    vect.data[i].cnt = 1;
}

void visit_VO(void (*exec)(char*, int), int order)
{
    int i;
    for (i = 0; i < vect.top; i++)
        exec(vect.data[i].key.c_str, vect.data[i].cnt);
}
