#include "coordinates.h"

struct coordinates{
    double x;
    double y;
};

void* newCoordinates(){
    struct coordinates* new = (struct coordinates*)malloc(sizeof(struct coordinates));
    return new;
}

void insertCoordinates(void* coordinates, double x, double y){
    struct coordinates* aux = coordinates;
    aux->x = x;
    aux->y = y;
}

void freeCoordinates(void* coordinates){
    struct coordinates* aux = coordinates;
    free(aux);
}

double getCoordX(void* coordinates){
    struct coordinates* aux = coordinates;
    return aux->x;
}

double getCoordY(void* coordinates){
    struct coordinates* aux = coordinates;
    return aux->y;
}