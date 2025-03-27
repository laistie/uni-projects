#include "libraries.h"

#ifndef LISTA_H
#define LISTA_H

typedef void* Lista;

Lista newList();

void insertList(Lista list, char type, double x, double y, double w, double h);

void markD(FILE* pSvg, Lista list);
void markLr(FILE* pSvg, Lista list);

void freeList(char type, Lista list);

#endif