#include "paths.h"

struct allPaths{
    char* givenPathIn;
    char* pathIn;
    char* givenPathOut;
    char* pathOut;
    char* givenFileGeo;
    char* filenameGeo;
    char* givenFileQry;
    char* filenameQry;
    char* catGeoQry;
};

void* newPaths(){
    struct allPaths* new = (struct allPaths*)malloc(sizeof(struct allPaths));
    return new;
}

void printPaths(void* paths){
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
    if(aux->catGeoQry){
        printf("\ncat geo qry: %s\n", aux->catGeoQry);
    }
}

void freePaths(void* paths){
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

void allocGivenPathIn(void* paths, int size){
    struct allPaths* aux = paths;
    aux->givenPathIn = calloc(size, sizeof(char));
}

void allocPathIn(void* paths, int size){
    struct allPaths* aux = paths;
    aux->pathIn = calloc(size, sizeof(char));
}

void allocGivenPathOut(void* paths, int size){
    struct allPaths* aux = paths;
    aux->givenPathOut = calloc(size, sizeof(char));
}

void allocPathOut(void* paths, int size){
    struct allPaths* aux = paths;
    aux->pathOut = calloc(size, sizeof(char));
}

void allocGivenFileGeo(void* paths, int size){
    struct allPaths* aux = paths;
    aux->givenFileGeo = calloc(size, sizeof(char));
}

void allocFileGeo(void* paths, int size){
    struct allPaths* aux = paths;
    aux->filenameGeo = calloc(size, sizeof(char));
}

void allocGivenFileQry(void* paths, int size){
    struct allPaths* aux = paths;
    aux->givenFileQry = calloc(size, sizeof(char));
}

void allocFileQry(void* paths, int size){
    struct allPaths* aux = paths;
    aux->filenameQry = calloc(size, sizeof(char));
}

void allocCatGeoQry(void* paths, int size){
    struct allPaths* aux = paths;
    aux->catGeoQry = calloc(size, sizeof(char));
}

void reallocGeo(void* paths, int size){
    struct allPaths* aux = paths;
    free(aux->givenFileGeo);
    aux->givenFileGeo = calloc(size, sizeof(char));
}

void reallocQry(void* paths, int size){
    struct allPaths* aux = paths;
    free(aux->givenFileQry);
    aux->givenFileQry = calloc(size, sizeof(char));
}

void setGivenPathIn(void* paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->givenPathIn, name);
}

void setPathIn(void* paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->pathIn, name);
}

void setGivenPathOut(void* paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->givenPathOut, name);
}

void setPathOut(void* paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->pathOut, name);
}

void setGivenFileGeo(void* paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->givenFileGeo, name);
}

void resetGeo(void* paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->givenFileGeo, name);
}

void setFileGeo(void* paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->filenameGeo, name);
}

void setGivenFileQry(void* paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->givenFileQry, name);
}

void setFileQry(void* paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->filenameQry, name);
}

void setCatGeoQry(void* paths, char* name){
    struct allPaths* aux = paths;
    strcpy(aux->catGeoQry, name);
}

bool checkFileGeo(void* paths){
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

bool checkFileQry(void* paths){
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

bool checkAbsPathIn(void* paths){
    struct allPaths* aux = paths;
    char wanted = '/';
    char* slash = strrchr(aux->givenPathIn, wanted);
    if(slash == NULL){
        return false;
    }
    else{
        return true;
    }
}

bool checkRelPathIn(void* paths){
    struct allPaths* aux = paths;
    char* wanted = "./";
    char* dotslash = strstr(aux->givenPathIn, wanted);
    if(dotslash == NULL){
        return false;
    }
    else{
        return true;
    }
}

bool checkAbsPathOut(void* paths){
    struct allPaths* aux = paths;
    char wanted = '/';
    char* slash = strrchr(aux->givenPathOut, wanted);
    if(slash == NULL){
        return false;
    }
    else{
        return true;
    }
}

bool checkRelPathOut(void* paths){
    struct allPaths* aux = paths;
    char* wanted = "./";
    char* dotslash = strstr(aux->givenPathOut, wanted);
    if(dotslash == NULL){
        return false;
    }
    else{
        return true;
    }
}

bool checkRelGeo(void* paths){
    struct allPaths* aux = paths;
    char* wanted = "/";
    char* dotslash = strstr(aux->givenFileGeo, wanted);
    if(dotslash == NULL){
        return false;
    }
    else{
        return true;
    }
}

bool checkRelQry(void* paths){
    struct allPaths* aux = paths;
    char* wanted = "/";
    char* dotslash = strstr(aux->givenFileQry, wanted);
    if(dotslash == NULL){
        return false;
    }
    else{
        return true;
    }
}

void strcpyPathIn(void* paths, char* builtPath){
    struct allPaths* aux = paths;
    strcpy(aux->pathIn, builtPath);
}

void strcpyPathOut(void* paths, char* builtPath){
    struct allPaths* aux = paths;
    strcpy(aux->pathOut, builtPath);
}

void strcpyGeo(void* paths){
    struct allPaths* aux = paths;
    strcpy(aux->filenameGeo, aux->givenFileGeo);
}

void strcpyQry(void* paths){
    struct allPaths* aux = paths;
    strcpy(aux->filenameQry, aux->givenFileQry);
}

void buildWholePathIn(void* paths){
    struct allPaths* aux = paths;
    char currentPathIn[150];
    getcwd(currentPathIn, sizeof(currentPathIn));
    strcat(currentPathIn, "/");
    strcat(currentPathIn, aux->givenPathIn);
    allocPathIn(paths, strlen(currentPathIn) + 1);
    strcpyPathIn(paths, currentPathIn);
}

void buildPathIn(void* paths, char* tempPathIn){
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

void buildWholePathOut(void* paths){
    struct allPaths* aux = paths;
    char currentPathOut[150];
    getcwd(currentPathOut, sizeof(currentPathOut));
    strcat(currentPathOut, "/");
    strcat(currentPathOut, aux->givenPathOut);
    strcat(currentPathOut, "/");
    allocPathOut(paths, strlen(currentPathOut) + 1);
    strcpyPathOut(paths, currentPathOut);
}

void buildPathOut(void* paths, char* tempPathOut){
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

char* getRelPathIn(void* paths){
    struct allPaths* aux = paths;
    char* wanted = "./";
    char* slash = strstr(aux->givenPathIn, wanted);
    char slashArr[strlen(slash)];
    strcpy(slashArr, slash);
    memmove(slash, slashArr + 2, strlen(slashArr));
    return slash;
}

char* getRelPathOut(void* paths){
    struct allPaths* aux = paths;
    char* wanted = "./";
    char* slash = strstr(aux->givenPathOut, wanted);
    char slashArr[strlen(slash)];
    strcpy(slashArr, slash);
    memmove(slash, slashArr + 2, strlen(slashArr));
    return slash;
}

char* getPathIn(void* paths){
    struct allPaths* aux = paths;
    return aux->pathIn;
}

char* getPathOut(void* paths){
    struct allPaths* aux = paths;
    return aux->pathOut;
}

char* getGivenGeo(void* paths){
    struct allPaths* aux = paths;
    return aux->givenFileGeo;
}

char* getFileGeo(void* paths){
    struct allPaths* aux = paths;
    return aux->filenameGeo;
}

char* getGivenQry(void* paths){
    struct allPaths* aux = paths;
    return aux->givenFileQry;
}

char* getFileQry(void* paths){
    struct allPaths* aux = paths;
    return aux->filenameQry;
}

char* getCatGeoQry(void* paths){
    struct allPaths* aux = paths;
    return aux->catGeoQry;
}