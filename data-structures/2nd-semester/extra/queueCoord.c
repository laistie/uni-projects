#include "queueCoord.h"

struct coordinates{
    double x, y;
};

Coordinates newCoordinates(){
    struct coordinates* new = (struct coordinates*)malloc(sizeof(struct coordinates));
    return new;
}

void insertCoordinates(Coordinates coordinates, double x, double y){
    struct coordinates* aux = coordinates;
    aux->x = x;
    aux->y = y;
}

double getXCoord(Coordinates coordinates){
    struct coordinates* aux = coordinates;
    return aux->x;
}

double getYCoord(Coordinates coordinates){
    struct coordinates* aux = coordinates;
    return aux->y;
}

void freeCoordinates(Coordinates coordinates){
    struct coordinates* aux = coordinates;
    free(aux);
}