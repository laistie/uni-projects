#include "qry.h"

FILE* newReport(AllPaths paths){
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".txt");
    FILE* pfileTxt = fopen(filename, "w+");
    if(!pfileTxt) return NULL;
    fprintf(pfileTxt, "RELATÓRIO DAS FUNÇÕES UTILIZADAS NO ARQUIVO .QRY\n");
    return pfileTxt;
}

void endReport(FILE* txt){
    fprintf(txt, "\nCONSIDERAÇÕES FINAIS: enlouquecendo cada vez mais.");
    fclose(txt);
}

FILE* openSvg(AllPaths paths){
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".svg");
    FILE* pSvg = fopen(filename, "w");
    if(!pSvg) return NULL;
    return pSvg;
}

void drawAxis(AllPaths paths){
    FILE* pSvg = openSvg(paths);
    fprintf(pSvg, "<svg viewBox=\" 0 -10 1500 1500\" xmlns=\"http://www.w3.org/2000/svg\">");
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
    if(!pSvg) return NULL;
    return pSvg;
}

void e(FILE* pTxt, SRbTree tree, double energy){
    void* energyStruct = newEnergy(energy, pTxt);
    fprintf(pTxt, "\n[*] e %lf\n", energy);
    percursoProfundidade(tree, setEnergy, energyStruct);
    free(energyStruct);
}

void mv(FILE* pSvg, FILE* pTxt, SRbTree tree, int id, double dx, double dy){
    void* mvStruct = newMv(tree, id, dx, dy, pTxt);
    fprintf(pTxt, "\n[*] mv %d %lf %lf\n", id, dx, dy);
    percursoProfundidade(tree, updateMv, mvStruct);
    free(mvStruct);
    writeSvg(pSvg, tree);
}

void mc(FILE* pSvg, FILE* pTxt, SRbTree tree, double dx, double dy, double x, double y, double w, double h){
    void* mcStruct = newMc(tree, dx, dy, x, y, w, h, pTxt);
    fprintf(pTxt, "\n[*] mc %lf %lf %lf %lf %lf %lf\n", dx, dy, x, y, w, h);
    percursoProfundidade(tree, updateMc, mcStruct);
    free(mcStruct);
    writeSvg(pSvg, tree);
}

void dCannon(FILE* pSvg, FILE* pTxt, SRbTree tree, Lista list, int i, char lado[3], double d){
    void* dStruct = newD(i, lado, d, tree, pTxt);
    setDList(dStruct, list);
    fprintf(pTxt, "\n[*] d %d %s %lf\n", i, lado, d);
    percursoProfundidade(tree, updateD, dStruct);
    free(dStruct);
    writeSvg(pSvg, tree);
    markD(pSvg, list);
}

double lr(FILE* pSvg, FILE* pTxt, SRbTree tree, Lista list, int i, char lado[3], double d, double w, double h, double lastPoints){
    void* lrStruct = newLr(i, lado, d, w, h, tree, pTxt);
    setLrList(lrStruct, list);
    setPoints(lrStruct, 0);
    fprintf(pTxt, "\n[*] lr %d %s %lf %lf %lf\n", i, lado, d, w, h);
    percursoProfundidade(tree, updateLr, lrStruct);
    double points = getPoints(lrStruct);
    fprintf(pTxt, "\tpontos da captura: M$%lf\n\tpontos acumulados: M$%lf\n", points, points + lastPoints);
    free(lrStruct);
    writeSvg(pSvg, tree);
    markLr(pSvg, list);
    return lastPoints + points;
}

void readQry(FILE* pTxt, SRbTree tree, AllPaths paths){
    char filename[150];
    strcpy(filename, getPathIn(paths));
    strcat(filename, "/");
    strcat(filename, getGivenQry(paths));
    strcat(filename, ".qry");
    FILE* pfileQry = fopen(filename, "r");
    if(!pfileQry) return;
    
    drawAxis(paths);
    FILE* pSvg;
    pSvg = appendSvg(paths);
    writeSvg(pSvg, tree);

    Lista dList = newList();
    Lista lrList = newList();

    char function[3];
    double points = 0;

    while(!feof(pfileQry)){
        fscanf(pfileQry, "%s ", function);
        if(strcmp(function, "e") == 0){
            double v;
            fscanf(pfileQry, "%lf\n", &v);
            e(pTxt, tree, v);
        }
        else if(strcmp(function, "mv") == 0){
            int id;
            double dx, dy;
            fscanf(pfileQry, "%d %lf %lf\n", &id, &dx, &dy);
            fclose(pSvg);
            drawAxis(paths);
            pSvg = appendSvg(paths);
            mv(pSvg, pTxt, tree, id, dx, dy);
        }
        else if(strcmp(function, "mc") == 0){
            double dx, dy, x, y, w, h;
            fscanf(pfileQry, "%lf %lf %lf %lf %lf %lf\n", &dx, &dy, &x, &y, &w, &h);
            fclose(pSvg);
            drawAxis(paths);
            pSvg = appendSvg(paths);
            mc(pSvg, pTxt, tree, dx, dy, x, y, w, h);
        }
        else if(strcmp(function, "lr") == 0){
            int i;
            double d, w, h;
            char lado[3];
            fscanf(pfileQry, "%d %s %lf %lf %lf\n", &i, lado, &d, &w, &h);
            fclose(pSvg);
            drawAxis(paths);
            pSvg = appendSvg(paths);
            points = lr(pSvg, pTxt, tree, lrList, i, lado, d, w, h, points);
        }
        else if(strcmp(function, "d") == 0){
            int i;
            double d;
            char lado[3];
            fscanf(pfileQry, "%d %s %lf\n", &i, lado, &d);
            fclose(pSvg);
            drawAxis(paths);
            pSvg = appendSvg(paths);
            dCannon(pSvg, pTxt, tree, dList, i, lado, d);
        }
    }

    freeList('d', dList);
    freeList('l', lrList);

    fclose(pfileQry);
    closeSvg(pSvg);
}