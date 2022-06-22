#include "geo.h"
#include "tree.h"
#include "circle.h"

void* getGeoParameters(char* pathIn, char* fileGeo){
    char filename[150];
    strcpy(filename, pathIn);
    strcat(filename, "/");
    strcat(filename, fileGeo);
    strcat(filename, ".geo");
    FILE *pfileGeo = fopen(filename, "r");
    if(pfileGeo == NULL){
        return NULL;
    }
    char function, colorBorder[20], colorFill[20], a, txt[30];
    int id;
    double x1, y1, x2, y2, r, w, h;
    void* element;

    void* tree = newTree();
    void* root = getRoot(tree);

    while(!feof(pfileGeo)){
        function = getc(pfileGeo);
        if(function == 'c'){
            fscanf(pfileGeo, "%d %lf %lf %lf %s %s", &id, &x1, &y1, &r, colorBorder, colorFill);
            element = newCircle(id, x1, y1, r, colorBorder, colorFill);
            root = insertTree(x1, y1, tree, root, function, element);
        }
        else if(function == 'r'){
            fscanf(pfileGeo, "%d %lf %lf %lf %lf %s %s", &id, &x1, &y1, &w, &h, colorBorder, colorFill);
            element = newRect(id, x1, y1, w, h, colorBorder, colorFill);
            root = insertTree(x1, y1, tree, root, function, element);
        }
        else if(function == 'l'){
            fscanf(pfileGeo, "%d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, colorBorder);
            element = newLine(id, x1, y1, x2, y2, colorBorder);
            root = insertTree(x1, y1, tree, root, function, element);
        }
        else if(function == 't'){
            fscanf(pfileGeo, "%d %lf %lf %s %s %c %[^\n]s", &id, &x1, &y1, colorBorder, colorFill, &a, txt);
            element = newTxt(id, x1, y1, colorBorder, colorFill, a, txt);
            root = insertTree(x1, y1, tree, root, function, element);
        }
    }
    fclose(pfileGeo);
    return tree;
}