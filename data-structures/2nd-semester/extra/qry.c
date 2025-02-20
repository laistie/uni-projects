#include "qry.h"

FILE* newReport(AllPaths paths){
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".txt");
    FILE* pfileTxt = fopen(filename, "w+");
    if(!pfileTxt){
        return NULL;
    }
    fprintf(pfileTxt, "RELATÓRIO DAS FUNÇÕES UTILIZADAS NO ARQUIVO .QRY\n");
    return pfileTxt;
}

void endReport(FILE* txt){
    fprintf(txt, "\nCONSIDERAÇÕES FINAIS: enlouqueci.");
    fclose(txt);
}

FILE* openSvg(AllPaths paths){
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".svg");
    FILE* pSvg = fopen(filename, "w");
    if(!pSvg){
        return NULL;
    }
    return pSvg;
}

void drawAxis(AllPaths paths){
    FILE* pSvg = openSvg(paths);
    fprintf(pSvg, "<svg viewBox=\" 0 -10 1000 1000\" xmlns=\"http://www.w3.org/2000/svg\">");
    fprintf(pSvg, "\n\t<defs>");
    fprintf(pSvg, "\n\t\t<marker id=\"arrowhead\" makerWidth=\"3.5\" markerHeight=\"5\" refX=\"0\" refY=\"2.5\" orient=\"auto\">");
    fprintf(pSvg, "\n\t\t\t<polygon points=\"0 0, 2.5 2.5, 0 5\"/>");
    fprintf(pSvg, "\n\t\t</marker>");
    fprintf(pSvg, "\n\t</defs>");
    fprintf(pSvg, "\n\t<line x1=\"-0.5\" y1=\"0\" x2=\"1000\" y2=\"0\" style=\"stroke:black;stroke-width:1\" marker-end=\"url(#arrowhead)\"/>");
    fprintf(pSvg, "\n\t<line x1=\"0\" y1=\"0\" x2=\"0\" y2=\"900\" style=\"stroke:black; stroke-width:1\" marker-end=\"url(#arrowhead)\"/>");
    fprintf(pSvg, "\n\t<text x=\"1010\" y=\"0\" style=\"font:15px sans-serif; stroke:black; stroke-width:0.5; text-anchor:start\">x</text>");
    fprintf(pSvg, "\n\t<text x=\"0\" y=\"920\" style=\"font:15px sans-serif; stroke:black; stroke-width:0.5; text-anchor:middle\">y</text>");
    fclose(pSvg);
}

FILE* appendSvg(AllPaths paths){
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".svg");
    FILE* pSvg = fopen(filename, "a");
    if(!pSvg){
        return NULL;
    }
    return pSvg;
}

void inp(FILE* pTxt, Queue queue, YxxTree tree, int i){
    void* inpStruct = newInp(i, queue, pTxt);
    fprintf(pTxt, "\n[*] inp %d\n", i);
    visitaProfundidadeYxxT(tree, fInp, inpStruct);
    free(inpStruct);
}

void rmp(FILE* pTxt, Queue queue){
    Coordinates coordinates = getFirstCoordinates(queue);
    fprintf(pTxt, "\n[*] rmp\ncoordenada removida: (%lf, %lf)\n", getXCoord(coordinates), getYCoord(coordinates));
    dequeue(queue, coordinates);
}

void writeClp(FILE* pTxt, bool removeValue){
    if(removeValue){
        fprintf(pTxt, "\n[*] clp\ntodas as coordenadas da fila foram removidas\n");
    }
    else{
        fprintf(pTxt, "\n[*] clp\nerro ao remover coordenadas, a fila está vazia\n");
    }
}

void clp(FILE* pTxt, Queue queue){
    writeClp(pTxt, freeAllCoordinates(queue));
}

void writeSelReport(FILE* pTxt, double x, double y, double w, double h){
    fprintf(pTxt, "\n[*] sel %lf %lf %lf %lf\n", x, y, w, h);
}

void drawSelArea(FILE* pSvg, double x, double y, double w, double h){
    fprintf(pSvg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill-opacity: 0; stroke:red; stroke-width:1; stroke-dasharray: 1 1\"/>", x, y, w, h);
}

List sel(FILE* pTxt, FILE* pSvg, YxxTree tree, List list, double x, double y, double w, double h){
    list = getNodesDentroRegiaoYxxT(tree, x, y, x + w, y + h);
    drawSelArea(pSvg, x, y, w, h);
    writeSelReport(pTxt, x, y, w, h);
    reportSelections(pTxt, pSvg);
    return list;
}

void writeSelPlusReport(FILE* pTxt, double x, double y, double w, double h){
    fprintf(pTxt, "\n[*] sel+ %lf %lf %lf %lf\n", x, y, w, h);
}

void writeSelPlusSelections(FILE* pTxt, int prevSelections, int total){
    fprintf(pTxt, "figuras anteriormente selecionadas: %d\ntotal de figuras selecionadas: %d\n", prevSelections, total);
}

List selPlus(FILE* pTxt, FILE* pSvg, YxxTree tree, List prevList, double x, double y, double w, double h){
    List newlist = getNodesDentroRegiaoYxxT(tree, x, y, x + w, y + h);
    drawSelArea(pSvg, x, y, w, h);
    writeSelPlusReport(pTxt, x, y, w, h);
    int prevSelections;
    reportSelections(pTxt, pSvg);
    if(prevList){
        prevSelections = getListSize(prevList);
        mergeLists(prevList, newlist);
    }
    else{
        prevSelections = 0;
        prevList = newList();
        mergeLists(prevList, newlist);
    }
    writeSelPlusSelections(pTxt, prevSelections, getListSize(prevList));
    return prevList;
}

void writeDelsReport(FILE* pTxt){
    fprintf(pTxt, "\n[*] dels\n");
}

void dels(FILE* pTxt, FILE* pSvg, YxxTree tree, List list){
    writeDelsReport(pTxt);
    reportDeletions(pTxt);
    double x, y;
    Element element;
    Node node;
    for(int i = 0; i < getListSize(list); i++){
        element = getElementAtPos(i);
        if(getInfoType(element) == 'c'){
            x = getCircleX(getInfoFromInfo(element));
            y = getCircleY(getInfoFromInfo(element));
        }
        if(getInfoType(element) == 'r'){
            x = getRectX(getInfoFromInfo(element));
            y = getRectY(getInfoFromInfo(element));
        }
        if(getInfoType(element) == 'l'){
            x = getLineX1(getInfoFromInfo(element));
            y = getLineY1(getInfoFromInfo(element));
        }
        if(getInfoType(element) == 't'){
            x = getTxtX(getInfoFromInfo(element));
            y = getTxtY(getInfoFromInfo(element));
        }
        node = getNodeYxxT(tree, x, y, 0.01);
        removeNoYxxT(tree, node);
    }
    visitaProfundidadeYxxT(tree, updateTSvg, pSvg);
}

void dps(FILE* pSvg, YxxTree tree, List list, int i, double dx, double dy, char colorBorder[20], char colorFill[20]){
    updateDpsSvg(pSvg, tree, list, i, dx, dy, colorBorder, colorFill);
}

void ups(FILE* pSvg, YxxTree tree, List list, char colorBorder[20], char colorFill[20], double dx, double dy, int n){
    updateUpsSvg(pSvg, list, colorBorder, colorFill, dx, dy, n);
    visitaProfundidadeYxxT(tree, printTSvg, pSvg);
}

void readQry(FILE* pTxt, YxxTree tree, AllPaths paths, CheckedPaths checkedPaths){
    char filename[150];
    strcpy(filename, getPathIn(paths));
    strcat(filename, "/");
    strcat(filename, getGivenQry(paths));
    strcat(filename, ".qry");
    FILE* pfileQry = fopen(filename, "r");
    if(!pfileQry){
        return;
    }

    drawAxis(paths);
    FILE* pSvg;
    pSvg = appendSvg(paths);
    writeSvg(pSvg, tree);

    char function[5];
    List list = NULL;
    Queue queue = newQueue(MAX_QUEUE);

    while(!feof(pfileQry)){
        fscanf(pfileQry, "%s ", function);
        if(strcmp(function, "inp") == 0){
            int i;
            fscanf(pfileQry, "%d\n", &i);
            inp(pTxt, queue, tree, i);
        }
        else if(strcmp(function, "rmp") == 0){
            rmp(pTxt, queue);
        }
        else if(strcmp(function, "pol") == 0){
            printf("\n===POL===\n");
            int i;
            double d, e;
            char colorBorder[20], colorFill[20];
            fscanf(pfileQry, "%d %lf %lf %s %s\n", &i, &d, &e, colorBorder, colorFill);
            pol(pSvg, queue, i, d, e, colorBorder, colorFill);
        }
        else if(strcmp(function, "clp") == 0){
            clp(pTxt, queue);
        }
        else if(strcmp(function, "sel") == 0){
            double x, y, w, h;
            fscanf(pfileQry, "%lf %lf %lf %lf\n", &x, &y, &w, &h);
            list = sel(pTxt, pSvg, tree, list, x, y, w, h);
        }
        else if(strcmp(function, "sel+") == 0){
            double x, y, w, h;
            fscanf(pfileQry, "%lf %lf %lf %lf\n", &x, &y, &w, &h);
            list = selPlus(pTxt, pSvg, tree, list, x, y, w, h);
        }
        else if(strcmp(function, "dels") == 0){
            fclose(pSvg);
            drawAxis(paths);
            pSvg = appendSvg(paths);
            dels(pTxt, pSvg, tree, list);
        }
        else if(strcmp(function, "dps") == 0){
            int i;
            double dx, dy;
            char colorBorder[20], colorFill[20];
            fscanf(pfileQry, "%d %lf %lf %s %s\n", &i, &dx, &dy, colorBorder, colorFill);
            dps(pSvg, tree, list, i, dx, dy, colorBorder, colorFill);
        }
        else if(strcmp(function, "ups") == 0){
            fclose(pSvg);
            drawAxis(paths);
            pSvg = appendSvg(paths);
            char colorBorder[20], colorFill[20];
            double dx, dy;
            int n;
            fscanf(pfileQry, "%s %s %lf %lf %d\n", colorBorder, colorFill, &dx, &dy, &n);
            ups(pSvg, tree, list, colorBorder, colorFill, dx, dy, n);
        }
    }
    if(list){
        freeList(list);
    }
    if(queue){
        freeQueue(queue);
    }
    fclose(pfileQry);
    closeSvg(pSvg);
}