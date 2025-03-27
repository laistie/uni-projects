#include "libraries.h"
#include "SRbTree.h"
#include "info.h"
#include "circle.h"

#ifndef MC_H
#define MC_H

void* newMc(SRbTree tree, double dx, double dy, double x, double y, double w, double h, FILE* pTxt);

void updateMc(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux);

#endif