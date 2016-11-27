#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "str.h"
#include "types.h"

#include "tabelaSimbolo_VO.h"
#include "tabelaSimbolo_VD.h"
#include "tabelaSimbolo_LO.h"
#include "tabelaSimbolo_LD.h"
#include "tabelaSimbolo_AB.h"

char *readWord (FILE *file)
{
    int max = 0, top = 0;
    char *str = 0;
    char c;
    while (((c = fgetc(file)) > 0) && !isalpha(c));
    while (isalnum(c))
    {
        if (top + 1 >= max)
            str = realloc(str, sizeof(char)*(max = (2*max + 1)));
        str[top++] = c;
        str[top] = 0;
        c = fgetc(file);
    }
    return str;
}

void print (char* key, int cnt)
{
    printf("%s %d\n", key, cnt);
}

void execute (FILE *file, void (*insert)(char*, int),
        void (*visit)(void (*)(char*, int), int), void (*destroy)(), int order)
{
    char* word;
    while ((word = readWord(file)))
    {
        insert(word, order);
        free(word);
    }

    visit(print, order);
    destroy();
}

implementation getTableType (char *identifier)
{
    if (!strcmp(identifier, "VD"))
        return VD;
    if (!strcmp(identifier, "VO"))
        return VO;
    if (!strcmp(identifier, "LD"))
        return LD;
    if (!strcmp(identifier, "LO"))
        return LO;
    if (!strcmp(identifier, "AB"))
        return AB;
    return NONE;
}

int main (int argc, char **argv)
{
    FILE *file;
    implementation table_type;
    if (argc != 4)
    {
        printf("%s <input file> <symbol table type> <sort by>\n", argv[0]);
        return -1;
    }

    file = fopen(argv[1], "ro");
    
    if (!file)
    {
        printf("Error opening file '%s'!\n", argv[1]);
        return -1;
    }

    table_type = getTableType(argv[2]);

    if (table_type == NONE)
    {
        printf("'%s' is not a table type.\n", argv[2]);
        return -1;
    }

    switch (table_type)
    {
    case VO:
        execute(file, insert_VO, visit_VO, destroy_VO, tolower(*argv[3]) != 'a');
        break;
    case VD:
        execute(file, insert_VD, visit_VD, destroy_VD, tolower(*argv[3]) != 'a');
        break;
    case LO:
        execute(file, insert_LO, visit_LO, destroy_LO, tolower(*argv[3]) != 'a');
        break;
    case LD:
        execute(file, insert_LD, visit_LD, destroy_LD, tolower(*argv[3]) != 'a');
        break;
    case AB:
        execute(file, insert_AB, visit_AB, destroy_AB, tolower(*argv[3]) != 'a');
        break;
    default:
        return -1;
    }

    return 0;
}
