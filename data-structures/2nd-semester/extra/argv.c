#include "argv.h"

struct checkedPaths{
    bool givenPathIn, pathIn, givenPathOut, pathOut, fileGeo, fileQry, degFactor;
}; 

void* newCheckedPaths(){
    struct checkedPaths* new = (struct checkedPaths*)malloc(sizeof(struct checkedPaths));
    return new;
}

void setCheckedPaths(CheckedPaths checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->givenPathIn = aux->pathIn = aux->givenPathOut = aux->pathOut = aux->fileGeo = aux->fileQry = aux->degFactor = false;
}

void freeCheckedPaths(CheckedPaths checkedPaths){
    free(checkedPaths);
}

void setGivenPathInTrue(CheckedPaths checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->givenPathIn = true;
}

void setPathInTrue(CheckedPaths checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->pathIn = true;
}

void setPathOutTrue(CheckedPaths checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->pathOut = true;
}

void setGivenPathOutTrue(CheckedPaths checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->givenPathOut = true;
}

void setFileGeoTrue(CheckedPaths checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->fileGeo = true;
}

void setFileQryTrue(CheckedPaths checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->fileQry = true;
}

void setDegFactorTrue(CheckedPaths checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->degFactor = true;
}

bool checkCheckedPaths(CheckedPaths checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    if(aux->pathIn && aux->givenPathOut && aux->pathOut && aux->fileGeo){
        return true;
    }
    return false;
}

bool getCheckedGivenPathIn(CheckedPaths checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    return aux->givenPathIn;
}

bool getCheckedPathIn(CheckedPaths checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    return aux->pathIn;
}

bool getCheckedGeo(CheckedPaths checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    return aux->fileGeo;
}

bool getCheckedQry(CheckedPaths checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    return aux->fileQry;
}

bool getCheckedDegFactor(CheckedPaths checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    return aux->degFactor;
}

void setArgv(int argc, char** argv, void* paths, CheckedPaths checkedPaths){
    int i = 1;

    setCheckedPaths(checkedPaths);

    while(i < argc){ 
        if(strcmp(argv[i], "-e") == 0){ //PATH PARA DIRETÓRIO BASE DE ENTRADA (BED)
            i++;
            allocGivenPathIn(paths, strlen(argv[i]) + 1);
            setGivenPathIn(paths, argv[i]);
            setGivenPathInTrue(checkedPaths);
            if(checkRelPathIn(paths)){ //IF GIVEN PATH IN HAS RELATIVE PATH
                char* tempPathIn = getRelPathIn(paths);
                buildPathIn(paths, tempPathIn);
            }
            else if(checkAbsPathIn(paths)){ //IF GIVEN PATH IN HAS ABSOLUTE PATH
                allocPathIn(paths, strlen(argv[i]) + 1);
                setPathIn(paths, argv[i]);
            }
            setPathInTrue(checkedPaths);
        }
        else if(strcmp(argv[i], "-o") == 0){ //PATH PARA DIRETÓRIO BASE DE SAÍDA (BSD)
            i++;
            allocGivenPathOut(paths, strlen(argv[i]) + 1);
            setGivenPathOut(paths, argv[i]);
            setGivenPathOutTrue(checkedPaths);
            if(checkRelPathOut(paths)){ //IF GIVEN PATH OUT HAS RELATIVE PATH
                char* tempPathOut = getRelPathOut(paths);
                buildPathOut(paths, tempPathOut);
            }
            else if(checkAbsPathOut(paths)){ //IF GIVEN PATH OUT HAS ABSOLUTE PATH
                allocPathOut(paths, strlen(argv[i]) + 1);
                setPathOut(paths, argv[i]);
            }
            else{
                buildWholePathOut(paths);    
            }
            setPathOutTrue(checkedPaths);
        }
        else if(strcmp(argv[i], "-f") == 0){ //NOME DO ARQUIVO GEO SOB O DIRETÓRIO BED
            i++;
            allocGivenFileGeo(paths, strlen(argv[i]) + 1);
            setGivenFileGeo(paths, argv[i]);
            char* auxGeo = calloc(strlen(argv[i]) + 1, sizeof(char));
            strcpy(auxGeo, argv[i]);
            char* tempGeo = calloc(strlen(argv[i]) + 1, sizeof(char));
            if(checkRelGeo(paths)){
                char* geoArr = calloc(strlen(auxGeo) + 1, sizeof(char));
                int begin = 0;
                if(auxGeo[0] == '.' || auxGeo[0] == '/'){
                    begin++;
                    if(auxGeo[1] == '/'){
                        begin++;
                    }
                }
                removeExt(auxGeo, geoArr, begin);
                removeRelPath(geoArr, tempGeo);
                reallocGeo(paths, strlen(geoArr) + 1);
                setGivenFileGeo(paths, geoArr);
                free(geoArr);
            }
            else{
                strcpy(tempGeo, argv[i]);
                removeExt(tempGeo, tempGeo, 0);
                reallocGeo(paths, strlen(tempGeo) + 1);
                setGivenFileGeo(paths, tempGeo);
            }
            allocFileGeo(paths, strlen(tempGeo) + 1);
            setFileGeo(paths, tempGeo);
            setFileGeoTrue(checkedPaths);
            free(tempGeo);
            free(auxGeo);
        }
        else if(strcmp(argv[i], "-q") == 0){ //NOME DO ARQUIVO QRY SOB O DIRETÓRIO BED
            i++;
            allocGivenFileQry(paths, strlen(argv[i]) + 1);
            setGivenFileQry(paths, argv[i]);
            char* auxQry = calloc(strlen(argv[i]) + 1, sizeof(char));
            strcpy(auxQry, argv[i]);
            char* tempQry = calloc(strlen(argv[i]) + 1, sizeof(char));
            if(checkRelQry(paths)){ //IF GIVEN GEO FILE HAS RELATIVE PATH
                char* qryArr = calloc(strlen(auxQry) + 1, sizeof(char));
                int begin = 0;
                if(auxQry[0] == '.' || auxQry[0] == '/'){ //REMOVING RELATIVE PATH STUFF
                    begin++;
                    if(auxQry[1] == '/'){
                        begin++;
                    }
                }
                removeExt(auxQry, qryArr, begin);
                removeRelPath(qryArr, tempQry);
                reallocQry(paths, strlen(qryArr) + 1);
                setGivenFileQry(paths, qryArr);
                free(qryArr);
            }
            else{
                strcpy(tempQry, argv[i]);
                removeExt(tempQry, tempQry, 0);
                reallocQry(paths, strlen(tempQry) + 1);
                setGivenFileQry(paths, tempQry);
            }
            allocFileQry(paths, strlen(tempQry) + 1);
            setFileQry(paths, tempQry);
            setFileQryTrue(checkedPaths);
            free(tempQry);
            free(auxQry);
        }
        else if(strcmp(argv[i], "-fd") == 0){
            i++;
            double number;
            sscanf(argv[i], "%lf", &number);
            setDegFactor(paths, number);
            setDegFactorTrue(checkedPaths);
        }
        i++;
    }
    
    if(!getCheckedGivenPathIn(checkedPaths)){
        allocGivenPathIn(paths, 1);
        setGivenPathIn(paths, "");
    }
    if(!getCheckedPathIn(checkedPaths)){
        buildWholePathIn(paths);
        setPathInTrue(checkedPaths);
    }
    if(getCheckedGeo(checkedPaths) && getCheckedQry(checkedPaths)){
        char tempCat[50];
        strcpy(tempCat, getFileGeo(paths));
        strcat(tempCat, "-");
        strcat(tempCat, getFileQry(paths));
        allocCatGeoQry(paths, strlen(tempCat) + 1);
        setCatGeoQry(paths, tempCat);
    }
    if(!getCheckedDegFactor(checkedPaths)){
        setDegFactor(paths, 0.5);
        setDegFactorTrue(checkedPaths);
    }
}