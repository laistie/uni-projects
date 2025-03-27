#include "dot.h"

void newGraph(char* pathOut, char* file){
    char filename[150];
    strcpy(filename, pathOut);
    strcat(filename, "/");
    strcat(filename, file);
    strcat(filename, ".dot");
    FILE* pfileDot = fopen(filename, "w");
    if(!pfileDot) return;
    fprintf(pfileDot, "digraph G{\n");
    fprintf(pfileDot, "\tnode [margin=0 fontcolor=white fontsize=12 width=0.5 shape=circle style=filled]\n");
    fprintf(pfileDot, "\tedge [fontcolor=grey fontsize=10]\n");
    fprintf(pfileDot, "\tnil [fillcolor=black fixedsize=shape label=\"nil\" width=2]\n");
    fclose(pfileDot);
}

void printNode(FILE* pDot, char* color, int id, double x, double y){
    fprintf(pDot, "\t%d [fillcolor=%s fixedsize=shape label=\"id:%d x=%lf y=%lf\" width=3]\n", id, color, id, x, y);
}

void printLink(FILE* pDot, int id, int parentId){
    fprintf(pDot, "\t%d -> %d\n", parentId, id);
}

void printNLink(FILE* pDot, char* nil, int parentId){
    fprintf(pDot, "\t%d -> %s\n", parentId, nil);
}

void endGraph(char* filename){
    FILE* pfile = fopen(filename, "a");
    fprintf(pfile, "}");
    fclose(pfile);
}