#include "libraries.h"

#ifndef PATHS_H
#define PATHS_H

//ALOCAÇÃO DA STRUCT COM TODOS OS POSSÍVEIS PARÂMETROS
void* newPaths();

//DEBUG: MOSTRA TODOS OS PATHS
void printPaths(void* paths);

//LIBERAÇÃO DOS ESPACOS ALOCADOS PELA STRUCT DOS PATHS E PELOS PRÓPRIOS PATHS ARMAZENADOS DENTRO DA STRUCT
void freePaths(void* paths);

//ALOCAÇÃO DINÃMICA DOS PARÂMETROS
void allocGivenPathIn(void* paths, int size);
void allocPathIn(void* paths, int size);
void allocGivenPathOut(void* paths, int size);
void allocPathOut(void* paths, int size);
void allocGivenFileGeo(void* paths, int size);
void allocFileGeo(void* paths, int size);
void allocGivenFileQry(void* paths, int size);
void allocFileQry(void* paths, int size);
void allocCatGeoQry(void* paths, int size);

//REALOCAÇÃO DINÂMICA DOS ARQUIVOS DE LEITURA
void reallocGeo(void* paths, int size);
void reallocQry(void* paths, int size);

//ATRIBUIÇÃO AOS RESPECTIVOS DADOS O NOME PASSADO PELOS PARÂMETROS
void setGivenPathIn(void* paths, char* name);
void setPathIn(void* paths, char* name);
void setGivenPathOut(void* paths, char* name);
void setPathOut(void* paths, char* name);
void setGivenFileGeo(void* paths, char* name);
void resetGeo(void* paths, char* name);
void setFileGeo(void* paths, char* name);
void setGivenFileQry(void* paths, char* name);
void setFileQry(void* paths, char* name);
void setCatGeoQry(void* paths, char* name);

//VERIFICA SE HÁ EXTENSAO DOS RESPECTIVOS ARQUIVOS DE LEITURA PASSADOS COMO PARÂMETROS
bool checkFileGeo(void* paths);
bool checkFileQry(void* paths);

//VERIFICA SE HÁ PATHS (ABSOLUTOS OU RELATIVOS) NOS NOMES DE ARQUIVO DOS PARÂMETROS PASSADOS
bool checkAbsPathIn(void* paths);
bool checkRelPathIn(void* paths);
bool checkAbsPathOut(void* paths);
bool checkRelPathOut(void* paths);
bool checkRelGeo(void* paths);
bool checkRelQry(void* paths);

//FUNCOES DE COPIA UTILIZADAS EM OUTRAS FUNCOES DE SET
void strcpyPathIn(void* paths, char* builtPath);
void strcpyPathOut(void* paths, char* builtPath);
void strcpyGeo(void* paths);
void strcpyQry(void* paths);

//CONSTRUCAO DOS PATHS, DEPENDENDO DOS PARAMETROS PASSADOS
void buildWholePathIn(void* paths);
void buildPathIn(void* paths, char* tempPathIn);
void buildWholePathOut(void* paths);
void buildPathOut(void* paths, char* tempPathOut);

//GETTERS PARA PARAMETROS COM PATH RELATIVO
char* getRelPathIn(void* paths);
char* getRelPathOut(void* paths);

//GETTERS PARA RESPECTIVOS ARGUMENTOS
char* getPathIn(void* paths);
char* getPathOut(void* paths);
char* getGivenGeo(void* paths);
char* getFileGeo(void* paths);
char* getGivenQry(void* paths);
char* getFileQry(void* paths);
char* getCatGeoQry(void* paths);

#endif