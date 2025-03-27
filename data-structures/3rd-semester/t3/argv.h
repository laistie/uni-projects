#include "paths.h"
#include "libraries.h"

#ifndef ARGV_H
#define ARGV_H

/*MÓDULO PARA TRATAMENTO DE CHECKERS DOS PARÂMETROS FORNECIDOS PELO ARGV*/

//ALOCA A STRUCT COM OS VALORES BOOLEANOS DOS PARÂMETROS
void* newCheckedPaths();

//INICIALIZAÇÃO OS VALORES BOOLEANOS DOS PARÂMETROS
void setCheckedPaths(CheckedPaths checkedPaths);

//LIBERAÇÃO DO ESPAÇO ALOCADO PARA A STRUCT COM VALORES BOOLEANOS DOS PARÂMETROS
void freeCheckedPaths(CheckedPaths checkedPaths);

//ATRIBUIÇÃO DE VALOR TRUE AO VALOR BOOLEANO REFERENTE AO PARÂMETRO PASSADO
void setGivenPathInTrue(CheckedPaths checkedPaths);
void setPathInTrue(CheckedPaths checkedPaths);
void setGivenPathOutTrue(CheckedPaths checkedPaths);
void setPathOutTrue(CheckedPaths checkedPaths);
void setFileGeoTrue(CheckedPaths checkedPaths);
void setFileQryTrue(CheckedPaths checkedPaths);
void setEpsilonTrue(CheckedPaths checkedPaths);

//VERIFICA OS VALORES REFERENTES À PASSAGEM DE PARÂMETROS
bool checkCheckedPaths(CheckedPaths checkedPaths);
bool getCheckedGivenPathIn(CheckedPaths checkedPaths);
bool getCheckedPathIn(CheckedPaths checkedPaths);
bool getCheckedGeo(CheckedPaths checkedPaths);
bool getCheckedQry(CheckedPaths checkedPaths);
bool getCheckedEpsilon(CheckedPaths checkedPaths);

//FUNÇÃO DE LEITURA DE PARÂMETROS E ARMAZENAMENTO DOS RESPECTIVOS NOMES DOS PATHS E ARQUIVOS
void setArgv(int argc, char** argv, void* paths, CheckedPaths checkedPaths);

#endif