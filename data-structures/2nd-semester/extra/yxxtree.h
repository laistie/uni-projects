#include "libraries.h"
#include "list.h"

#ifndef YXXTREE_H
#define YXXTREE_H

/*MÓDULO DESTINADO À MANIPULAÇÃO DA ÁRVORE YXX
    YXXTREE É UMA ÁRVORE TERNÁRIA QUE CONTÉM 3 RAMIFICAÇÕES (se, sm, sd), COORDENADAS (x,y), INFO SOBRE A FORMA ARMAZENADA E UM CHAR AUXILIAR PARA FACILITAR A IDENTIFICAÇÃO DE CADA FORMA GEOMÉTRICA*/

typedef void* YxxTree;
typedef void* Node;
typedef void* Info;

//FUNÇÃO RETORNA VERDADEIRO SE A INFORMAÇÃO i ESTÁ DENTRO DA REGIÃO RETANGULAR DELIMITADA PELOS PONTOS (x1, y1) e (x2, y2)
typedef bool (*FdentroDe)(Info i, double x1, double y1 , double x2, double y2);

//FUNÇÃO RETORNA VERDADEIRO SE O PONTO (x, y) DEVE SER CONSIDERADO INTERNO DA INFORMAÇÃO i
typedef bool (*FatingidoPor)(Info i, double x, double y);

//PROCESSA A INFORMAÇÃO i, ASSOCIADA A UM NÓ DA ÁRVORE, CUJA A ÂNCORA É O PONTO (x, y). O PARÂMETRO aux APONTA PARA UM CONJUNTO DE DADOS QUE SÃO COMPARTILHADOS ENTRE AS SUCESSIVAS INVOCAÇÕES DESSA FUNÇÃO
typedef void (*FvisitaNo)(Info i, double x, double y, void* aux);

//CRIAÇÃO DE UMA ÁRVORE YXX COM FATOR DE DEGRADAÇÃO FD
YxxTree newYxxTree(double fd);

//INSERÇÃO DA INFORMAÇÃO info ASSOCIADA À ÂNCORA (x,y) NA ÁRVORE tree, RETORNA IDENTIFICADOR PARA O NÓ INSERIDO
Node insertYxxT(YxxTree tree, Node node, double x, double y, Info info);

//RETORNA O NÓ CUJA ÂNCORA SEJA O PONTO (x,y), ACEITA-SE UMA DISCREPÂNCIA ENTRE A ÂNCORA E O PONTO
Node getNodeYxxT(YxxTree tree, double x, double y, double epsilon);

//MARCA COMO REMOVIDO O NÓ node; CASO, APÓS A REMOÇÃO, O FATOR DE DEGRADAÇÃO SUPERAR O LIMIAR DEFINIDO NA CRIAÇÃO DA ÁRVORE, ELA É RECRIADA SEM OS NÓS REMOVIDOS
void removeNoYxxT(YxxTree tree, Node node);

//RETORNA A RAIZ DA ÁRVORE
Node getRoot(YxxTree tree);

//RETORNA A INFORMAÇÃO ASSOCIADA AO NÓ node
Info getInfoYxxT(YxxTree tree, Node node);

//RETORNA UMA LISTA DOS NÓS DA ÁRVORE CUJAS ÂNCORAS ESTÃO DENTRO DA REGIÃO DELIMITADA PELOS PONTOS (x1, y1) e (x2, y2)
List getNodesDentroRegiaoYxxT(YxxTree tree, double x1, double y1, double x2, double y2);

//PERCORRE A ÁRVORE EM PROFUNDIDADE. INVOCA f EM CADA NÓ VISITADO E O APONTADOR aux É PARÂMETRO DE INVOCAÇÃO PARA f
void visitaProfundidadeYxxT(YxxTree tree, FvisitaNo f, void* aux);

//PERCORRE A ÁRVORE EM LARGURA. INVOCA f EM CADA NÓ VISITADO E O APONTADOR aux É PARÂMETRO DE INVOCAÇÃO PARA f
void visitaLarguraYxxT(YxxTree tree, FvisitaNo f, void* aux);

//DEBUG: PRINTA A ÁRVORE INTEIRA
void printTree(YxxTree tree);

//LIBERAÇÃO DE ESPAÇO ALOCADO PARA A ÁRVORE YXX
void freeTree(YxxTree tree);

#endif