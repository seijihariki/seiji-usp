#ifndef TABELA_S_LD_H
#define TABELA_S_LD_H

void insert_LD(char* key, int order);

void visit_LD(void (*exec)(char*, int), int order);

#endif 
