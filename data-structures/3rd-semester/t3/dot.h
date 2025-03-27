#ifndef _DOT_H
#define _DOT_H

#include "libraries.h"

/*MÓDULO DESTINADO PARA PRODUÇÃO DE ARQUIVO .DOT*/

void newGraph(char* pathOut, char* filenameGeo);

//FUNÇÕES DE IMPRESSÃO NO ARQUIVO .DOT
void printNode(FILE* pDot, char* color, int id, double x, double y);
void printLink(FILE* pDot, int id, int parentId);
void printNLink(FILE* pDot, char* nil, int parentId);

void endGraph(char* filename);

#endif