#include "libraries.h"

#ifndef SEL_H
#define SEL_H

//ALOCACAO DINAMICA PARA LISTA DE FIGURAS SELECIONADAS
void* newSelList();

//ALOCACAO DINAMICA PARA NOVO ELEMENTO SELECIONADO
void* newSel(void* selectedList, int id, char elementType);

//INSERÇÃO NO FINAL DA LISTA PARA FIGURAS SELECIONADAS
void insertSel(void* selectedList, int id, char elementType);

//CHECKER PARA SABER SE A FIGURA FOI SELECIONADA OU NAO
bool checkSelected(void* selectedList, char type, int id);

//REMOCAO DE TODAS AS FIGURAS SELECIONADAS
void rmvSelAll();

//GETTERS PARA FIGURAS SELECIONADAS
int getSelSize(void* selectedList);
int getSelId(void* selectedList, int visits);
char getSelType(void* selectedList, int visits);
int getLastSel(void* selectedList);
char getLastType(void* selectedList);

//REMOCAO DE ELEMENTOS ESPECIFICOS DAS LISTA
void rmvFirstSel(void* selectedList);
void rmvLastSel(void* selectedList);

//DEBUG: PRINTAR TODAS AS FIGURAS SELECIONADAS
void printSelList();

//LIBERACAO DE ESPACO DE MEMORIA DESTINADO AS FIGURAS SELECIONADAS
void freeSelList(void* selectedList);

#endif