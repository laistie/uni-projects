#include "libraries.h"
#include "geometry.h"
#include "paths.h"

#ifndef SVG_H
#define SVG_H

//CRIACAO DE FILE POINTER PARA ARQUIVO .SVG
FILE* newSvg(char* pathOut, char* filenameGeo);

//FUNCOES DE DESENHO DE FORMAS DO ARQUIVO .GEO
void drawCircle(FILE* svg, int id, double x, double y, double r, char colorBorder[15], char colorFill[15]);
void drawRect(FILE* svg, int id, double x, double y, double w, double h, char colorBorder[15], char colorFill[15]);
void drawLine(FILE* svg, int id, double x1, double y1, double x2, double y2, char color[15]);
void drawText(FILE* svg, int id, double x, double y, char colorBorder[15], char colorFill[15], char a, char txt[30]);

//ENCERRAMENTO DO ARQUIVO .SVG
void closeSvg(FILE* svg);

//ESCRITA DO ARQUIVO .SVG
void writeSvg(FILE* svg, void* geometryList);

#endif