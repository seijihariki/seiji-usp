#ifndef TABELA_S_VD_H
#define TABELA_S_VD_H

void insert_VD(char* key, int order);

void visit_VD(void (*exec)(char*, int), int order);

void destroy_VD();

#endif
