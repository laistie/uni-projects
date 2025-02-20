#include "geo.h"


void* getGeoParameters(char* pathIn, char* filenameGeo){
    char filename[150];
    strcpy(filename, pathIn);
    strcat(filename, "/");
    strcat(filename, filenameGeo);
    strcat(filename, ".geo");
    FILE *pfileGeo = fopen(filename, "r");
    if(pfileGeo == NULL){
        printf("\nErro: nao foi possivel abrir %s\n", filename);
        return NULL;
    }
    else{
        printf("\nArquivo %s aberto com sucesso\n", filename);
    }
    char function;
    
    int id;
    double x1, y1, x2, y2, w, h, r;
    char colorBorder[20], colorFill[20], a, txt[30];

    void* geometryList = newGeoList();
    void* element;

    while(!feof(pfileGeo)){
        function = getc(pfileGeo);
        if(function == 'c'){
            fscanf(pfileGeo, "%d %lf %lf %lf %s %s", &id, &x1, &y1, &r, colorBorder, colorFill);
            element = newCircle(id, x1, y1, r, colorBorder, colorFill);
            insertGeo(geometryList, function, element);
        }
        else if(function == 'r'){
            fscanf(pfileGeo, "%d %lf %lf %lf %lf %s %s", &id, &x1, &y1, &w, &h, colorBorder, colorFill);
            element = newRect(id, x1, y1, w, h, colorBorder, colorFill);
            insertGeo(geometryList, function, element);
        }
        else if(function == 'l'){
            fscanf(pfileGeo, "%d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, colorBorder);
            element = newLine(id, x1, y1, x2, y2, colorBorder);
            insertGeo(geometryList, function, element);
        }
        else if(function == 't'){
            fscanf(pfileGeo, "%d %lf %lf %s %s %c %[^\n]s", &id, &x1, &y1, colorBorder, colorFill, &a, txt);
            element = newTxt(id, x1, y1, colorBorder, colorFill, a, txt);
            insertGeo(geometryList, function, element);
        }
    }
    fclose(pfileGeo);
    return geometryList;
}