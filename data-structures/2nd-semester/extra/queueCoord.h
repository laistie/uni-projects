#include "libraries.h"

#ifndef QUEUECOORD_H
#define QUEUECOORD_H

typedef void* Coordinates;

Coordinates newCoordinates();

void insertCoordinates(Coordinates coordinates, double x, double y);

double getXCoord(Coordinates coordinates);
double getYCoord(Coordinates coordinates);

void freeCoordinates(Coordinates coordinates);

#endif