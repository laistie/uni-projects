#include "libraries.h"
#include "yxxtree.h"
#include "info.h"
#include "queue.h"

#ifndef INP_H
#define INP_H

void* newInp(int id, Queue queue, FILE* pTxt);
void fInp(Info i, double x, double y, void* aux);

#endif