#ifndef STR_H
#define STR_H

#include <string.h>

typedef struct str_s
{
    char *c_str;
    int len;
} string;

string makeString(char* c_str);

string str_append(string *str1, string str2);

string str_copy(string *str1, string str2);

string str_delete(string *str);

int str_compare(string str1, string str2);

#endif

