#include "List.h"

struct list{
    double x, y, w, h;
    struct list* next;
};

struct list* headD = NULL;

struct list* headLr = NULL; 

Lista newList(){
    struct list* new = (struct list*)malloc(sizeof(struct list));
    return new;
}

void* newDListCoord(Lista list, double x, double y){
    struct list* new = (struct list*)malloc(sizeof(struct list));
    new->x = x;
    new->y = y;
    new->next = NULL;
    return new;
}

void* newLrListCoord(Lista list, double x, double y, double w, double h){
    struct list* new = (struct list*)malloc(sizeof(struct list));
    new->x = x;
    new->y = y;
    new->w = w;
    new->h = h;
    new->next = NULL;
    return new;
}

void insertList(Lista list, char type, double x, double y, double w, double h){
    if(type == 'd'){
        struct list* new = newDListCoord(list, x, y);
        if(!headD){
            headD = new;
            return;
        }
        new->next = headD;
        headD = new;
    }
    else if(type == 'l'){
        struct list* new = newLrListCoord(list, x, y, w, h);
        if(!headLr){
            headLr = new;
            return;
        }
        new->next = headLr;
        headLr = new;
    }
}

double getListNodeX(char type, int position){
    struct list* aux;
    if(type == 'd'){
        aux = headD;
    }
    else if(type == 'l'){
        aux = headLr;
    }
    for(int i = 0; i < position; i++){
        aux = aux->next;
    }
    return aux->x;
}

double getListNodeY(char type, int position){
    struct list* aux;
    if(type == 'd'){
        aux = headD;
    }
    else if(type == 'l'){
        aux = headLr;
    }
    for(int i = 0; i < position; i++){
        aux = aux->next;
    }
    return aux->y;
}

double getListNodeW(int position){
    struct list* aux = headLr;
    for(int i = 0; i < position; i++){
        aux = aux->next;
    }
    return aux->w;
}

double getListNodeH(int position){
    struct list* aux = headLr;
    for(int i = 0; i < position; i++){
        aux = aux->next;
    }
    return aux->h;
}

void markD(FILE* pSvg, Lista list){
    struct list* aux = headD;
    if(!aux){
        return;
    }
    int i = 0;
    double x, y;
    while(aux){
        x = getListNodeX('d', i);
        y = getListNodeY('d', i);
        fprintf(pSvg,"\n\t<text x=\"%lf\" y=\"%lf\" style=\"font:7.5px sans-serif; stroke:red; stroke-width:0.5; fill: red; text-anchor:middle;\"> * </text>", x, y);
        aux = aux->next;
        i++;
    }
}

void markLr(FILE* pSvg, Lista list){
    struct list* aux = headLr;
    if(!aux){
        return;
    }
    int i = 0;
    double x, y, w, h;
    while(aux){
        x = getListNodeX('l', i);
        y = getListNodeY('l', i);
        w = getListNodeW(i);
        h = getListNodeH(i);
        fprintf(pSvg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill-opacity: 0; stroke:red; stroke-width:1; stroke-dasharray: 1 1\"/>", x, y, w, h);
        aux = aux->next;
        i++;
    }
}

void freeList(char type, Lista list){
    if(type == 'd'){
        if(!headD){
            free(list);
            return;
        }
        void* nodeAux, *currentHead, *nextHead;
        do{
            currentHead = headD;
            nodeAux = currentHead;
            nextHead = headD->next;
            headD = headD->next;
            free(nodeAux);
        } while(nextHead);
    }
    else if(type == 'l'){
        if(!headLr){
            free(list);
            return;
        }
        void* nodeAux, *currentHead, *nextHead;
        do{
            currentHead = headLr;
            nodeAux = currentHead;
            nextHead = headLr->next;
            headLr = headLr->next;
            free(nodeAux);
        } while(nextHead);
    }
    free(list);
}