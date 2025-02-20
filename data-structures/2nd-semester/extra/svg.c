#include "svg.h"

FILE *newSvg(char *pathOut, char *filenameGeo){
    char filename[150];
    strcpy(filename, pathOut);
    strcat(filename, "/");
    strcat(filename, filenameGeo);
    strcat(filename, ".svg");
    FILE *pfileSvg = fopen(filename, "w");
    if (pfileSvg == NULL)
    {
        return NULL;
    }
    fprintf(pfileSvg, "<svg viewBox=\" 0 -10 1000 1000\" xmlns=\"http://www.w3.org/2000/svg\">");
    fprintf(pfileSvg, "\n\t<defs>");
    fprintf(pfileSvg, "\n\t\t<marker id=\"arrowhead\" makerWidth=\"3.5\" markerHeight=\"5\" refX=\"0\" refY=\"2.5\" orient=\"auto\">");
    fprintf(pfileSvg, "\n\t\t\t<polygon points=\"0 0, 2.5 2.5, 0 5\"/>");
    fprintf(pfileSvg, "\n\t\t</marker>");
    fprintf(pfileSvg, "\n\t</defs>");
    fprintf(pfileSvg, "\n\t<line x1=\"-0.5\" y1=\"0\" x2=\"1000\" y2=\"0\" style=\"stroke:black;stroke-width:1\" marker-end=\"url(#arrowhead)\"/>");
    fprintf(pfileSvg, "\n\t<line x1=\"0\" y1=\"0\" x2=\"0\" y2=\"900\" style=\"stroke:black; stroke-width:1\" marker-end=\"url(#arrowhead)\"/>");
    fprintf(pfileSvg, "\n\t<text x=\"1010\" y=\"0\" style=\"font:15px sans-serif; stroke:black; stroke-width:0.5; text-anchor:start\">x</text>");
    fprintf(pfileSvg, "\n\t<text x=\"0\" y=\"920\" style=\"font:15px sans-serif; stroke:black; stroke-width:0.5; text-anchor:middle\">y</text>");
    return pfileSvg;
}

void drawCircle(FILE *svg, int id, double x, double y, double r, char colorBorder[20], char colorFill[20]){
    fprintf(svg, "\n\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" style=\"stroke:%s; stroke-width:0.5; fill:%s; fill-opacity: .25\"/>", id, x, y, r, colorBorder, colorFill);
}

void drawRect(FILE *svg, int id, double x, double y, double w, double h, char colorBorder[20], char colorFill[20]){
    fprintf(svg, "\n\t<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"stroke:%s; stroke-width:0.5; fill:%s; fill-opacity: .25\"/>", id, x, y, w, h, colorBorder, colorFill);
}

void drawLine(FILE *svg, int id, double x1, double y1, double x2, double y2, char color[20]){
    fprintf(svg, "\n\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:%s; stroke-width:0.5\"/>", id, x1, y1, x2, y2, color);
}

void drawText(FILE *svg, int id, double x, double y, char colorBorder[20], char colorFill[20], char a, char txt[30]){
    char anchor[10];
    if (a == 'i'){
        strcpy(anchor, "start");
    }
    else if (a == 'm'){
        strcpy(anchor, "middle");
    }
    else if (a == 'f'){
        strcpy(anchor, "end");
    }
    else if (!a){
        strcpy(anchor, "start");
    }
    fprintf(svg, "\n\t<text id=\"%d\" x=\"%lf\" y=\"%lf\" style=\"font:7.5px sans-serif; stroke:%s; stroke-width:0.5; fill:%s; text-anchor:%s;\">", id, x, y, colorBorder, colorFill, anchor);
    fprintf(svg, "\n\t\t%s", txt);
    fprintf(svg, "\n\t</text>");
}

void closeSvg(FILE *svg){
    fprintf(svg, "\n</svg>");
    fclose(svg);
}

void printTSvg(Info i, double x, double y, void *aux){
    FILE *pSvg = aux;
    if(getInfoType(i) == 'c'){
        int id = getCircleId(getInfoFromInfo(i));
        double r = getCircleR(getInfoFromInfo(i));
        char colorBorder[20], colorFill[20];
        strcpy(colorBorder, getCircleBorder(getInfoFromInfo(i)));
        strcpy(colorFill, getCircleFill(getInfoFromInfo(i)));
        drawCircle(pSvg, id, x, y, r, colorBorder, colorFill);
    }
    else if(getInfoType(i) == 'r'){
        int id = getRectId(getInfoFromInfo(i));
        double w = getRectW(getInfoFromInfo(i));
        double h = getRectH(getInfoFromInfo(i));
        char colorBorder[20], colorFill[20];
        strcpy(colorBorder, getRectBorder(getInfoFromInfo(i)));
        strcpy(colorFill, getRectFill(getInfoFromInfo(i)));
        drawRect(pSvg, id, x, y, w, h, colorBorder, colorFill);
    }
    else if(getInfoType(i) == 'l'){
        int id = getLineId(getInfoFromInfo(i));
        double x1 = getLineX1(getInfoFromInfo(i));
        double y1 = getLineY1(getInfoFromInfo(i));
        double x2 = getLineX2(getInfoFromInfo(i));
        double y2 = getLineY2(getInfoFromInfo(i));
        char colorBorder[20];
        strcpy(colorBorder, getLineBorder(getInfoFromInfo(i)));
        drawLine(pSvg, id, x1, y1, x2, y2, colorBorder);
    }
    else if(getInfoType(i) == 't'){
        int id = getTxtId(getInfoFromInfo(i));
        char colorBorder[20], colorFill[20], a, txt[30];
        strcpy(colorBorder, getTxtBorder(getInfoFromInfo(i)));
        strcpy(colorFill, getTxtFill(getInfoFromInfo(i)));
        a = getA(getInfoFromInfo(i));
        strcpy(txt, getTxt(getInfoFromInfo(i)));
        drawText(pSvg, id, x, y, colorBorder, colorFill, a, txt);
    }
}

void writeSvg(FILE *svg, YxxTree tree){
    visitaProfundidadeYxxT(tree, printTSvg, svg);
}

void updateTSvg(Info i, double x, double y, void *aux){
    FILE *pSvg = aux;
    bool checker = checkIsInList(i);
    if(!checker){
        if(getInfoType(i) == 'c'){
            int id = getCircleId(getInfoFromInfo(i));
            double r = getCircleR(getInfoFromInfo(i));
            char colorBorder[20], colorFill[20];
            strcpy(colorBorder, getCircleBorder(getInfoFromInfo(i)));
            strcpy(colorFill, getCircleFill(getInfoFromInfo(i)));
            drawCircle(pSvg, id, x, y, r, colorBorder, colorFill);
        }
        else if(getInfoType(i) == 'r'){
            int id = getRectId(getInfoFromInfo(i));
            double w = getRectW(getInfoFromInfo(i));
            double h = getRectH(getInfoFromInfo(i));
            char colorBorder[20], colorFill[20];
            strcpy(colorBorder, getRectBorder(getInfoFromInfo(i)));
            strcpy(colorFill, getRectFill(getInfoFromInfo(i)));
            drawRect(pSvg, id, x, y, w, h, colorBorder, colorFill);
        }
        else if(getInfoType(i) == 'l'){
            int id = getLineId(getInfoFromInfo(i));
            double x1 = getLineX1(getInfoFromInfo(i));
            double y1 = getLineY1(getInfoFromInfo(i));
            double x2 = getLineX2(getInfoFromInfo(i));
            double y2 = getLineY2(getInfoFromInfo(i));
            char colorBorder[20];
            strcpy(colorBorder, getLineBorder(getInfoFromInfo(i)));
            drawLine(pSvg, id, x1, y1, x2, y2, colorBorder);
        }
        else if(getInfoType(i) == 't'){
            int id = getTxtId(getInfoFromInfo(i));
            char colorBorder[20], colorFill[20], a, txt[30];
            strcpy(colorBorder, getTxtBorder(getInfoFromInfo(i)));
            strcpy(colorFill, getTxtFill(getInfoFromInfo(i)));
            a = getA(getInfoFromInfo(i));
            strcpy(txt, getTxt(getInfoFromInfo(i)));
            drawText(pSvg, id, x, y, colorBorder, colorFill, a, txt);
        }
    }
}

void updateDpsSvg(FILE* pSvg, YxxTree tree, List list, int i, double dx, double dy, char colorBorder[20], char colorFill[20]){
    Node root = getRoot(tree);
    Element element;
    InfoStruct infoNode;

    for(int j = 0; j < getListSize(list); j++){
        element = getElementAtPos(j);
        if(getInfoType(element) == 'c'){
            double x = getCircleX(getInfoFromInfo(element)) + dx;
            double y = getCircleY(getInfoFromInfo(element)) + dy;
            double r = getCircleR(getInfoFromInfo(element));
            element = newCircle(i, x, y, r, colorBorder, colorFill);
            infoNode = newInfo('c', element);
            root = insertYxxT(tree, root, x, y, infoNode);
            drawCircle(pSvg, i, x, y, r, colorBorder, colorFill);
        }
        else if(getInfoType(element) == 'r'){
            double x = getRectX(getInfoFromInfo(element)) + dx;
            double y = getRectY(getInfoFromInfo(element)) + dy;
            double w = getRectW(getInfoFromInfo(element));
            double h = getRectH(getInfoFromInfo(element));
            element = newRect(i, x, y, w, h, colorBorder, colorFill);
            infoNode = newInfo('r', element);
            root = insertYxxT(tree, root, x, y, infoNode);
            drawRect(pSvg, i, x, y, w, h, colorBorder, colorFill);
        }
        else if(getInfoType(element) == 'l'){
            double x1 = getLineX1(getInfoFromInfo(element)) + dx;
            double y1 = getLineY1(getInfoFromInfo(element)) + dy;
            double x2 = getLineX2(getInfoFromInfo(element)) + dx;
            double y2 = getLineY2(getInfoFromInfo(element)) + dy;
            element = newLine(i, x1, y1, x2, y2, colorBorder);
            infoNode = newInfo('l', element);
            root = insertYxxT(tree, root, x1, y1, infoNode);
            drawLine(pSvg, i, x1, y1, x2, y2, colorBorder);
        }
        else if(getInfoType(element) == 't'){
            double x = getTxtX(getInfoFromInfo(element)) + dx;
            double y = getTxtY(getInfoFromInfo(element)) + dy;
            char a, txt[30];
            a = getA(getInfoFromInfo(element));
            strcpy(txt, getTxt(getInfoFromInfo(element)));
            element = newTxt(i, x, y, colorBorder, colorFill, a, txt);
            infoNode = newInfo('t', element);
            root = insertYxxT(tree, root, x, y, infoNode);
            drawText(pSvg, i, x, y, colorBorder, colorFill, a, txt);
        }
        i++;
    }
}

void updateUpsSvg(FILE* pSvg, List list, char colorBorder[20], char colorFill[20], double dx, double dy, int n){
    printf("list size: %d\n", getListSize(list));
    Element element;
    for(int i = 1; i <= abs(n); i++){
        element = getElementAtPos(getListSize(list) - i);
        if(getInfoType(element) == 'c'){
            double x = getCircleX(getInfoFromInfo(element)) + dx;
            double y = getCircleY(getInfoFromInfo(element)) + dy;
            setCircleX(getInfoFromInfo(element), x);
            setCircleY(getInfoFromInfo(element), y);
            setCircleBorder(getInfoFromInfo(element), colorBorder);
            setCircleFill(getInfoFromInfo(element), colorFill);
        }
        else if(getInfoType(element) == 'r'){
            double x = getRectX(getInfoFromInfo(element)) + dx;
            double y = getRectY(getInfoFromInfo(element)) + dy;
            setRectX(getInfoFromInfo(element), x);
            setRectY(getInfoFromInfo(element), y);
            setRectBorder(getInfoFromInfo(element), colorBorder);
            setRectFill(getInfoFromInfo(element), colorFill);
        }
        else if(getInfoType(element) == 'l'){
            double x1 = getLineX1(getInfoFromInfo(element)) + dx;
            double y1 = getLineY1(getInfoFromInfo(element)) + dy;
            double x2 = getLineX2(getInfoFromInfo(element)) + dx;
            double y2 = getLineY2(getInfoFromInfo(element)) + dy;
            setLineX1(getInfoFromInfo(element), x1);
            setLineY1(getInfoFromInfo(element), y1);
            setLineX2(getInfoFromInfo(element), x2);
            setLineY2(getInfoFromInfo(element), y2);
            setLineColor(getInfoFromInfo(element), colorBorder);
        }
        else if(getInfoType(element) == 't'){
            double x = getTxtX(getInfoFromInfo(element)) + dx;
            double y = getTxtY(getInfoFromInfo(element)) + dy;
            setTxtX(getInfoFromInfo(element), x);
            setTxtY(getInfoFromInfo(element), y);
            setTxtBorder(getInfoFromInfo(element), colorBorder);
            setTxtFill(getInfoFromInfo(element), colorFill); 
        }
    }
}