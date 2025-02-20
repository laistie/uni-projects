#include "libraries.h"

#ifndef CIRCLE_H
#define CIRCLE_H

/*MÓDULO PARA TRATAMENTO DE CÍRCULOS QUE PODERÃO SER INSERIDOS NA ÁRVORE YXX COMO INFO
    STRUCT ESPECÍFICA PARA CÍRCULOS COM OS PARÂMETROS LIDOS NO ARQUIVO .GEO*/

//ALOCAÇÃO DINÂMICA DA STRUCT PARA CÍRCULOS
void* newCircle(int id, double x, double y, double r, char colorBorder[20], char colorFill[20]);

void setCircleX(void* element, double x);
void setCircleY(void* element, double y);
void setCircleBorder(void* element, char colorBorder[20]);
void setCircleFill(void* element, char colorFill[20]);

//GETTERS PARA CÍRCULOS
int getCircleId(void* element);
double getCircleX(void* element);
double getCircleY(void* element);
double getCircleR(void* element);
char* getCircleBorder(void* element);
char* getCircleFill(void* element);

bool checkCircle(void* element, double x1, double y1, double x2, double y2);

#endif