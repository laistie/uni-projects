#include "libraries.h"

#ifndef CIRCLE_H
#define CIRCLE_H

//ALOCACAO DINAMICA DA STRUCT PARA CIRCULOS
void* newCircle(int id, double x, double y, double r, char colorBorder[20], char colorFill[20]);

//LIBERACAO DO ESPAÇO DE MEMORIA DESTINADO AOS CIRCULOS
void freeCircle(void* element);

//GETTERS PARA CIRCULOS
int getCircleId(void* element);
double getCircleX(void* element);
double getCircleY(void* element);
double getCircleR(void* element);
char* getCircleBorder(void* element);
char* getCircleFill(void* element);

//SETTERS PARA CIRCULOS
void setCircleX(void* element, double x);
void setCircleY(void* element, double y);
void setCircleBorder(void* element, char colorBorder[20]);
void setCircleFill(void* element, char colorFill[20]);

#endif