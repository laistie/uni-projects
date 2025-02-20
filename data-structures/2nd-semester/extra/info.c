#include "info.h"

struct info{
    char type;
    void* info;
};

InfoStruct newInfo(char type, void* info){
    struct info* new = (struct info*)malloc(sizeof(struct info));
    new->type = type;
    new->info = info;
    return new;
} 

char getInfoType(InfoStruct node){
    struct info* aux = node;
    return aux->type;
}

InfoElement getInfoFromInfo(InfoStruct node){
    struct info* aux = node;
    return aux->info;
}

void freeInfo(InfoStruct node){
    struct info* aux = node;
    free(aux->info);
    free(node);
}