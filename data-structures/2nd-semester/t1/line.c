#include "line.h"

struct line{
    int id;
    double x1, y1, x2, y2;
    char color[20];
};

void* newLine(int id, double x1, double y1, double x2, double y2, char color[20]){
    struct line* new = (struct line*)malloc(sizeof(struct line));
    new->id = id;
    new->x1 = x1;
    new->y1 = y1;
    new->x2 = x2;
    new->y2 = y2;
    strcpy(new->color, color);
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

void setLineX1(void* element, double x1){
    struct line* aux = element;
    aux->x1 = x1;
}

void setLineY1(void* element, double y1){
    struct line* aux = element;
    aux->y1 = y1;
}

void setLineX2(void* element, double x2){
    struct line* aux = element;
    aux->x2 = x2;
}

void setLineY2(void* element, double y2){
    struct line* aux = element;
    aux->y2 = y2;
}

void setLineColor(void* element, char color[20]){
    struct line* aux = element;
    strcpy(aux->color, color);
}