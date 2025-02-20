#include "libraries.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "txt.h"
#include "torpedo.h"
#include "be.h"

#ifndef TREE_H
#define TREE_H

//ALOCAÇÃO DINÂMICA PARA A ÁRVORE TERNÁRIA
void* newTree();

//CRIAÇÃO DE NOVO NÓ DA ÁRVORE
void* newNode(double x, double y, char type, void* element);

//CHECKER PARA RAIZ DA ARVORE
bool isRoot(void* tree, void* node);

//INSERÇÃO DE PARÂMETROS NO NÓ DA ÁRVORE
void* insertTree(double x, double y, void* tree, void* node, char type, void* element);

//GETTERS PARA ÁRVORE
void* getRoot(void* tree);
int getSize(void* tree);
char getType(void* node);
void* getElement(void* node);
bool getActivity(void* node);
bool getDestruction(void* node);
bool getHit(void* node);

//SETTERS PARA ATUALIZAR STATUS DO EQUIPAMENTO NAVAL
void setInactive(void* node);
void setDestroyed(void* node);
void setHit(void* node);

//DEBUG: PRINTAR A ÁRVORE INTEIRA
void printIndentation(int n);
void printTreeNodes(void* node, int depth);
void printTree(void* tree);
 
//FUNÇÕES PARA PERCORRER A ÁRVORE TERNÁRIA E PRINTAR O SVG
void transverseTreeNodes(FILE* svg, void* node, int depth);
void transverseTree(FILE* svg, void* tree);

//FUNÇÃO PARA PERCORRER A ÁRVORE TERNÁRIA E AUXÍLIO PARA FUNÇÃO TP
int transverseTreeTp(FILE* svg, FILE* txt, void* node, int depth, double x, double y, int checks);

//FUNÇÃO PARA PERCORRER A ÁRVORE TERNÁRIA E AUXÍLIO PARA FUNÇÃO TR
int transverseTreeTr(FILE* svg, FILE* txt, void* tree, void* root, void* node, int depth, double x, double y, int id, int checks);

//ATUALIZAÇÃO DO NÍVEL DE PROTEÇÃO DE FIGURA DENTRO DA ÁRVORE
void updateProtection(FILE* txt, void* node, void* element, char type, double area, double elementArea, double v);

//FUNÇÃO PARA PERCORRER A ÁRVORE TERNÁRIA E AUXÍLIO PARA FUNÇÃO BE
void transverseTreeBe(FILE* svg, FILE* txt, void* node, int depth, double x, double y, double w, double h, double v);

//FUNÇÃO PARA PERCORRER A ÁRVORE TERNÁRIA E SOMAR OS PONTOS
double transverseTreePoints(void* node, int depth, double totalPoints);
double transverseTreeMaxPoints(void* node, int depth, double maxPoints, char* qryFunction);

//LIBERAÇÃO DO ESPAÇO ALOCADO PARA A ÁRVORE TERNÁRIA
void freeNodes(void* node);
void freeTree(void* tree);

#endif