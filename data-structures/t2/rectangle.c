#include "rectangle.h"

struct rectangle{
    int id;
    double x, y, w, h;
    char colorBorder[20], colorFill[20];
    double protectLvl;
};

void* newRect(int id, double x, double y, double w, double h, char colorBorder[20], char colorFill[20]){
    struct rectangle* new = (struct rectangle*)malloc(sizeof(struct rectangle));
    new->id = id;
    new->x = x;
    new->y = y;
    new->w = w;
    new->h = h;
    strcpy(new->colorBorder, colorBorder);
    strcpy(new->colorFill, colorFill);
    new->protectLvl = 60;
    return new;
}

void freeRect(void* element){
    struct rectangle* aux = element;
    free(aux);
}

int getRectId(void* element){
    struct rectangle* aux = element;
    return aux->id;
}

double getRectX(void* element){
    struct rectangle* aux = element;
    return aux->x;
}

double getRectY(void* element){
    struct rectangle* aux = element;
    return aux->y;
}

double getRectW(void* element){
    struct rectangle* aux = element;
    return aux->w;
}

double getRectH(void* element){
    struct rectangle* aux = element;
    return aux->h;
}

char* getRectBorder(void* element){
    struct rectangle* aux = element;
    return aux->colorBorder;
}

char* getRectFill(void* element){
    struct rectangle* aux = element;
    return aux->colorFill;
}

double getRectEnergy(void* element){
    struct rectangle* aux = element;
    return aux->protectLvl;
}

double updateRectProtect(void* element, double reduction){
    struct rectangle* aux = element;
    aux->protectLvl = aux->protectLvl - reduction;
    return aux->protectLvl;
}