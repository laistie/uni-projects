#include "libraries.h"

#ifndef TXT_H
#define TXT_H

//ALOCACAO DINAMICA DA STRUCT PARA TEXTOS
void* newTxt(int id, double x, double y, char colorBorder[20], char colorFill[20], char a, char txt[30]);

//LIBERACAO DO ESPACO DE MEMORIA DESTINADO AOS TEXTOS
void freeTxt(void* element);

//GETTERS PARA TEXTOS
int getTxtId(void* element);
double getTxtX(void* element);
double getTxtY(void* element);
char* getTxtBorder(void* element);
char* getTxtFill(void* element);
char getA(void* element);
char* getTxt(void* element);

//SETTERS PARA TEXTOS
void setTxtX(void* element, double x);
void setTxtY(void* element, double y);
void setTxtBorder(void* element, char colorBorder[20]);
void setTxtFill(void* element, char colorFill[20]);

#endif