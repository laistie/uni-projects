#include "geo.h"
#include "paths.h"
#include "yxxtree.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "txt.h"
#include "info.h"

void* getGeoParameters(void* paths){
    char filename[150];
    strcpy(filename, getPathIn(paths));
    strcat(filename, "/");
    strcat(filename, getGivenGeo(paths));
    strcat(filename, ".geo");
    FILE *pfileGeo = fopen(filename, "r");
    if(pfileGeo == NULL){
        return NULL;
    }
    char function, colorBorder[20], colorFill[20], a, txt[100];
    int id;
    double x1, y1, x2, y2, r, w, h;
    InfoStruct infoNode;
    Info element;

    YxxTree tree = newYxxTree(getDegFactor(paths));
    Node root = NULL;

    while(!feof(pfileGeo)){
        function = getc(pfileGeo);
        if(function == 'c'){
            fscanf(pfileGeo, "%d %lf %lf %lf %s %s", &id, &x1, &y1, &r, colorBorder, colorFill);
            element = newCircle(id, x1, y1, r, colorBorder, colorFill);
            infoNode = newInfo(function, element);
            root = insertYxxT(tree, root, x1, y1, infoNode);
        }
        else if(function == 'r'){
            fscanf(pfileGeo, "%d %lf %lf %lf %lf %s %s", &id, &x1, &y1, &w, &h, colorBorder, colorFill);
            element = newRect(id, x1, y1, w, h, colorBorder, colorFill);
            infoNode = newInfo(function, element);
            root = insertYxxT(tree, root, x1, y1, infoNode);
        }
        else if(function == 'l'){
            fscanf(pfileGeo, "%d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, colorBorder);
            element = newLine(id, x1, y1, x2, y2, colorBorder);
            infoNode = newInfo(function, element);
            root = insertYxxT(tree, root, x1, y1, infoNode);
        }
        else if(function == 't'){
            fscanf(pfileGeo, "%d %lf %lf %s %s %c %[^\n]s", &id, &x1, &y1, colorBorder, colorFill, &a, txt);
            element = newTxt(id, x1, y1, colorBorder, colorFill, a, txt);
            infoNode = newInfo(function, element);
            root = insertYxxT(tree, root, x1, y1, infoNode);
        }
    }
    fclose(pfileGeo);
    return tree;
}