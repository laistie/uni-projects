#include "libraries.h"

#ifndef _RECTANGLE_H
#define _RECTANGLE_H

/*MÓDULO PARA TRATAMENTO DE RETÂNGULOS QUE PODERÃO SER INSERIDOS NA SRB TREE COMO INFO
    STRUCT ESPECÍFICA PARA RETÂNGULOS COM OS PARÂMETROS LIDOS NO ARQUIVO .GEO*/

//ALOCAÇÃO DINÂMICA DA STRUCT PARA RETÂNGULOS
void* newRect(int id, double x, double y, double w, double h, char colorBorder[20], char colorFill[20]);

//SETTERS PARA RETÂNGULOS
void setRectX(void* element, double x);
void setRectY(void* element, double y);
void setRectBorder(void* element, char colorBorder[20]);
void setRectFill(void* element, char colorFill[20]);
void setRectEnergy(void* element, double e);

//GETTERS PARA RETÂNGULOS
int getRectId(void* element);
double getRectX(void* element);
double getRectY(void* element);
double getRectW(void* element);
double getRectH(void* element);
char* getRectBorder(void* element);
char* getRectFill(void* element);
double getRectEnergy(void* element);

bool checkRectHit(double x, double y, double w, double h, double hitX, double hitY);

#endif