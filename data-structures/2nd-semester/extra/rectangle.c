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

bool checkRect(void* element, double x1, double y1, double x2, double y2){
    double x = getRectX(element);
    double y = getRectY(element);
    double w = getRectW(element);
    double h = getRectH(element);
    double centerX = x + w / 2;
    double centerY = y + h / 2;
    if(centerX + w / 2 <= x2 && centerY - h / 2 >= y1 && centerX - w / 2 >= x1 && centerY + h / 2 <= y2){
        return true;
    }
    return false;
}