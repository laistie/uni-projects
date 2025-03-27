#include "svg.h"

FILE* newSvg(char* pathOut, char* filenameGeo){
    char filename[150];
    strcpy(filename, pathOut);
    strcat(filename, "/");
    strcat(filename, filenameGeo);
    strcat(filename, ".svg");
    FILE* pfileSvg = fopen(filename, "w");
    if (pfileSvg == NULL)
    {
        return NULL;
    }
    fprintf(pfileSvg, "<svg viewBox=\" 0 -10 1500 1500\" xmlns=\"http://www.w3.org/2000/svg\">");
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

void drawCircle(FILE* svg, int id, double x, double y, double r, char colorBorder[20], char colorFill[20]){
    fprintf(svg, "\n\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" style=\"stroke:%s; stroke-width:0.5; fill:%s; fill-opacity: .25\"/>", id, x, y, r, colorBorder, colorFill);
}

void drawRect(FILE* svg, int id, double x, double y, double w, double h, char colorBorder[20], char colorFill[20]){
    fprintf(svg, "\n\t<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"stroke:%s; stroke-width:0.5; fill:%s; fill-opacity: .25\"/>", id, x, y, w, h, colorBorder, colorFill);
}

void drawLine(FILE* svg, int id, double x1, double y1, double x2, double y2, char color[20]){
    fprintf(svg, "\n\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:%s; stroke-width:0.5\"/>", id, x1, y1, x2, y2, color);
}

void drawText(FILE* svg, int id, double x, double y, char colorBorder[20], char colorFill[20], char a, char txt[30]){
    char anchor[10];
    if (a == 'i') strcpy(anchor, "start");
    else if (a == 'm') strcpy(anchor, "middle");
    else if (a == 'f') strcpy(anchor, "end");
    else if (!a) strcpy(anchor, "start");
    fprintf(svg, "\n\t<text id=\"%d\" x=\"%lf\" y=\"%lf\" style=\"font:7.5px sans-serif; stroke:%s; stroke-width:0.5; fill:%s; text-anchor:%s;\">", id, x, y, colorBorder, colorFill, anchor);
    fprintf(svg, "\n\t\t<![CDATA[%s]]>", txt);
    fprintf(svg, "\n\t</text>");
}

void closeSvg(FILE* svg){
    fprintf(svg, "\n</svg>");
    fclose(svg);
}

void printTSvg(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux){
    FILE *pSvg = aux;
    if(getInfoType(i) == 'c'){
        int id = getCircleId(getInfoFromInfo(i));
        double x1 = getCircleX(getInfoFromInfo(i));
        double y1 = getCircleY(getInfoFromInfo(i));
        double r = getCircleR(getInfoFromInfo(i));
        char colorBorder[20], colorFill[20];
        strcpy(colorBorder, getCircleBorder(getInfoFromInfo(i)));
        strcpy(colorFill, getCircleFill(getInfoFromInfo(i)));
        drawCircle(pSvg, id, x1, y1, r, colorBorder, colorFill);
    }
    else if(getInfoType(i) == 'r'){
        int id = getRectId(getInfoFromInfo(i));
        double x1 = getRectX(getInfoFromInfo(i));
        double y1 = getRectY(getInfoFromInfo(i));
        double w = getRectW(getInfoFromInfo(i));
        double h = getRectH(getInfoFromInfo(i));
        char colorBorder[20], colorFill[20];
        strcpy(colorBorder, getRectBorder(getInfoFromInfo(i)));
        strcpy(colorFill, getRectFill(getInfoFromInfo(i)));
        drawRect(pSvg, id, x1, y1, w, h, colorBorder, colorFill);
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
        double x1 = getTxtX(getInfoFromInfo(i));
        double y1 = getTxtY(getInfoFromInfo(i));
        char colorBorder[20], colorFill[20], a, txt[30];
        strcpy(colorBorder, getTxtBorder(getInfoFromInfo(i)));
        strcpy(colorFill, getTxtFill(getInfoFromInfo(i)));
        a = getA(getInfoFromInfo(i));
        strcpy(txt, getTxt(getInfoFromInfo(i)));
        drawText(pSvg, id, x1, y1, colorBorder, colorFill, a, txt);
    }
}

void writeSvg(FILE *svg, SRbTree tree){
    percursoProfundidade(tree, printTSvg, svg);
}