#include "libraries.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

//ALOCAÇÃO DINÂMICA DA STRUCT PARA RETÂNGULOS
void* newRect(int id, double x, double y, double w, double h, char colorBorder[20], char colorFill[20]);

//LIBERAÇÃO DO ESPAÇO DE MEMÓRIA DESTINADO AOS RETÂNGULOS
void freeRect(void* element);

//GETTERS PARA RETÂNGULOS
int getRectId(void* element);
double getRectX(void* element);
double getRectY(void* element);
double getRectW(void* element);
double getRectH(void* element);
char* getRectBorder(void* element);
char* getRectFill(void* element);
double getRectEnergy(void* element);

//ATUALICAÇÃO DO NÍVEL DE ENERGIA DO RETÂNGULO
double updateRectProtect(void* element, double reduction);

#endif