#ifndef TABELA_S_LO_H
#define TABELA_S_LO_H

void insert_LO(char* key, int order);

void visit_LO(void (*exec)(char*, int), int order);

void destroy_LO();

#endif
