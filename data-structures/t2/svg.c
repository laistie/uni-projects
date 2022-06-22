#include "svg.h"

FILE* newSvg(char* pathOut, char* filenameGeo){
    char filename[150];
    strcpy(filename, pathOut);
    strcat(filename, "/");
    strcat(filename, filenameGeo);
    strcat(filename, ".svg");
    FILE* pfileSvg = fopen(filename, "w");
    if(pfileSvg == NULL){
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

void drawCircle(FILE* svg, int id, double x, double y, double r, char colorBorder[15], char colorFill[15]){
    fprintf(svg, "\n\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" style=\"stroke:%s; stroke-width:0.5; fill:%s; fill-opacity: .25\"/>", id, x, y, r, colorBorder, colorFill);
}

void drawRect(FILE* svg, int id, double x, double y, double w, double h, char colorBorder[15], char colorFill[15]){
    fprintf(svg, "\n\t<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"stroke:%s; stroke-width:0.5; fill:%s; fill-opacity: .25\"/>", id, x, y, w, h, colorBorder, colorFill);
}

void drawLine(FILE* svg, int id, double x1, double y1, double x2, double y2, char color[15]){
    fprintf(svg, "\n\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:%s; stroke-width:0.5\"/>", id, x1, y1, x2, y2, color);
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
    fprintf(svg,"\n\t<text id=\"%d\" x=\"%lf\" y=\"%lf\" style=\"font:7.5px sans-serif; stroke:%s; stroke-width:0.5; fill:%s; text-anchor:%s;\">", id, x, y, colorBorder, colorFill, anchor);
    fprintf(svg, "\n\t\t%s", txt);
    fprintf(svg, "\n\t</text>");
}

void closeSvg(FILE* svg){
    fprintf(svg, "\n</svg>");
    fclose(svg);
}

void writeSvg(FILE* svg, void* tree){
    transverseTree(svg, tree);
    closeSvg(svg);
}