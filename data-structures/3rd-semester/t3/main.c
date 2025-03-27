#include "libraries.h"
#include "argv.h"
#include "dot.h"
#include "geo.h"
#include "paths.h"
#include "qry.h"
#include "svg.h"
#include "SRbTree.h"

int main(int argc, char* argv[]){
    void* paths = newPaths();
    void* checkedPaths = newCheckedPaths();

    setArgv(argc, argv, paths, checkedPaths);

    if(!checkCheckedPaths(checkedPaths)){
        printf("Erro: parametro(s) obrigatório(s) faltando\n");
        freeCheckedPaths(checkedPaths);
        freePaths(paths);
        return 0;
    }

    SRbTree tree = getGeoParameters(paths);

    FILE* pGeoSvg = newSvg(getPathOut(paths), getFileGeo(paths));
    writeSvg(pGeoSvg, tree);
    closeSvg(pGeoSvg);
    
    newGraph(getPathOut(paths), getFileGeo(paths));
    char dotGeo[150];
    strcpy(dotGeo, getPathOut(paths));
    strcat(dotGeo, "/");
    strcat(dotGeo, getFileGeo(paths));
    strcat(dotGeo, ".dot");
    printSRb(tree, dotGeo);
    endGraph(dotGeo);

    if(getCheckedQry(checkedPaths)){
        FILE* pTxt = newReport(paths);
        readQry(pTxt, tree, paths);
        endReport(pTxt);    
        newGraph(getPathOut(paths), getCatGeoQry(paths));
        char dotQry[150];
        strcpy(dotQry, getPathOut(paths));
        strcat(dotQry, "/");
        strcat(dotQry, getCatGeoQry(paths));
        strcat(dotQry, ".dot");
        printSRb(tree, dotQry);
        endGraph(dotQry);    
    }

    killSRb(tree);
    freeCheckedPaths(checkedPaths);
    freePaths(paths);
}