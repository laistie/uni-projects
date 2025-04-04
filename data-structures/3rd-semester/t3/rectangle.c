#include "rectangle.h"

struct rectangle{ //NAUS
    int id;
    double x, y, w, h;
    char colorBorder[20], colorFill[20];
    double energy;
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
    return new;
}

void setRectX(void* element, double x){
    struct rectangle* aux = element;
    aux->x = x;
}

void setRectY(void* element, double y){
    struct rectangle* aux = element;
    aux->y = y;
}

void setRectBorder(void* element, char colorBorder[20]){
    struct rectangle* aux = element;
    strcpy(aux->colorBorder, colorBorder);
}

void setRectFill(void* element, char colorFill[20]){
    struct rectangle* aux = element;
    strcpy(aux->colorFill, colorFill);
}

void setRectEnergy(void* element, double e){
    struct rectangle* aux = element;
    aux->energy = e;
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
    return aux->energy;
}

bool checkRectHit(double x, double y, double w, double h, double hitX, double hitY){
    if (hitX >= x && hitX <= x + w && hitY >= y && hitY <= y + h){
        return true;
    }
    return false;
}