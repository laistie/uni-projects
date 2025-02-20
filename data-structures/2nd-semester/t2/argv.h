#include "libraries.h"
#include "paths.h"

#ifndef ARGV_H
#define ARGV_H

//ALOCA A STRUCT COM OS VALORES BOOLEANOS DOS PARÂMETROS
void* newCheckedPaths();

//INICIALIZAÇÃO OS VALORES BOOLEANOS DOS PARÂMETROS
void setCheckedPaths(void* checkedPaths);

//LIBERAÇÃO DO ESPAÇO ALOCADO PARA A STRUCT COM VALORES BOOLEANOS DOS PARÂMETROS
void freeCheckedPaths(void* checkedPaths);

//ATRIBUIÇÃO DE VALOR TRUE AO VALOR BOOLEANO REFERENTE AO PARÂMETRO PASSADO
void setGivenPathInTrue(void* checkedPaths);
void setPathInTrue(void* checkedPaths);
void setGivenPathOutTrue(void* checkedPaths);
void setPathOutTrue(void* checkedPaths);
void setFileGeoTrue(void* checkedPaths);
void setFileQryTrue(void* checkedPaths);

//VERIFICA OS VALORES REFERENTES À PASSAGEM DE PARÂMETROS
bool checkCheckedPaths(void* checkedPaths);
bool getCheckedGivenPathIn(void* checkedPaths);
bool getCheckedPathIn(void* checkedPaths);
bool getCheckedGeo(void* checkedPaths);
bool getCheckedQry(void* checkedPaths);

//FUNÇÃO DE LEITURA DE PARÂMETROS E ARMAZENAMENTO DOS RESPECTIVOS NOMES DOS PATHS E ARQUIVOS
void setArgv(int argc, char** argv, void* paths, void* checkedPaths);

#endif