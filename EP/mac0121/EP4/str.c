#include "str.h"

#include <stdlib.h>

string makeString(char* c_str)
{
    string str;
    int len = strlen(c_str);
    str.c_str = malloc((len + 1)*sizeof(char));
    strcpy(str.c_str, c_str);
    str.len = len;
    return str;
}

string str_append(string *str1, string str2)
{
    int len1 = str1->len;
    int len2 = str2.len;
    int len = len1 + len2;
    str1->c_str = realloc(str1->c_str, (len + 1)*sizeof(char));
    strcpy(str1->c_str + len1, str2.c_str);
    str1->len = len;
    return *str1;
}


string str_copy(string *str1, string str2)
{
    free (str1->c_str);
    str1->c_str = malloc((str2.len + 1)*sizeof(char));
    strcpy(str1->c_str, str2.c_str);
        str1->len = str2.len;
    return *str1;
}

string str_delete(string *str)
{
    free (str->c_str);
    str->c_str = 0;
    str->len = 0;
    return *str;
}

int str_compare(string str1, string str2)
{
    return strcmp(str1.c_str, str2.c_str);
}

