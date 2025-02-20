#include "libraries.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "txt.h"

#ifndef BE_H
#define BE_H

//CRIAÇÃO DA LISTA ENCADEADA PARA ARMAZENAMENTO DE ÁREAS DE FUNÇÕES BE
void* newAreaList();

//ALOCAÇÃO DINÂMICA PARA UMA ÁREA DA FUNÇÃO BE
void* newArea(void* areaList, double x, double y, double w, double h);

//INSERÇÃO DA ÁREA ALOCADA NA LISTA ENCADEADA
void insertArea(void* areaList, double x, double y, double w, double h);

//LIBERAÇÃO DO ESPAÇO ALOCADO PARA A LISTA ENCADEADA E SEUS NÓS
void freeArea(void* areaList);

//GETTERS PARA LISTA DE ÁREAS DE FUNÇÕES BE
double getAreaX(int position);
double getAreaY(int position);
double getAreaW(int position);
double getAreaH(int position);

//FUNÇÃO DE DESENHO DAS ÁREAS DE FUNÇÕES BE NO .SVG
void drawBeArea(FILE* svg);

//FUNÇÃO DE DESENHO DE MARCAÇÃO DA FIGURA NA ÁREA DA FUNÇÃO BE
void drawBe(FILE* svg, double x, double y);

//CHECKERS PARA VERIFICAR SE AS FIGURAS ESTÃO DENTRO DA ÁREA DA FUNÇÃO BE
bool beCheckCircle(double circleX, double circleY, double circleR, double areaX, double areaY, double areaW, double areaH);
bool beCheckRect(double rectX, double rectY, double rectW, double rectH, double areaX, double areaY, double areaW, double areaH);
bool beCheckLine(double x1, double y1, double x2, double y2, double areaX, double areaY, double areaW, double areaH);
bool beCheckText(double x, double y, double areaX, double areaY, double areaW, double areaH);

//ESCRITA DO RELATÓRIO DA FUNÇÃO BE NO .TXT
void writeBe(FILE* txt, void* element, char type, bool activity);

#endif