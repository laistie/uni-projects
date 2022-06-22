#include "libraries.h"
#include "coordinates.h"
#include "geometry.h"

#ifndef POLYGON_H
#define POLYGON_H

#define MAX_QUEUE 100

//ALOCACAO DINAMICA DA FILA ESTATICA DESTINADA AO POLIGONO
void* newPolQueue(int size);

//FUNCOES PARA SABER SE A FILA ESTA CHEIA OU VAZIA
bool isFull(void* polQueue);
bool isEmpty(void* polQueue);

//FUNCOES PARA INSERIR E REMOVER COORDENADAS DA FILA
void enqueue(void* polQueue, char type, int id, int position);
void dequeue(void* polQueue, void* coordinates);

//GETTERS PARA FILA CIRCULAR
void* getCurrentCoordinates(void* polQueue);
void* getFirstCoordinates(void* polQueue);
void* getCoordinatesAt(void* polQueue, int position);

//FUNCOES PARA DESENHAR NO SVG
void drawPolLines(FILE* svg, void* polQueue, int start, int sides, double d, double e, char color[15], double minX, double maxX, double minY, double maxY);
void drawPolygon(FILE* svg, void* polQueue, int start, double d, double e, char colorBorder[15], char colorFill[15]);

//FUNCOES PARA LIBERAR ESPACO DESTINADO A FILA CIRCULAR
bool freeAllCoordinates(void* polQueue);
void freePolQueue(void* polQueue);

#endif