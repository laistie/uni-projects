#include "libraries.h"
#include "SRbTree.h"
#include "info.h"
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

//ESCRITA DO ARQUIVO .SVG
void writeSvg(FILE* svg, SRbTree tree);

#endif