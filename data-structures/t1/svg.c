#include "svg.h"
#include "geometry.h"

FILE* newSvg(char* pathOut, char* filenameGeo){
    char filename[150];
    strcpy(filename, pathOut);
    strcat(filename, "/");
    strcat(filename, filenameGeo);
    strcat(filename, ".svg");
    FILE* svg = fopen(filename, "w");
    if(svg == NULL){
        printf("\nErro: nao foi possivel abrir %s\n", filename);
        return NULL;
    }
    else{
        printf("\nArquivo %s aberto com sucesso\n", filename);
    }

    fprintf(svg, "<svg viewBox=\" 0 -10 1000 1000\" xmlns=\"http://www.w3.org/2000/svg\">");
    fprintf(svg, "\n\t<defs>");
    fprintf(svg, "\n\t\t<marker id=\"arrowhead\" makerWidth=\"3.5\" markerHeight=\"5\" refX=\"0\" refY=\"2.5\" orient=\"auto\">");
    fprintf(svg, "\n\t\t\t<polygon points=\"0 0, 2.5 2.5, 0 5\"/>");
    fprintf(svg, "\n\t\t</marker>");
    fprintf(svg, "\n\t</defs>");
    fprintf(svg, "\n\t<line x1=\"-0.5\" y1=\"0\" x2=\"1000\" y2=\"0\" style=\"stroke:black;stroke-width:1\" marker-end=\"url(#arrowhead)\"/>");
    fprintf(svg, "\n\t<line x1=\"0\" y1=\"0\" x2=\"0\" y2=\"950\" style=\"stroke:black; stroke-width:1\" marker-end=\"url(#arrowhead)\"/>");
    fprintf(svg, "\n\t<text x=\"1010\" y=\"0\" style=\"font:7.5px sans-serif; stroke:black; stroke-width:0.5; text-anchor:start\">x</text>");
    fprintf(svg, "\n\t<text x=\"0\" y=\"960\" style=\"font:7.5px sans-serif; stroke:black; stroke-width:0.5; text-anchor:middle\">y</text>");
    return svg;
}

void drawCircle(FILE* svg, int id, double x, double y, double r, char colorBorder[15], char colorFill[15]){
    fprintf(svg, "\n\t<circle id=\"%d\" cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2lf\" stroke=\"%s\" stroke-width=\"0.5\" fill=\"%s\"/>", id, x, y, r, colorBorder, colorFill);
    fprintf(svg, "\n\t<text x=\"%.2lf\" y=\"%.2lf\" style=\"font:5px sans-serif; stroke: black; stroke-width:0.25; text-anchor:middle\">%d</text>", x, y, id);
}

void drawRect(FILE* svg, int id, double x, double y, double w, double h, char colorBorder[15], char colorFill[15]){
    fprintf(svg, "\n\t<rect id=\"%d\" x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\" style=\"stroke:%s; stroke-width:0.5; fill:%s\"/>", id, x, y, w, h, colorBorder, colorFill);
    fprintf(svg, "\n\t<text x=\"%.2lf\" y=\"%.2lf\" style=\"font:5px sans-serif; stroke: black; stroke-width:0.25; text-anchor:middle\">%d</text>", x, y, id);
}

void drawLine(FILE* svg, int id, double x1, double y1, double x2, double y2, char color[15]){
    fprintf(svg, "\n\t<line id=\"%d\" x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:%s; stroke-width:0.5\"/>", id, x1, y1, x2, y2, color);
    fprintf(svg, "\n\t<text x=\"%.2lf\" y=\"%.2lf\" style=\"font:5px sans-serif; stroke: black; stroke-width:0.25; text-anchor:end\">%d</text>", x1, y1, id);
}

void drawText(FILE* svg, int id, double x, double y, char colorBorder[15], char colorFill[15], char a, char txt[30]){
    char anchor[10];
    if(a == 'i'){
        strcpy(anchor, "start");
    }
    else if(a == 'm'){
        strcpy(anchor, "middle");
    }
    else if(a == 'f'){
        strcpy(anchor, "end");
    }
    else if(!a){
        strcpy(anchor, "start");
    }
    fprintf(svg,"\n\t<text id=\"%d\" x=\"%.2lf\" y=\"%.2lf\" style=\"font:7.5px sans-serif; stroke:%s; stroke-width:0.5; fill:%s; text-anchor:%s;\">", id, x, y, colorBorder, colorFill, anchor);
    fprintf(svg, "\n\t\t%s", txt);
    fprintf(svg, "\n\t</text>");
    fprintf(svg, "\n\t<text x=\"%.2lf\" y=\"%.2lf\" style=\"font:5px sans-serif; stroke: black; stroke-width:0.25;\">%d</text>", x, y, id);
}

void closeSvg(FILE* svg){
    fprintf(svg, "\n</svg>");
    fclose(svg);
}

void writeSvg(FILE* svg, void* geometryList){
    int i = getGeoSize(geometryList);

    void* element;
    int visits, id;
    double x1, y1, x2, y2, r, w, h;
    char function, colorBorder[20], colorFill[20], a, txt[30];

    for(visits = 0; visits <= i; visits++){
        function = getCurrentType(visits);
        element = getCurrentElement(visits);
        if(function == 'c'){
            id = getCircleId(element);
            x1 = getCircleX(element);
            y1 = getCircleY(element);
            r = getCircleR(element);
            strcpy(colorBorder, getCircleBorder(element));
            strcpy(colorFill, getCircleFill(element));
            drawCircle(svg, id, x1, y1, r, colorBorder, colorFill);
        }
        else if(function == 'r'){
            id = getRectId(element);
            x1 = getRectX(element);
            y1 = getRectY(element);
            w = getRectW(element);
            h = getRectH(element);
            strcpy(colorBorder, getRectBorder(element));
            strcpy(colorFill, getRectFill(element));
            drawRect(svg, id, x1, y1, w, h, colorBorder, colorFill);
        }
        else if(function == 'l'){
            id = getLineId(element);
            x1 = getLineX1(element);
            y1 = getLineY1(element);
            x2 = getLineX2(element);
            y2 = getLineY2(element);
            strcpy(colorBorder, getLineBorder(element));
            drawLine(svg, id, x1, y1, x2, y2, colorBorder);
        }
        else if(function == 't'){
            id = getTxtId(element);
            x1 = getTxtX(element);
            y1 = getTxtY(element);
            strcpy(colorBorder, getTxtBorder(element));
            strcpy(colorFill, getTxtFill(element));
            a = getA(element);
            strcpy(txt, getTxt(element));
            drawText(svg, id, x1, y1, colorBorder, colorFill, a, txt);
        }
    }
    closeSvg(svg);
}