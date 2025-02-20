#include "libraries.h"

#ifndef COORDINATES_H
#define COORDINATES_H

//ALOCACAO DA STRUCT DE COORDENADAS DO POLIGONO
void* newCoordinates();

//INSERCACAO DE COORDENADAS
void insertCoordinates(void* coordinates, double x, double y);

//LIBERACAO DO ESPACO ALOCADO PARA AS COORDENADAS
void freeCoordinates(void* coordinates);

//GETTERS PARA STRUCT DE COORDENADAS
double getCoordX(void* coordinates);
double getCoordY(void* coordinates);

#endif