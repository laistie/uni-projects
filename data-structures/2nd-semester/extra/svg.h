#include "libraries.h"
#include "yxxtree.h"
#include "list.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "txt.h"

#ifndef SVG_H
#define SVG_H

/*MÓDULO DESTINADO À MANIPULAÇÃO DO ARQUIVO .SVG*/

//CRIAÇÃO DE FILE POINTER PARA ARQUIVO .SVG
FILE* newSvg(char* pathOut, char* filenameGeo);

//ENCERRAMENTO DO ARQUIVO .SVG
void closeSvg(FILE *svg);

void printTSvg(Info i, double x, double y, void *aux);

//ESCRITA DO ARQUIVO .SVG
void writeSvg(FILE* svg, YxxTree tree);

void updateTSvg(Info i, double x, double y, void *aux);
void updateDpsSvg(FILE* pSvg, YxxTree tree, List list, int i, double dx, double dy, char colorBorder[20], char colorFill[20]);
void updateUpsSvg(FILE* pSvg, List list, char colorBorder[20], char colorFill[20], double dx, double dy, int n);

#endif