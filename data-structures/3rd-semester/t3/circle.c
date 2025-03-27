#include "circle.h"

struct circle{ //PEIXE
    int id;
    double x, y, r;
    char colorBorder[20], colorFill[20];
};

void* newCircle(int id, double x, double y, double r, char colorBorder[20], char colorFill[20]){
    struct circle* new = (struct circle*)malloc(sizeof(struct circle));
    new->id = id;
    new->x = x;
    new->y = y;
    new->r = r;
    strcpy(new->colorBorder, colorBorder);
    strcpy(new->colorFill, colorFill);
    return new; 
}

void setCircleX(void* element, double x){
    struct circle* aux = element;
    aux->x = x;
}

void setCircleY(void* element, double y){
    struct circle* aux = element;
    aux->y = y;
}

void setCircleBorder(void* element, char colorBorder[20]){
    struct circle* aux = element;
    strcpy(aux->colorBorder, colorBorder);
}

void setCircleFill(void* element, char colorFill[20]){
    struct circle* aux = element;
    strcpy(aux->colorFill, colorFill);
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

double getCircleMBBX1(double x, double r){
    double mbbX1 = x - r;
    return mbbX1;
}

double getCircleMBBY1(double y, double r){
    double mbbY1 = y - r;
    return mbbY1;
}

double getCircleMBBX2(double x, double r){
    double mbbX2 = x + r;
    return mbbX2;
}

double getCircleMBBY2(double y, double r){
    double mbbY2 = y + r;
    return mbbY2;
}