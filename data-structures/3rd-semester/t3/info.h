#ifndef _INFO_H
#define _INFO_H

typedef void* InfoStruct;
typedef void* InfoElement;

/*MÓDULO PARA TRATAMENTO DE INFOS QUE SERÃO INSERIDAS NA SRB TREE*/

InfoStruct newInfo(char type, InfoElement info);

char getInfoType(InfoStruct node);
InfoElement getInfoElement(InfoStruct node);
InfoElement getInfoFromInfo(InfoStruct node);

void freeInfo(InfoStruct node);

#endif