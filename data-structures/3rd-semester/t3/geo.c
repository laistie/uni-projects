#include "geo.h"
#include "paths.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "txt.h"
#include "SRbTree.h"
#include "info.h"

SRbTree getGeoParameters(void* paths){
    char filename[150];
    strcpy(filename, getPathIn(paths));
    strcat(filename, "/");
    strcat(filename, getGivenGeo(paths));
    strcat(filename, ".geo");
    FILE* pfileGeo = fopen(filename, "r");
    if(!pfileGeo) return NULL;
    char function, colorBorder[20], colorFill[20], a, txt[100];
    int id;
    double x1, y1, x2, y2, r, w, h, mbbX1, mbbY1, mbbX2, mbbY2;
    InfoStruct infoNode;
    Info element;

    SRbTree tree = createSRb(getEpsilon(paths));

    while(!feof(pfileGeo)){
        function = getc(pfileGeo);
        if(function == 'c'){
            fscanf(pfileGeo, "%d %lf %lf %lf %s %s\n", &id, &x1, &y1, &r, colorBorder, colorFill);
            element = newCircle(id, x1, y1, r, colorBorder, colorFill);
            infoNode = newInfo(function, element);
            mbbX1 = getCircleMBBX1(x1, r);
            mbbY1 = getCircleMBBY1(y1, r);
            mbbX2 = getCircleMBBX2(x2, r);
            mbbY2 = getCircleMBBY2(y2, r);
            insertSRb(tree, x1, y1, mbbX1, mbbY1, mbbX2, mbbY2, infoNode);
        }
        else if(function == 'r'){
            fscanf(pfileGeo, "%d %lf %lf %lf %lf %s %s\n", &id, &x1, &y1, &w, &h, colorBorder, colorFill);
            element = newRect(id, x1, y1, w, h, colorBorder, colorFill);
            infoNode = newInfo(function, element);
            insertSRb(tree, x1, y1, x1, y1, x1 + w, y1 + h, infoNode);
        }
        else if(function == 'l'){
            fscanf(pfileGeo, "%d %lf %lf %lf %lf %s\n", &id, &x1, &y1, &x2, &y2, colorBorder);
            element = newLine(id, x1, y1, x2, y2, colorBorder);
            infoNode = newInfo(function, element);
            if(x1 > x2){
                insertSRb(tree, x1, y1, x1, y1, x2, y2, infoNode);
            }else{ 
                insertSRb(tree, x1, y1, x2, y2, x1, y1, infoNode);
            }
        }
        else if(function == 't'){
            fscanf(pfileGeo, "%d %lf %lf %s %s %c %s\n", &id, &x1, &y1, colorBorder, colorFill, &a, txt);
            element = newTxt(id, x1, y1, colorBorder, colorFill, a, txt);
            infoNode = newInfo(function, element);
            insertSRb(tree, x1, y1, x1, y1, x1, y1, infoNode);
        }
    }
    fclose(pfileGeo);
    return tree;
}