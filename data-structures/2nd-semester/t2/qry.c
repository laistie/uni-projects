#include "qry.h"

FILE* newReport(void* paths){
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".txt");
    FILE* pfileTxt = fopen(filename, "w+");
    if(pfileTxt == NULL){
        return NULL;
    }
    fprintf(pfileTxt, "RELATÓRIO DAS FUNÇÕES UTILIZADAS NO ARQUIVO .QRY\n");
    return pfileTxt;
}

void endReport(FILE* txt){
    fprintf(txt, "\nCONSIDERAÇÕES FINAIS: enlouqueci.");
    fclose(txt);
}

void drawAxis(void* paths){
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".svg");
    FILE* pfileSvg = fopen(filename, "w");
    if(pfileSvg == NULL){
        printf("\nErro: nao foi possivel abrir %s\n", filename);
        return;
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
    fclose(pfileSvg);
}

void drawGeo(FILE* svg, void* tpList, void* trList, void* tree){
    transverseTree(svg, tree);
    mark(svg, tpList);
    markTr(svg, trList);
}

FILE* updateSvg(void* tpList, void* trList, void* paths, FILE* svg, void* tree){
    fclose(svg);
    drawAxis(paths);
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".svg");
    FILE* pfileSvg = fopen(filename, "a");
    if(pfileSvg == NULL){
        return NULL;
    }
    drawGeo(pfileSvg, tpList, trList, tree);
    return pfileSvg;
}

FILE* tp(void* tpList, void* trList, void* paths, FILE* svg, FILE* txt, void* tree, double x, double y){
    int n = transverseTreeTp(svg, txt, getRoot(tree), 0, x, y, 0);
    insertTorpedo(tpList, 'p', x, y, n);
    svg = updateSvg(tpList, trList, paths, svg, tree);
    if(n == 0){
        writeNotTp(txt, x, y);
    }
    return svg;
}

FILE* tr(void* tpList, void* trList, void* paths, FILE* svg, FILE* txt, void* tree, double x, double y, double dx, double dy, int id){
    int n = transverseTreeTr(svg, txt, tree, getRoot(tree), getRoot(tree), 0, x, y, id, 0);
    insertTorpedo(trList, 'r', x, y, n);
    svg = updateSvg(tpList, trList, paths, svg, tree);
    if(n == 0){
        writeNotTr(txt, x, y);
    }
    return svg;
}

FILE* be(void* tpList, void* trList, void* areaList, void* paths, FILE* svg, FILE* txt, void* tree, double x, double y, double w, double h, double v){
    fprintf(txt, "\n[*] be %lf %lf %lf %lf\nnível de agressividade: %lf\n", x, y, w, h, v);
    transverseTreeBe(svg, txt, getRoot(tree), 0, x, y, w, h, v);
    svg = updateSvg(tpList, trList, paths, svg, tree);
    insertArea(areaList, x, y, w, h);
    drawBeArea(svg);
    return svg;
}

double sumPoints(void* tree){
    double totalPoints = 0;
    totalPoints = transverseTreePoints(getRoot(tree), 0, totalPoints);
    return totalPoints;
}

double sumMaxPoints(void* tree, char* qryFunction){
    double maxPoints = 0;
    maxPoints = transverseTreeMaxPoints(getRoot(tree), 0, maxPoints, qryFunction);
    return maxPoints;
}

void endSvg(FILE* pfileSvg){
    fprintf(pfileSvg, "\n</svg>");
    fclose(pfileSvg);
}

void readQry(FILE* txt, void* tree, void* paths, void* checkedPaths){
    char filename[150];
    strcpy(filename, getPathIn(paths));
    strcat(filename, "/");
    strcat(filename, getGivenQry(paths));
    strcat(filename, ".qry");
    FILE* pfileQry = fopen(filename, "r");
    if(pfileQry == NULL){
        return;
    }

    drawAxis(paths);
    char svg[150];
    strcpy(svg, getPathOut(paths));
    strcat(svg, "/");
    strcat(svg, getCatGeoQry(paths));
    strcat(svg, ".svg");
    FILE* pfileSvg = fopen(svg, "a");
    if(pfileSvg == NULL){
        return;
    }
    void* tpList = newTorpedoList();
    void* trList = newTorpedoList();
    
    drawGeo(pfileSvg, tpList, trList, tree);

    char function[3];
    double aggressivity = 0;
    int aggressions = 0;
    void* areaList = newAreaList();
    bool torpedo = false;

    while(!feof(pfileQry)){
        fscanf(pfileQry, "%s ", function);
        if(strcmp(function, "na") == 0){
            fscanf(pfileQry, "%lf\n", &aggressivity);
            fprintf(txt, "\n[*] na %lf\n", aggressivity);
        }
        else if(strcmp(function, "tp") == 0){
            double x, y;
            fscanf(pfileQry, "%lf %lf\n", &x, &y);
            pfileSvg = tp(tpList, trList, paths, pfileSvg, txt, tree, x, y);
            aggressions++;
            torpedo = true;
        }
        else if(strcmp(function, "tr") == 0){
            int id;
            double x, y, dx, dy;
            fscanf(pfileQry, "%lf %lf %lf %lf %d\n", &x, &y, &dx, &dy, &id);
            pfileSvg = tr(tpList, trList, paths, pfileSvg, txt, tree, x, y, dx, dy, id);
            aggressions++;
            torpedo = true;
        }
        else if(strcmp(function, "be") == 0){
            double x, y, w, h;
            fscanf(pfileQry, "%lf %lf %lf %lf\n", &x, &y, &w, &h);
            pfileSvg = be(tpList, trList, areaList, paths, pfileSvg, txt, tree, x, y, w, h, aggressivity);
            aggressions++;
        }
    }

    char qryFunction[3];
    if(torpedo){
        strcpy(qryFunction, "tp");
    }
    else{
        strcpy(qryFunction, "be");
    }

    double totalPoints = sumPoints(tree);
    double maxPoints = sumMaxPoints(tree, qryFunction);
    double prop1 = totalPoints / maxPoints;
    double prop2 = totalPoints / aggressions;
    if(strcmp(qryFunction, "be") == 0){
        fprintf(txt, "\nPONTUAÇÃO\n\tpontuação total: %lf\n\tproporção entre pontos obtidos e a pontuação máxima: %lf / %lf = %lf\n\t\tOBS: no cálculo da pontuação máxima considerou-se apenas a possibilidade de inativação de todas as figuras do banco de dados pela ausência de torpedos no arquivo de consultas .qry\n\tproporção entre pontos obtidos e o número de agressões: %lf / %d = %lf\n", totalPoints, totalPoints, maxPoints, prop1, totalPoints, aggressions, prop2);
    }
    else{
        fprintf(txt, "\nPONTUAÇÃO\n\tpontuação total: %lf\n\tproporção entre pontos obtidos e a pontuação máxima: %lf / %lf = %lf\n\t\tOBS: no cálculo da pontuação máxima considerou-se a destruição de todas as figuras do banco de dados\n\tproporção entre pontos obtidos e o número de agressões: %lf / %d = %lf\n", totalPoints, totalPoints, maxPoints, prop1, totalPoints, aggressions, prop2);
    }
    
    freeTorpedo('p', tpList);
    freeTorpedo('r', trList);
    freeArea(areaList);

    fclose(pfileQry);
    endSvg(pfileSvg);
}