#include "libraries.h"

#ifndef LINE_H
#define LINE_H

//ALOCAÇÃO DINÂMICA DA STRUCT PARA LINHAS
void* newLine(int id, double x1, double y1, double x2, double y2, char color[20]);

//LIBERAÇÃO DO ESPAÇO DE MEMÓRIA DESTINADO ÀS LINHAS
void freeLine(void* element);

//GETTERS PARA LINHAS
int getLineId(void* element);
double getLineX1(void* element);
double getLineY1(void* element);
double getLineX2(void* element);
double getLineY2(void* element);
char* getLineBorder(void* element);
double getLineEnergy(void* element);

//ATUALIZAÇÃO DO NÍVEL DE ENERGIA DA LINHA
double updateLineProtect(void* element, double reduction);

#endif