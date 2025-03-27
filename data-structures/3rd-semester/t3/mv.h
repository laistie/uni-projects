#include "libraries.h"
#include "info.h"
#include "SRbTree.h"
#include "circle.h"
#include "line.h"
#include "rectangle.h"
#include "txt.h"

#ifndef MV_H
#define MV_H

void* newMv(SRbTree tree, int id, double dx, double dy, FILE* pTxt);

void updateMv(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux);

#endif