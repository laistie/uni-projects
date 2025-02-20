#include "libraries.h"
#include "yxxtree.h"
#include "paths.h"
#include "list.h"
#include "queue.h"
#include "inp.h"
#include "svg.h"

#ifndef QRY_H
#define QRY_H

/*MÓDULO DESTINADO*/

//CRIAÇÃO DE FILE POINTER PARA ARQUIVO .TXT DE RELATÓRIO
FILE* newReport(AllPaths paths);

//ENCERRAMENTO DO ARQUIVO .TXT
void endReport(FILE* txt);

//FINALIZAÇÃO DO ARQUIVO .SVG
void endSvg(FILE* pfileSvg);

//LEITURA DO ARQUIVO DE CONSULTAS .QRY
void readQry(FILE* txt, YxxTree tree, AllPaths paths, CheckedPaths checkedPaths);

#endif