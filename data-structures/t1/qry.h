#include "libraries.h"
#include "argv.h"
#include "paths.h"
#include "geometry.h"
#include "svg.h"
#include "polygon.h"
#include "coordinates.h"
#include "sel.h"

#ifndef QRY_H
#define QRY_H

//CRIACAO DE FILE POINTER PARA ARQUIVO .TXT DE RELATORIO
FILE* newReport(void* paths);

//ENCERRAMENTO DO ARQUIVO .TXT
void endReport(FILE* txt);

void drawAxis(void* paths);

//FUNCOES PARA FUNCAO INP
void writeInp(FILE* txt, void* polQueue, char type, int id, void* element);
void inp(FILE* txt, void* queue, int id);

//FUNCOES PARA FUNCAO RMP
void writeRmp(FILE* txt, void* polQueue, void* coordinates);
void rmp(FILE* txt, void* queue);

//FUNCOES PARA FUNCAO CLP
void writeClp(FILE* txt, bool removeValue);
void clp(FILE* txt, void* queue);

//FUNCAO PARA FUNCAO POL
void pol(FILE* txt, void* queue, void* paths, int start, double d, double e, char colorBorder[20], char colorFill[20]);

//FUNCOES PARA FUNCAO SEL
void drawGeo(FILE* svg, void* geometryList);
void writeSel(FILE* txt, double x, double y, double w, double h);
bool checkCircle(double circleX, double circleY, double circleR, double areaX, double areaY, double areaW, double areaH);
bool checkRect(double rectX, double rectY, double rectW, double rectH, double areaX, double areaY, double areaW, double areaH);
bool checkLine(double x1, double y1, double x2, double y2, double areaX, double areaY, double areaW, double areaH);
bool checkText(double x, double y, double areaX, double areaY, double areaW, double areaH);
void drawSelected(FILE* svg, double x, double y);
int checkSel(FILE* txt, FILE* svg, void* selectedList, void* geometryList, double x, double y, double w, double h);
int sel(void* paths, FILE* txt, void* selectedList, int selections, void* geometryList, double x, double y, double w, double h);

//FUNCOES PARA FUNCAO SEL+
void writeSelPlus(FILE* txt, double x, double y, double w, double h);
int selPlus(void* paths, FILE* txt, void* selectedList, void* geometryList, double x, double y, double w, double h, int n);

//FUNCOES PARA FUNCAO DELS
void writeDels(FILE* txt);
void dels(void* paths, FILE* txt, void* selectedList, void* geometryList);

//FUNCAO PARA FUNCAO DPS
void dps(void* paths, void* selectedList, void* geometryList, int i, double dx, double dy, char colorBorder[20], char colorFill[20]);

//FUNCAO PARA FUNCAO UPS
void ups(void* paths, void* selectedList, void* geometryList, char colorBorder[20], char colorFill[20], double dx, double dy, int n);

void endQry(void* paths);

//LEITURA DO ARQUIVO DE CONSULTAS .QRY
void readQry(FILE* txt, void* queue, void* paths, void* checkedPaths, void* geometryList);

#endif