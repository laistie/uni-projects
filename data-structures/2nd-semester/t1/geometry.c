#include "geometry.h"

struct geometryList{
    struct geometryList* prev;
    char elementType;
    void* element;
    struct geometryList* next;
};

struct geometryList* head = NULL;

void* newGeoList(){
    struct geometryList* new = (struct geometryList*)malloc(sizeof(struct geometryList));
    return new;
}

void* newGeo(void* geometryList, char elementType, void* element){
    struct geometryList* new = (struct geometryList*)malloc(sizeof(struct geometryList));
    new->elementType = elementType;
    new->element = element;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

void insertGeo(void* geometryList, char elementType, void* element){
    struct geometryList* new = newGeo(geometryList, elementType, element);
    if(head == NULL){
        head = new;
        return;
    }
    new->next = head;
    head->prev = new;
    head = new;
}

char getElementType(){
    struct geometryList* aux = head;
    return aux->elementType;
}

void freeGeoList(void* geometryList){
    if(head == NULL){
        free(geometryList);
        return;
    }
    void* nodeAux, *elementAux, *currentHead, *nextHead;
    char elementType;
    do{
        currentHead = head;
        nodeAux = currentHead; 
        elementAux = head->element;
        nextHead = head->next;
        elementType = getElementType(geometryList);
        if(elementType == 'c'){
            freeCircle(elementAux);
        }
        else if(elementType == 'r'){
            freeRect(elementAux);
        }
        else if(elementType == 'l'){
            freeRect(elementAux);
        }
        else if(elementType == 't'){
            freeTxt(elementAux);
        }
        head = head->next;
        free(nodeAux);
    } while(nextHead != NULL);
    free(geometryList);
}

void printGeoList(){
    struct geometryList* aux = head;
    int i = 0;
    if(aux == NULL){
        printf("\nErro: lista dinamica duplamente encadeada vazia\n");
    }
    else{
        printf("\n---geometry list---\n");
        while(aux != NULL){
            printf(" %c ->", aux->elementType);
            aux = aux->next;
            i++;
        }
    }
    printf("\ntotal: %d", i);
    printf("\n\n");
}

int getGeoSize(){
    struct geometryList* aux = head;
    int i = 0;
    while(aux->next != NULL){
        aux = aux->next;
        i++;
    }
    return i;
}

char getCurrentType(int visits){
    struct geometryList* aux = head;
    for(int i = 0; i < visits; i++){
        aux = aux->next;
    }
    return aux->elementType;
}

void* getCurrentElement(int visits){
    struct geometryList* aux = head;
    for(int i = 0; i < visits; i++){
        aux = aux->next;
    }
    return aux->element;
}

void* getNextElement(int visits){
    struct geometryList* aux = head;
    for(int i = 0; i < visits; i++){
        aux = aux->next;
    }
    if(aux == NULL){
        return NULL;
    }
    return aux->next->element;
}

void* getPrevElement(int visits){
    struct geometryList* aux = head;
    for(int i = 0; i < visits; i++){
        aux = aux->next;
    }
    if(aux->prev){
        return aux->prev->element;
    }
    return NULL;
}

double getX(int position, char type){
    double x, x1, x2, y1, y2;
    void* element;
    for(int i = 0; i < position; i++){
        element = getCurrentElement(i);
    }
    if(type == 'c'){
        x = getCircleX(element);
    }
    else if(type == 'r'){
        x = getRectX(element);
    }
    else if(type == 'l'){
        x1 = getLineX1(element);
        x2 = getLineX2(element);
        if(x1 < x2){
            x = x1;
        }
        else if(x1 > x2){
            x = x2;
        }
        else{
            y1 = getLineY1(element);
            y2 = getLineY2(element);
            if(y1 < y2){
                x = x1;
            }
            else{
                x = x2;
            }
        }
    }
    else if(type == 't'){
        x = getTxtX(element);
    }
    return x;
}

double getY(int position, char type){
    double y, y1, y2;
    void* element;
    for(int i = 0; i < position; i++){
        element = getCurrentElement(i);
    }
    if(type == 'c'){
        y = getCircleY(element);
    }
    else if(type == 'r'){
        y = getRectY(element);
    }
    else if(type == 'l'){
        y1 = getLineY1(element);
        y2 = getLineY2(element);
        if(y1 < y2){
            y = y1;
        }
        else{
            y = y2;
        }
    }
    else if(type == 't'){
        y = getTxtY(element);
    }
    return y;
}