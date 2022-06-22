#include "libraries.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

//ALOCACAO DINAMICA DA STRUCT PARA RETANGULOS
void* newRect(int id, double x, double y, double w, double h, char colorBorder[20], char colorFill[20]);

//LIBERACAO DO ESPACO DE MEMORIA DESTINADO AOS RETANGULOS
void freeRect(void* element);

//GETTERS PARA RETANGULOS
int getRectId(void* element);
double getRectX(void* element);
double getRectY(void* element);
double getRectW(void* element);
double getRectH(void* element);
char* getRectBorder(void* element);
char* getRectFill(void* element);

//SETTERS PARA RETANGULOS
void setRectX(void* element, double x);
void setRectY(void* element, double y);
void setRectBorder(void* element, char colorBorder[20]);
void setRectFill(void* element, char colorFill[20]);

#endif