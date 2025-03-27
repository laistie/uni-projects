#include "libraries.h"
#include "List.h"
#include "rectangle.h"
#include "info.h"
#include "SRbTree.h"

#ifndef D_H
#define D_H

void* newD(int i, char lado[3], double d, SRbTree tree, FILE* pTxt);

double getPointImpactX(void* aux);
double getPointImpactY(void* aux);

void setDList(void* d, Lista list);

void updateD(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux);

#endif