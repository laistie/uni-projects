#include "info.h"
#include "libraries.h"

struct info{
    char type;
    InfoElement info;
};

InfoStruct newInfo(char type, InfoElement info){
    struct info* new = (struct info*)calloc(1, sizeof(struct info));
    new->type = type;
    new->info = info;
    return new;
}

char getInfoType(InfoStruct node){
    struct info* aux = node;
    return aux->type;
}

InfoElement getInfoElement(InfoStruct node){
    struct info* aux = node;
    return aux->info;
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