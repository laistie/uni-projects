#include "txt.h"

struct txt{ //RHIB
    int id;
    double x, y;
    char colorBorder[20], colorFill[20], a, txt[100];
    double protectLvl;
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
    new->protectLvl = 5;
    return new;
}

void freeTxt(void* element){
    struct txt* aux = element;
    free(aux);
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

double getTxtEnergy(void* element){
    struct txt* aux = element;
    return aux->protectLvl;
}

double updateTxtProtect(void* element, double reduction){
    struct txt* aux = element;
    aux->protectLvl = aux->protectLvl - reduction;
    return aux->protectLvl;
}