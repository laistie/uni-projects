#include "paths.h"

struct allPaths{
    char* givenPathIn, *pathIn, *givenPathOut, *pathOut, *givenFileGeo, *filenameGeo, *givenFileQry, *filenameQry, *catGeoQry;
    double degFactor;
};

void* newPaths(){
    struct allPaths* new = (struct allPaths*)malloc(sizeof(struct allPaths));
    new->givenPathIn = new->pathIn = new->givenPathOut = new->pathOut = new->givenFileGeo = new->filenameGeo = new->givenFileQry = new->filenameQry = new->catGeoQry = NULL;
    return new;
}

void printPaths(AllPaths paths){
    struct allPaths* aux = paths;
    if(aux->givenPathIn){
        printf("\ngiven path in: %s\n", aux->givenPathIn);
    }
    if(aux->pathIn){
        printf("\npath in: %s\n", aux->pathIn);
    }
    if(aux->givenPathOut){
        printf("\ngiven path out: %s\n", aux->givenPathOut);
    }
    if(aux->pathOut){
        printf("\npath out: %s\n", aux->pathOut);
    }
    if(aux->givenFileGeo){
        printf("\ngiven geo filename: %s\n", aux->givenFileGeo);
    }
    if(aux->filenameGeo){
        printf("\ngeo filename: %s\n", aux->filenameGeo);
    }
    if(aux->givenFileQry){
        printf("\ngiven qry filename: %s\n", aux->givenFileQry);
    }
    if(aux->filenameQry){
        printf("\nqry filename: %s\n", aux->filenameQry);
    }
    if(aux->degFactor){
        printf("\ndegradation factor: %lf\n", aux->degFactor);
    }
    if(aux->catGeoQry){
        printf("\ncat geo qry: %s\n", aux->catGeoQry);
    }
}

void freePaths(AllPaths paths){
    struct allPaths* aux = paths;
    if(aux->givenPathIn){
        free(aux->givenPathIn);
    }
    if(aux->pathIn){
        free(aux->pathIn);
    }
    if(aux->givenPathOut){
        free(aux->givenPathOut);
    }
    if(aux->pathOut){
        free(aux->pathOut);
    }
    if(aux->givenFileGeo){
        free(aux->givenFileGeo);
    }
    if(aux->filenameGeo){
        free(aux->filenameGeo);
    }
    if(aux->givenFileQry){
        free(aux->givenFileQry);
    }
    if(aux->filenameQry){
        free(aux->filenameQry);
    }
    if(aux->catGeoQry){
        free(aux->catGeoQry);
    }
    free(paths);
}

void allocGivenPathIn(AllPaths paths, int size){
    struct allPaths* aux = paths;
    aux->givenPathIn = calloc(size, sizeof(char));
}

void allocPathIn(AllPaths paths, int size){
    struct allPaths* aux = paths;
    aux->pathIn = calloc(size, sizeof(char));
}

void allocGivenPathOut(AllPaths paths, int size){
    struct allPaths* aux = paths;
    aux->givenPathOut = calloc(size, sizeof(char));
}

void allocPathOut(AllPaths paths, int size){
    struct allPaths* aux = paths;
    aux->pathOut = calloc(size, sizeof(char));
}

void allocGivenFileGeo(AllPaths paths, int size){
    struct allPaths* aux = paths;
    aux->givenFileGeo = calloc(size, sizeof(char));
}

void allocFileGeo(AllPaths paths, int size){
    struct allPaths* aux = paths;
    aux->filenameGeo = calloc(size, sizeof(char));
}

void allocGivenFileQry(AllPaths paths, int size){
    struct allPaths* aux = paths;
    aux->givenFileQry = calloc(size, sizeof(char));
}

void allocFileQry(AllPaths paths, int size){
    struct allPaths* aux = paths;
    aux->filenameQry = calloc(size, sizeof(char));
}

void allocCatGeoQry(AllPaths paths, int size){
    struct allPaths* aux = paths;
    aux->catGeoQry = calloc(size, sizeof(char));
}

void reallocGeo(AllPaths paths, int size){
    struct allPaths* aux = paths;
    free(aux->givenFileGeo);
    aux->givenFileGeo = calloc(size, sizeof(char));
}

void reallocQry(AllPaths paths, int size){
    struct allPaths* aux = paths;
    free(aux->givenFileQry);
    aux->givenFileQry = calloc(size, sizeof(char));
}

void setGivenPathIn(AllPaths paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->givenPathIn, name);
}

void setPathIn(AllPaths paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->pathIn, name);
}

void setGivenPathOut(AllPaths paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->givenPathOut, name);
}

void setPathOut(AllPaths paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->pathOut, name);
}

void setGivenFileGeo(AllPaths paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->givenFileGeo, name);
}

void setFileGeo(AllPaths paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->filenameGeo, name);
}

void setGivenFileQry(AllPaths paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->givenFileQry, name);
}

void setFileQry(AllPaths paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->filenameQry, name);
}

void setDegFactor(AllPaths paths, double number){
    struct allPaths* aux = paths;
    if(number >= 0 && number <= 1){ 
        aux->degFactor = number;
    }
    else{
        printf("Aviso: fator de degradação fora do intervalo especificado. Set fd como default\n");
        aux->degFactor = 0.5;
    }
}

void setCatGeoQry(AllPaths paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->catGeoQry, name);
}

bool checkFileGeo(AllPaths paths){
    struct allPaths* aux = paths;
    const char wanted = '.';
    char* dot = strrchr(aux->filenameGeo, wanted);
    if(dot == NULL){
        return false;
    }
    else{
        if((strcmp(dot, ".geo")) == 0){
            return true;
        }
        return false;
    }
}

bool checkFileQry(AllPaths paths){
    struct allPaths* aux = paths;
    char wanted = '.';
    char* dot = strrchr(aux->filenameQry, wanted);
    if(dot == NULL){
        return false;
    }
    else{
        if((strcmp(dot, ".qry")) == 0){
            return true;
        }
        return false;
    }
}

void removeExt(char* srcArr, char* destArr, int start){
    int last = 0;
    for(int i = start; i < strlen(srcArr); i++){
        if(srcArr[i] == '.'){
            destArr[last] = '\0';
            break;
        }
        else{   
            destArr[last] = srcArr[i];
            last++;
        }
    }
}

void removeRelPath(char* srcArr, char* destArr){
    int n, last = 0;
    for(int j = 0; j < strlen(srcArr); j++){
        if(srcArr[j] == '/'){
            n = j;
        }
    }
    for(int j = n + 1; j < strlen(srcArr); j++){
        destArr[last] = srcArr[j];
        last++;
    }
}

bool checkAbsPathIn(AllPaths paths){
    struct allPaths* aux = paths;
    char wanted = '/';
    char* slash = strrchr(aux->givenPathIn, wanted);
    if(slash == NULL){
        return false;
    }
    return true;
}

bool checkRelPathIn(AllPaths paths){
    struct allPaths* aux = paths;
    char* wanted = "./";
    char* dotslash = strstr(aux->givenPathIn, wanted);
    if(dotslash == NULL){
        return false;
    }
    return true;
}

bool checkAbsPathOut(AllPaths paths){
    struct allPaths* aux = paths;
    char wanted = '/';
    char* slash = strrchr(aux->givenPathOut, wanted);
    if(slash == NULL){
        return false;
    }
    return true;
}

bool checkRelPathOut(AllPaths paths){
    struct allPaths* aux = paths;
    char* wanted = "./";
    char* dotslash = strstr(aux->givenPathOut, wanted);
    if(dotslash == NULL){
        return false;
    }
    return true;
}

bool checkRelGeo(AllPaths paths){
    struct allPaths* aux = paths;
    char* wanted = "/";
    char* dotslash = strstr(aux->givenFileGeo, wanted);
    if(dotslash == NULL){
        return false;
    }
    return true;
}

bool checkRelQry(AllPaths paths){
    struct allPaths* aux = paths;
    char* wanted = "/";
    char* dotslash = strstr(aux->givenFileQry, wanted);
    if(dotslash == NULL){
        return false;
    }
    return true;
}

void strcpyPathIn(AllPaths paths, char* builtPath){
    struct allPaths* aux = paths;
    strcpy(aux->pathIn, builtPath);
}

void strcpyPathOut(AllPaths paths, char* builtPath){
    struct allPaths* aux = paths;
    strcpy(aux->pathOut, builtPath);
}

void buildWholePathIn(AllPaths paths){
    struct allPaths* aux = paths;
    char currentPathIn[150];
    getcwd(currentPathIn, sizeof(currentPathIn));
    strcat(currentPathIn, "/");
    strcat(currentPathIn, aux->givenPathIn);
    allocPathIn(paths, strlen(currentPathIn) + 1);
    strcpyPathIn(paths, currentPathIn);
}

void buildPathIn(AllPaths paths, char* tempPathIn){
    char tempArr[strlen(tempPathIn)];
    strcpy(tempArr, tempPathIn);
    char currentPathIn[100];
    getcwd(currentPathIn, sizeof(currentPathIn));
    char builtPathIn[150];
    strcpy(builtPathIn, currentPathIn);
    strcat(builtPathIn, "/");
    strcat(builtPathIn, tempArr);
    allocPathIn(paths, strlen(builtPathIn) + 1);
    setPathIn(paths, builtPathIn);
}

void buildWholePathOut(AllPaths paths){
    struct allPaths* aux = paths;
    char currentPathOut[150];
    getcwd(currentPathOut, sizeof(currentPathOut));
    strcat(currentPathOut, "/");
    strcat(currentPathOut, aux->givenPathOut);
    strcat(currentPathOut, "/");
    allocPathOut(paths, strlen(currentPathOut) + 1);
    strcpyPathOut(paths, currentPathOut);
}

void buildPathOut(AllPaths paths, char* tempPathOut){
    char tempArr[strlen(tempPathOut)];
    strcpy(tempArr, tempPathOut);
    char currentPathOut[100];
    getcwd(currentPathOut, sizeof(currentPathOut));
    char builtPathOut[150];
    strcpy(builtPathOut, currentPathOut);
    strcat(builtPathOut, "/");
    strcat(builtPathOut, tempArr);
    strcat(builtPathOut, "/");
    allocPathOut(paths, strlen(builtPathOut) + 1);
    setPathOut(paths, builtPathOut);
}

char* getRelPathIn(AllPaths paths){
    struct allPaths* aux = paths;
    char* wanted = "./";
    char* slash = strstr(aux->givenPathIn, wanted);
    char slashArr[strlen(slash)];
    strcpy(slashArr, slash);
    memmove(slash, slashArr + 2, strlen(slashArr));
    return slash;
}

char* getRelPathOut(AllPaths paths){
    struct allPaths* aux = paths;
    char* wanted = "./";
    char* slash = strstr(aux->givenPathOut, wanted);
    char slashArr[strlen(slash)];
    strcpy(slashArr, slash);
    memmove(slash, slashArr + 2, strlen(slashArr));
    return slash;
}

char* getPathIn(AllPaths paths){
    struct allPaths* aux = paths;
    return aux->pathIn;
}

char* getPathOut(AllPaths paths){
    struct allPaths* aux = paths;
    return aux->pathOut;
}

char* getGivenGeo(AllPaths paths){
    struct allPaths* aux = paths;
    return aux->givenFileGeo;
}

char* getFileGeo(AllPaths paths){
    struct allPaths* aux = paths;
    return aux->filenameGeo;
}

char* getGivenQry(AllPaths paths){
    struct allPaths* aux = paths;
    return aux->givenFileQry;
}

char* getFileQry(AllPaths paths){
    struct allPaths* aux = paths;
    return aux->filenameQry;
}

char* getCatGeoQry(AllPaths paths){
    struct allPaths* aux = paths;
    return aux->catGeoQry;
}

double getDegFactor(AllPaths paths){
    struct allPaths* aux = paths;
    return aux->degFactor;
}