#include "libraries.h"
#include "List.h"
#include "info.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "txt.h"
#include "SRbTree.h"

#ifndef LR_H
#define LR_H

void* newLr(int i, char lado[3], double d, double w, double h, SRbTree tree, FILE* pTxt);

void setLrList(void* lr, Lista list);
void setPoints(void* lr, double points);

double getPoints(void* lr);

void updateLr(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux);

#endif