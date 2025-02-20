#include "libraries.h"
#include "queueCoord.h"

#ifndef QUEUE_H
#define QUEUE_H

typedef void** CoordinatesArr;
typedef void* Queue;

Queue newQueue(int size);

bool isFull(Queue queue);
bool isEmpty(Queue queue);

int getRear(Queue queue);
Coordinates getFirstCoordinates(Queue queue);

void enqueue(Queue queue, double x, double y);

void dequeue(Queue queue, Coordinates coordinates);

void pol(FILE* pSvg, Queue queue, int i, double d, double e, char coLorBorder[20], char colorFill[20]);

bool freeAllCoordinates(Queue queue);
void freeQueue(Queue queue);

#endif