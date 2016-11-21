#ifndef TABELA_S_VO_H
#define TABELA_S_VO_H

void insert_VO(char* key, int order);

void visit_VO(void (*exec)(char*, int), int order);

void destroy_VO();

#endif
