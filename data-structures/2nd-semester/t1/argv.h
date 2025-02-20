#include "libraries.h"
#include "paths.h"

#ifndef ARGV_H
#define ARGV_H

//ALOCA A STRUCT COM OS VALORES BOOLEANOS DOS PARAMETROS
void* newCheckedPaths();

//INICIALIZACAO OS VALORES BOOLEANOS DOS PARAMETROS
void setCheckedPaths(void* checkedPaths);

//LIBERACAO DO ESPACO ALOCADO PARA A STRUCT COM VALORES BOOLEANOS DOS PARAMETROS
void freeCheckedPaths(void* checkedPaths);

//ATRIBUICAO DE VALOR TRUE AO RESPECTIVO VALOR BOOLEANO REFERENTE AO PARAMETRO PASSADO
void setGivenPathInTrue(void* checkedPaths);
void setPathInTrue(void* checkedPaths);
void setGivenPathOutTrue(void* checkedPaths);
void setPathOutTrue(void* checkedPaths);
void setFileGeoTrue(void* checkedPaths);
void setFileQryTrue(void* checkedPaths);

//VERIFICA OS VALORES REFERENTES A PASSAGEM DE PARAMETROS
bool checkCheckedPaths(void* checkedPaths);
bool getCheckedGivenPathIn(void* checkedPaths);
bool getCheckedPathIn(void* checkedPaths);
bool getCheckedGeo(void* checkedPaths);
bool getCheckedQry(void* checkedPaths);

//FUNCAO DE LEITURA DE PARAMETROS E ARMAZENAMENTO DOS RESPECTIVOS NOMES DOS PATHS E ARQUIVOS
void setArgv(int argc, char** argv, void* paths, void* checkedPaths);

#endif