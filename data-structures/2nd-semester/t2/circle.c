#include "circle.h"

struct circle{ //HOVERCRAFT DE ASSALTO
    int id;
    double x, y, r;
    char colorBorder[20], colorFill[20];
    double protectLvl;
};

void* newCircle(int id, double x, double y, double r, char colorBorder[20], char colorFill[20]){
    struct circle* new = (struct circle*)malloc(sizeof(struct circle));
    new->id = id;
    new->x = x;
    new->y = y;
    new->r = r;
    strcpy(new->colorBorder, colorBorder);
    strcpy(new->colorFill, colorFill);
    new->protectLvl = 60;
    return new; 
}

void freeCircle(void* element){
    struct circle* aux = element;
    free(aux);
}

int getCircleId(void* element){
    struct circle* aux = element;
    return aux->id;
}

double getCircleX(void* element){
    struct circle* aux = element;
    return aux->x;
}

double getCircleY(void* element){
    struct circle* aux = element;
    return aux->y;
}

double getCircleR(void* element){
    struct circle* aux = element;
    return aux->r;
}

char* getCircleBorder(void* element){
    struct circle* aux = element;
    return aux->colorBorder;
}

char* getCircleFill(void* element){
    struct circle* aux = element;
    return aux->colorFill;
}

double getCircleEnergy(void* element){
    struct circle* aux = element;
    return aux->protectLvl;
}

double updateCircleProtect(void* element, double reduction){
    struct circle* aux = element;
    aux->protectLvl = aux->protectLvl - reduction;
    return aux->protectLvl;
}