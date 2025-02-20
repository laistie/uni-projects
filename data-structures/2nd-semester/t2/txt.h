#include "libraries.h"

#ifndef TXT_H
#define TXT_H

//ALOCAÇÃO DINÂMICA DA STRUCT PARA TEXTOS
void* newTxt(int id, double x, double y, char colorBorder[20], char colorFill[20], char a, char txt[30]);

//LIBERACAO DO ESPAÇO DE MEMORIA DESTINADO AOS TEXTOS
void freeTxt(void* element);

//GETTERS PARA TEXTOS
int getTxtId(void* element);
double getTxtX(void* element);
double getTxtY(void* element);
char* getTxtBorder(void* element);
char* getTxtFill(void* element);
char getA(void* element);
char* getTxt(void* element);
double getTxtEnergy(void* element);

//ATUALIZAÇÃO DO NÍVEL DE ENERGIA DO TEXTO
double updateTxtProtect(void* element, double reduction);

#endif