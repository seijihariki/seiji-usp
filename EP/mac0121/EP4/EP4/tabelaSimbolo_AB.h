#ifndef TABELA_S_AB_H
#define TABELA_S_AB_H

void insert_AB(char* key, int order);

void visit_AB(void (*exec)(char*, int), int order);

void destroy_AB();

#endif
