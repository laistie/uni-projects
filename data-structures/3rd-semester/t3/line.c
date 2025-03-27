#include "line.h"

struct line{ //CAMARÃO
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

void setLineX1(void* element, double x){
    struct line* aux = element;
    aux->x1 = x;
}

void setLineY1(void* element, double y){
    struct line* aux = element;
    aux->y1 = y;
}

void setLineX2(void* element, double x){
    struct line* aux = element;
    aux->x2 = x;
}

void setLineY2(void* element, double y){
    struct line* aux = element;
    aux->y2 = y;
}

void setLineColor(void* element, char color[20]){
    struct line* aux = element;
    strcpy(aux->color, color);
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