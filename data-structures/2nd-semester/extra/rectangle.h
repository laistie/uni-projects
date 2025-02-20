#include "libraries.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

/*MÓDULO PARA TRATAMENTO DE RETÂNGULOS QUE PODERÃO SER INSERIDOS NA ÁRVORE YXX COMO INFO
    STRUCT ESPECÍFICA PARA RETÂNGULOS COM OS PARÂMETROS LIDOS NO ARQUIVO .GEO*/

//ALOCAÇÃO DINÂMICA DA STRUCT PARA RETÂNGULOS
void* newRect(int id, double x, double y, double w, double h, char colorBorder[20], char colorFill[20]);

void setRectX(void* element, double x);
void setRectY(void* element, double y);
void setRectBorder(void* element, char colorBorder[20]);
void setRectFill(void* element, char colorFill[20]);

//GETTERS PARA RETÂNGULOS
int getRectId(void* element);
double getRectX(void* element);
double getRectY(void* element);
double getRectW(void* element);
double getRectH(void* element);
char* getRectBorder(void* element);
char* getRectFill(void* element);

bool checkRect(void* element, double x1, double y1, double x2, double y2);

#endif