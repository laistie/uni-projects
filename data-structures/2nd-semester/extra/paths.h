#include "libraries.h"

#ifndef PATHS_H
#define PATHS_H

/*MÓDULO PARA TRATAMENTO DE PARÂMETROS FORNECIDOS NO ARGV*/

//ALOCAÇÃO DA STRUCT COM TODOS OS POSSÍVEIS PARÂMETROS
void* newPaths();

//DEBUG: MOSTRA TODOS OS PATHS
void printPaths(AllPaths paths);

//LIBERAÇÃO DOS ESPACOS ALOCADOS PELA STRUCT DOS PATHS E PELOS PRÓPRIOS PATHS ARMAZENADOS DENTRO DA STRUCT
void freePaths(AllPaths paths);

//ALOCAÇÃO DINÃMICA DOS PARÂMETROS
void allocGivenPathIn(AllPaths paths, int size);
void allocPathIn(AllPaths paths, int size);
void allocGivenPathOut(AllPaths paths, int size);
void allocPathOut(AllPaths paths, int size);
void allocGivenFileGeo(AllPaths paths, int size);
void allocFileGeo(AllPaths paths, int size);
void allocGivenFileQry(AllPaths paths, int size);
void allocFileQry(AllPaths paths, int size);
void allocCatGeoQry(AllPaths paths, int size);

//REALOCAÇÃO DINÂMICA DOS ARQUIVOS DE LEITURA
void reallocGeo(AllPaths paths, int size);
void reallocQry(AllPaths paths, int size);

//ATRIBUIÇÃO AOS RESPECTIVOS DADOS O NOME PASSADO PELOS PARÂMETROS
void setGivenPathIn(AllPaths paths, char* name);
void setPathIn(AllPaths paths, char* name);
void setGivenPathOut(AllPaths paths, char* name);
void setPathOut(AllPaths paths, char* name);
void setGivenFileGeo(AllPaths paths, char* name);
void setFileGeo(AllPaths paths, char* name);
void setGivenFileQry(AllPaths paths, char* name);
void setFileQry(AllPaths paths, char* name);
void setDegFactor(AllPaths paths, double number);
void setCatGeoQry(AllPaths paths, char* name);

//VERIFICA SE HÁ EXTENSÃO DOS RESPECTIVOS ARQUIVOS DE LEITURA PASSADOS COMO PARÂMETROS
bool checkFileGeo(AllPaths paths);
bool checkFileQry(AllPaths paths);

//REMOÇÃO DA EXTENSÃO DO ARQUIVO
void removeExt(char* srcArr, char* destArr, int start);

//REMOÇÃO DO PATH RELATIVO DO ARQUIVO, DEIXANDO APENAS O NOME DO ARQUIVO
void removeRelPath(char* srcArr, char* destArr);

//VERIFICA SE HÁ PATHS (ABSOLUTOS OU RELATIVOS) NOS NOMES DE ARQUIVO DOS PARÂMETROS PASSADOS
bool checkAbsPathIn(AllPaths paths);
bool checkRelPathIn(AllPaths paths);
bool checkAbsPathOut(AllPaths paths);
bool checkRelPathOut(AllPaths paths);
bool checkRelGeo(AllPaths paths);
bool checkRelQry(AllPaths paths);

//FUNÇÕES DE CÓPIA UTILIZADAS EM OUTRAS FUNÇÕES DE SET
void strcpyPathIn(AllPaths paths, char* builtPath);
void strcpyPathOut(AllPaths paths, char* builtPath);

//CONSTRUCAO DOS PATHS, DEPENDENDO DOS PARÂMETROS PASSADOS
void buildWholePathIn(AllPaths paths);
void buildPathIn(AllPaths paths, char* tempPathIn);
void buildWholePathOut(AllPaths paths);
void buildPathOut(AllPaths paths, char* tempPathOut);

//GETTERS PARA PARÂMETROS COM PATH RELATIVO
char* getRelPathIn(AllPaths paths);
char* getRelPathOut(AllPaths paths);

//GETTERS PARA RESPECTIVOS ARGUMENTOS
char* getPathIn(AllPaths paths);
char* getPathOut(AllPaths paths);
char* getGivenGeo(AllPaths paths);
char* getFileGeo(AllPaths paths);
char* getGivenQry(AllPaths paths);
char* getFileQry(AllPaths paths);
char* getCatGeoQry(AllPaths paths);
double getDegFactor(AllPaths paths);

#endif