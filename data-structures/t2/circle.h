#include "libraries.h"

#ifndef CIRCLE_H
#define CIRCLE_H

//ALOCAÇÃO DINÂMICA DA STRUCT PARA CÍRCULOS
void* newCircle(int id, double x, double y, double r, char colorBorder[20], char colorFill[20]);

//LIBERAÇÃO DO ESPAÇO DE MEMÓRIA DESTINADO AOS CÍRCULOS
void freeCircle(void* element);

//GETTERS PARA CÍRCULOS
int getCircleId(void* element);
double getCircleX(void* element);
double getCircleY(void* element);
double getCircleR(void* element);
char* getCircleBorder(void* element);
char* getCircleFill(void* element);
double getCircleEnergy(void* element);

//ATUALIZAÇÃO DO NÍVEL DE ENERGIA DO CÍRCULO
double updateCircleProtect(void* element, double reduction);

#endif