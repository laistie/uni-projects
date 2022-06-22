#include "libraries.h"
#include "argv.h"
#include "paths.h"
#include "tree.h"
#include "be.h"

#ifndef QRY_H
#define QRY_H

//CRIAÇÃO DE FILE POINTER PARA ARQUIVO .TXT DE RELATÓRIO
FILE* newReport(void* paths);

//ENCERRAMENTO DO ARQUIVO .TXT
void endReport(FILE* txt);

//FUNÇÃO PARA DESENHAR OS EIXOS COORDENADOS
void drawAxis(void* paths);

//FUNÇÃO PARA DESENHAR O ARQUIVO .GEO
void drawGeo(FILE* svg, void* tpList, void* trList, void* tree);

//FUNÇÃO PARA ATUALIZAR O ARQUIVO .SVG APÓS FUNÇÃO TP
FILE* updateSvg(void* tpList, void* trList, void* paths, FILE* svg, void* tree);

//TORPEDO: REMOVER TODAS AS FORMAS PARA AS QUAIS O PONTO É INTERNO
FILE* tp(void* tpList, void* trList, void* paths, FILE* svg, FILE* txt, void* tree, double x, double y);

//TORPEDO REPLICANTE: TRANSLADA A(S) FIGURA(S) ATINGIDA(S) EM DX E DY
FILE* tr(void* tpList, void* trList, void* paths, FILE* svg, FILE* txt, void* tree, double x, double y, double dx, double dy, int id);

//BOMBA DE IRRADIAÇÃO: FIGURAS DENTRO DA ÁREA TERÃO SEU NÍVEL DE ENERGIA DIMINUÍDO
FILE* be(void* tpList, void* trList, void* areaList, void* paths, FILE* svg, FILE* txt, void* tree, double x, double y, double w, double h, double v);

//FUNÇÕES DE SOMA DE PONTOS
double sumPoints(void* tree);
double sumMaxPoints(void* tree, char* qryFunction);

//FINALIZAÇÃO DO ARQUIVO .SVG
void endSvg(FILE* pfileSvg);

//LEITURA DO ARQUIVO DE CONSULTAS .QRY
void readQry(FILE* txt, void* tree, void* paths, void* checkedPaths);

#endif