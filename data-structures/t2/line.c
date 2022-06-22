#include "line.h"

struct line{ //SUBMARINO
    int id;
    double x1, y1, x2, y2;
    char color[20];
    double protectLvl;
};

void* newLine(int id, double x1, double y1, double x2, double y2, char color[20]){
    struct line* new = (struct line*)malloc(sizeof(struct line));
    new->id = id;
    new->x1 = x1;
    new->y1 = y1;
    new->x2 = x2;
    new->y2 = y2;
    strcpy(new->color, color);
    new->protectLvl = 50;
    return new;
}

void freeLine(void* element){
    struct line* aux = element;
    free(aux);
}

int getLineId(void* element){
    struct line* aux = element;
    return aux->id;
}

double getLineX1(void* element){
    struct line* aux = element;
    return aux->x1;
}

double getLineY1(void* element){
    struct line* aux = element;
    return aux->y1;
}

double getLineX2(void* element){
    struct line* aux = element;
    return aux->x2;
}

double getLineY2(void* element){
    struct line* aux = element;
    return aux->y2;
}

char* getLineBorder(void* element){
    struct line* aux = element;
    return aux->color;
}

double getLineEnergy(void* element){
    struct line* aux = element;
    return aux->protectLvl;
}

double updateLineProtect(void* element, double reduction){
    struct line* aux = element;
    aux->protectLvl = aux->protectLvl - reduction;
    return aux->protectLvl;
}