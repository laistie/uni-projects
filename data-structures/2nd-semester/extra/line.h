#include "libraries.h"

#ifndef LINE_H
#define LINE_H

/*MÓDULO PARA TRATAMENTO DE LINHAS QUE PODERÃO SER INSERIDAS NA ÁRVORE YXX COMO INFO
    STRUCT ESPECÍFICA PARA LINHAS COM OS PARÂMETROS LIDOS NO ARQUIVO .GEO*/

//ALOCAÇÃO DINÂMICA DA STRUCT PARA LINHAS
void* newLine(int id, double x1, double y1, double x2, double y2, char color[20]);

void setLineX1(void* element, double x);
void setLineY1(void* element, double y);
void setLineX2(void* element, double x);
void setLineY2(void* element, double y);
void setLineColor(void* element, char color[20]);

//GETTERS PARA LINHAS
int getLineId(void* element);
double getLineX1(void* element);
double getLineY1(void* element);
double getLineX2(void* element);
double getLineY2(void* element);
char* getLineBorder(void* element);

bool checkLine(void* element, double x1, double y1, double x2, double y2);

#endif