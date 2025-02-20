#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

#ifndef LIBRARIES_H
#define LIBRARIES_H

#define MAX_QUEUE 500

/*MÓDULO COM TODAS AS BIBLIOTECAS UTILIZADAS NO PROJETO E TYPEDEFS*/

//STRUCT COM VALORES BOOLEANOS PARA AUXILIAR NA VERIFICAÇÃO DOS PARÂMETROS
typedef void* CheckedPaths;

//STRUCT COM TODOS OS PARÂMETROS FORNECIDOS PELO ARGV, ALGUNS SÃO SUJEITOS A MODIFICAÇÕES ANTES DE SEREM ARMAZENADOS PARA FACILITAR SUA MANIPULAÇÃO AO LONGO DO PROJETO
typedef void* AllPaths;

#endif