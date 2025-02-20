#include "libraries.h"

#ifndef INFO_H
#define INFO_H

typedef void* InfoStruct;
typedef void* InfoElement;

InfoStruct newInfo(char type, void* info);

char getInfoType(InfoStruct node);
InfoElement getInfoFromInfo(InfoStruct node);

void freeInfo(InfoStruct node);

#endif