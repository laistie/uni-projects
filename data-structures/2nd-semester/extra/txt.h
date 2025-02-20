#include "libraries.h"

#ifndef TXT_H
#define TXT_H

/*MÓDULO PARA TRATAMENTO DE TEXTOS QUE PODERÃO SER INSERIDOS NA ÁRVORE YXX COMO INFO
    STRUCT ESPECÍFICA PARA TEXTOS COM OS PARÂMETROS LIDOS NO ARQUIVO .GEO*/

//ALOCAÇÃO DINÂMICA DA STRUCT PARA TEXTOS
void* newTxt(int id, double x, double y, char colorBorder[20], char colorFill[20], char a, char txt[30]);

void setTxtX(void* element, double x);
void setTxtY(void* element, double y);
void setTxtBorder(void* element, char colorBorder[20]);
void setTxtFill(void* element, char colorFill[20]);

//GETTERS PARA TEXTOS
int getTxtId(void* element);
double getTxtX(void* element);
double getTxtY(void* element);
char* getTxtBorder(void* element);
char* getTxtFill(void* element);
char getA(void* element);
char* getTxt(void* element);

bool checkTxt(void* element, double x1, double y1, double x2, double y2);

#endif