#include "txt.h"

struct txt{ //RHIB
    int id;
    double x, y;
    char colorBorder[20], colorFill[20], a, txt[100];
};

void* newTxt(int id, double x, double y, char colorBorder[20], char colorFill[20], char a, char txt[100]){
    struct txt* new = (struct txt*)malloc(sizeof(struct txt));
    new->id = id;
    new->x = x;
    new->y = y;
    strcpy(new->colorBorder, colorBorder);
    strcpy(new->colorFill, colorFill);
    new->a = a;
    strcpy(new->txt, txt);
    return new;
}

void setTxtX(void* element, double x){
    struct txt* aux = element;
    aux->x = x;
}

void setTxtY(void* element, double y){
    struct txt* aux = element;
    aux->y = y;
}

void setTxtBorder(void* element, char colorBorder[20]){
    struct txt* aux = element;
    strcpy(aux->colorBorder, colorBorder);
}

void setTxtFill(void* element, char colorFill[20]){
    struct txt* aux = element;
    strcpy(aux->colorFill, colorFill);
}

int getTxtId(void* element){
    struct txt* aux = element;
    return aux->id;
}

double getTxtX(void* element){
    struct txt* aux = element;
    return aux->x;
}

double getTxtY(void* element){
    struct txt* aux = element;
    return aux->y;
}

char* getTxtBorder(void* element){
    struct txt* aux = element;
    return aux->colorBorder;
}

char* getTxtFill(void* element){
    struct txt* aux = element;
    return aux->colorFill;
}

char getA(void* element){
    struct txt* aux = element;
    return aux->a;
}

char* getTxt(void* element){
    struct txt* aux = element;
    return aux->txt;
}

bool checkTxt(void* element, double x1, double y1, double x2, double y2){
    double x = getTxtX(element);
    double y = getTxtY(element);
    if(x >= x1&& x <= x2 && y >= y1 && y <= y2){
       return true;
    }
    return false;
}