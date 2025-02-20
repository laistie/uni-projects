#include "libraries.h"

#ifndef LINE_H
#define LINE_H

//ALOCACAO DINAMICA DA STRUCT PARA LINHAS
void* newLine(int id, double x1, double y1, double x2, double y2, char color[20]);

//LIBERACAO DO ESPACO DE MEMORIA DESTINADO AS LINHAS
void freeLine(void* element);

//GETTERS PARA LINHAS
int getLineId(void* element);
double getLineX1(void* element);
double getLineY1(void* element);
double getLineX2(void* element);
double getLineY2(void* element);
char* getLineBorder(void* element);

//SETTERS PARA LINHAS
void setLineX1(void* element, double x1);
void setLineY1(void* element, double y1);
void setLineX2(void* element, double x2);
void setLineY2(void* element, double y2);
void setLineColor(void* element, char color[20]);

#endif