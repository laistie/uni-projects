#include "sel.h"

struct selectedList{
    struct selectedList* prev;
    int id;
    char elementType;
    struct selectedList* next;
};

struct selectedList* headSel = NULL;

void* newSelList(){
    struct selectedList* new = (struct selectedList*)malloc(sizeof(struct selectedList));
    return new;
}

void* newSel(void* selectedList, int id, char elementType){
    struct selectedList* new = (struct selectedList*)malloc(sizeof(struct selectedList));
    new->id = id;
    new->elementType = elementType;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

void insertSel(void* selectedList, int id, char elementType){
    struct selectedList* new = newSel(selectedList, id, elementType);
    if( headSel == NULL){
        new->prev = NULL;
        headSel = new;
        return;
    }
    struct selectedList* aux =  headSel;
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->next = new;
    new->prev = aux;
}

bool checkSelected(void* selectedList, char type, int id){
    struct selectedList* aux = headSel;
    if(aux == NULL){
        return false;
    }
    while(aux != NULL){
        if(aux->elementType == type && aux->id == id){
            return true;
        }
        aux = aux->next;
    }
    return false;
}

void rmvSelAll(){
    if(headSel == NULL){
        return;
    }
    void* nodeAux, *currentHead, *nextHead;
    do{
        currentHead =  headSel;
        nodeAux = currentHead; 
        nextHead =  headSel->next;
        headSel =  headSel->next;
        free(nodeAux);
    } while(nextHead != NULL);
    headSel = NULL;
}

int getSelSize(void* selectedList){
    int size = 0;
    if(headSel == NULL){
        return size;
    }
    struct selectedList* aux = headSel;
    while(aux != NULL){
        size++;
        aux = aux->next;
    }
    return size;
}

int getSelId(void* selectedList, int visits){
    struct selectedList* aux = headSel;
    for(int i = 0; i < visits; i++){
        aux = aux->next;
    }
    return aux->id;
}

char getSelType(void* selectedList, int visits){
    struct selectedList* aux = headSel;
    for(int i = 0; i < visits; i++){
        aux = aux->next;
    }
    return aux->elementType;
}

int getLastSel(void* selectedList){
    struct selectedList* aux = headSel;
    while(aux->next != NULL){
        aux = aux->next;
    }
    return aux->id;
}

char getLastType(void* selectedList){
    struct selectedList* aux = headSel;
    while(aux->next != NULL){
        aux = aux->next;
    }
    return aux->elementType;
}

void rmvFirstSel(void* selectedList){
    struct selectedList* aux = headSel;
    headSel = headSel->next;
    free(aux);
}

void rmvLastSel(void* selectedList){
    struct selectedList* aux = headSel;
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->prev->next = NULL;
    free(aux);
}

void printSelList(){
    struct selectedList* aux =  headSel;
    if(aux == NULL){
        printf("\nErro: lista de figuras selecionadas vazia\n");
    }
    else{
        printf("\n---selected list---\n");
        while(aux != NULL){
            printf(" %c(%d) ->", aux->elementType, aux->id);
            aux = aux->next;
        }
    }
    printf("\n\n");
}

void freeSelList(void* selectedList){
    if(headSel == NULL){
        free(selectedList);
        return;
    }
    void* nodeAux, *currentHead, *nextHead;
    do{
        currentHead =  headSel;
        nodeAux = currentHead; 
        nextHead =  headSel->next;
        headSel =  headSel->next;
        free(nodeAux);
    } while(nextHead != NULL);
    free(selectedList);
}