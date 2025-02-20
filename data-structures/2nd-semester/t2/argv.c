#include "argv.h"

struct checkedPaths{
    bool givenPathIn;
    bool pathIn;
    bool givenPathOut;
    bool pathOut;
    bool fileGeo;
    bool fileQry;
};

void* newCheckedPaths(){
    struct checkedPaths* new = (struct checkedPaths*)malloc(sizeof(struct checkedPaths));
    return new;
}

void setCheckedPaths(void* checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->givenPathIn = false;
    aux->pathIn = false;
    aux->givenPathOut = false;
    aux->pathOut = false;
    aux->fileGeo = false;
    aux->fileQry = false;
}

void freeCheckedPaths(void* checkedPaths){
    free(checkedPaths);
}

void setGivenPathInTrue(void* checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->givenPathIn = true;
}

void setPathInTrue(void* checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->pathIn = true;
}

void setPathOutTrue(void* checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->pathOut = true;
}

void setGivenPathOutTrue(void* checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->givenPathOut = true;
}

void setFileGeoTrue(void* checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->fileGeo = true;
}

void setFileQryTrue(void* checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    aux->fileQry = true;
}

bool checkCheckedPaths(void* checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    if(aux->pathIn == true && aux->givenPathOut && aux->pathOut == true && aux->fileGeo == true && aux->fileQry == true){
        return true;
    }
    else{
        return false;
    }
}

bool getCheckedGivenPathIn(void* checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    return aux->givenPathIn;
}

bool getCheckedPathIn(void* checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    return aux->pathIn;
}

bool getCheckedGeo(void* checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    return aux->fileGeo;
}

bool getCheckedQry(void* checkedPaths){
    struct checkedPaths* aux = checkedPaths;
    return aux->fileQry;
}

void setArgv(int argc, char** argv, void* paths, void* checkedPaths){
    int i = 1;
    if(argc < 3){
        printf("Erro: argumentos faltando\n");
        return;
    }

    setCheckedPaths(checkedPaths);

    while(i < argc){ 
        if(strcmp(argv[i], "-e") == 0){ //PATH PARA DIRETÓRIO BASE DE ENTRADA (BED)
            i++;
            allocGivenPathIn(paths, strlen(argv[i]) + 1);
            setGivenPathIn(paths, argv[i]);
            setGivenPathInTrue(checkedPaths);
            if(checkRelPathIn(paths) == true){ //IF GIVEN PATH IN HAS RELATIVE PATH
                char* tempPathIn = getRelPathIn(paths);
                buildPathIn(paths, tempPathIn);
            }
            else if(checkAbsPathIn(paths) == true){ //IF GIVEN PATH IN HAS ABSOLUTE PATH
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
            if(checkRelPathOut(paths) == true){ //IF GIVEN PATH OUT HAS RELATIVE PATH
                char* tempPathOut = getRelPathOut(paths);
                buildPathOut(paths, tempPathOut);
            }
            else if(checkAbsPathOut(paths) == true){ //IF GIVEN PATH OUT HAS ABSOLUTE PATH
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
            if(checkRelGeo(paths) == true){
                char* geoArr = calloc(strlen(auxGeo) + 1, sizeof(char));
                int last = 0;
                int begin = 0;
                if(auxGeo[0] == '.' || auxGeo[0] == '/'){
                    begin++;
                    if(auxGeo[1] == '/'){
                        begin++;
                    }
                }
                for(int j = begin; j < strlen(auxGeo); j++){
                    if(auxGeo[j] == '.'){
                        geoArr[last] = '\0';
                        break;
                    }
                    else{   
                        geoArr[last] = auxGeo[j];
                        last++;
                    }
                }
                last = 0;
                int n = 0;
                for(int j = 0; j < strlen(geoArr); j++){
                    if(geoArr[j] == '/'){
                        n = j;
                    }
                }
                for(int j = n + 1; j < strlen(geoArr); j++){
                    if(geoArr[j] == '.'){
                        tempGeo[last] = '\0';
                        break;
                    }
                    else{
                        tempGeo[last] = geoArr[j];
                        last++;
                    }
                }
                reallocGeo(paths, strlen(geoArr) + 1);
                setGivenFileGeo(paths, geoArr);
                free(geoArr);
            }
            else{
                strcpy(tempGeo, argv[i]);
                for(int j = 0; j < strlen(tempGeo); j++){
                    if(tempGeo[j] == '.'){
                        tempGeo[j] = '\0';
                    }
                }
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
            if(checkRelQry(paths) == true){ //IF GIVEN GEO FILE HAS RELATIVE PATH
                char* qryArr = calloc(strlen(auxQry) + 1, sizeof(char));
                int last = 0;
                int begin = 0;
                if(auxQry[0] == '.' || auxQry[0] == '/'){ //REMOVING RELATIVE PATH STUFF
                    begin++;
                    if(auxQry[1] == '/'){
                        begin++;
                    }
                }
                for(int j = begin; j < strlen(auxQry); j++){ //REMOVING EXTENSION IF IT EXISTS
                    if(auxQry[j] == '.'){
                        qryArr[last] = '\0';
                        break;
                    }
                    else{   
                        qryArr[last] = auxQry[j];
                        last++;
                    }
                }
                last = 0;
                int n = 0;
                for(int j = 0; j < strlen(qryArr); j++){
                    if(qryArr[j] == '/'){
                        n = j;
                    }
                }
                for(int j = n + 1; j < strlen(qryArr); j++){
                    tempQry[last] = qryArr[j];
                    last++;
                }
                reallocQry(paths, strlen(qryArr) + 1);
                setGivenFileQry(paths, qryArr);
                free(qryArr);
            }
            else{
                strcpy(tempQry, argv[i]);
                for(int j = 0; j < strlen(tempQry); j++){
                    if(tempQry[j] == '.'){
                        tempQry[j] = '\0';
                    }
                }
                reallocQry(paths, strlen(tempQry) + 1);
                setGivenFileQry(paths, tempQry);
            }
            allocFileQry(paths, strlen(tempQry) + 1);
            setFileQry(paths, tempQry);
            setFileQryTrue(checkedPaths);
            free(tempQry);
            free(auxQry);
        }
        i++;
    }
    
    if(getCheckedGivenPathIn(checkedPaths) == false){
        allocGivenPathIn(paths, 1);
        setGivenPathIn(paths, "");
    }

    if(getCheckedPathIn(checkedPaths) == false){
        buildWholePathIn(paths);
        setPathInTrue(checkedPaths);
    }

    if(getCheckedGeo(checkedPaths) == true && getCheckedQry(checkedPaths) == true){
        char tempCat[50];
        strcpy(tempCat, getFileGeo(paths));
        strcat(tempCat, "-");
        strcat(tempCat, getFileQry(paths));
        allocCatGeoQry(paths, strlen(tempCat) + 1);
        setCatGeoQry(paths, tempCat);
    }
}