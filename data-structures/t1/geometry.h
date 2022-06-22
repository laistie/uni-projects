#include "libraries.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "txt.h"

#ifndef GEOMETRY_H
#define GEOMETRY_H

//ALOCAO DINAMICA DA LISTA DUPLAMENTE ENCADEADA DAS FIGURAS SELECIONADAS
void* newGeoList();

//CRIACAO DE ELEMENTO DA LISTA
void* newGeo(void* geometryList, char elementType, void* element);

//INSERCAO DE ELEMENTO CRIADO NA LISTA
void insertGeo(void* geometryList, char elementType, void* element);

//GETTER PARA TIPO DE ELEMENTO
char getElementType();

//LIBERACAO DO ESPACO ALOCADO PARA A LISTA
void freeGeoList(void* geometryList);

//DEBUG: MOSTRA TODOS OS TIPOS DE ELEMENTOS ADICIONADOS NA LISTA
void printGeoList();

//GETTERS PARA LISTA
int getGeoSize();
char getCurrentType(int visits);
void* getCurrentElement(int visits);
void* getNextElement(int visits);
void* getPrevElement(int visits);

double getX(int position, char type);
double getY(int position, char type);

#endif