#include "libraries.h"
#include "info.h"
#include "SRbTree.h"
#include "rectangle.h"

#ifndef ENERGY_H
#define ENERGY_H

void* newEnergy(double e, FILE* pTxt);

void setEnergy(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux);

#endif