#include "libraries.h"
#include "paths.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "txt.h"

#ifndef TORPEDO_H
#define TORPEDO_H

//ALOCAÇÃO DINÂMICA PARA LISTA DUPLAMENTE ENCADEADA DE TORPEDOS
void* newTorpedoList();

//ALOCAÇÃO E INSERÇÃO DE NOVO TORPEDO À LISTA
void* newTorpedo(void* torpedoList, double x, double y, int n);
void insertTorpedo(void* torpedoList, char type, double x, double y, int n);

//GETTERS PARA LISTA DE TORPEDOS
double getTpX(char type, int position);
double getTpY(char type, int position);
int getTpN(char type, int position);

//LIBERAÇÃO DO ESPAÇO DE MEMÓRIA ALOCADO PARA A LISTA E SEUS NÓS
void freeTorpedo(char type, void* torpedoList);

//CHECKERS PARA PONTO DENTRO DAS FIGURAS GEOMÉTRICAS
bool checkCircle(void* element, double x, double y);
bool checkRect(void* element, double x, double y);
bool checkLine(void* element, double x, double y);
bool checkTxt(void* element, double x, double y);

//FUNÇÕES PARA DESENHAR TORPEDOS
void mark(FILE* pfileSvg, void* tpList);
void markTr(FILE* pfileSvg, void* trList);

//ESCRITA DO RELATÓRIO DA FUNÇÃO TP NO .TXT
void writeTp(FILE* txt, void* element, char type);
void writeNotTp(FILE* txt, double x, double y);

//ESCRITA DO RELATÓRIO DA FUNÇÃO TR NO .TXT
void writeTr(FILE* txt, void* element, char type, double x, double y, int start, int adder);
void writeNotTr(FILE* txt, double x, double y);

#endif