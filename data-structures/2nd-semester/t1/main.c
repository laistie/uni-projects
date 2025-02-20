#include "libraries.h"
#include "argv.h"
#include "paths.h"
#include "geo.h"
#include "svg.h"
#include "qry.h"

int main(int argc, char* argv[]){

    void* paths = newPaths();
    void* checkedPaths = newCheckedPaths();

    setArgv(argc, argv, paths, checkedPaths);

    if(checkCheckedPaths(checkedPaths) == false){
        printf("Erro: parametro(s) obrigatorio(s) faltando\n");
        freeCheckedPaths(checkedPaths);
        freePaths(paths);
        return 0;
    }

    printPaths(paths);
    
    void* geoList = getGeoParameters(getPathIn(paths), getGivenGeo(paths));

    FILE* svg = newSvg(getPathOut(paths), getFileGeo(paths));
    writeSvg(svg, geoList);

    FILE* txt = newReport(paths);
    void* polQueue = newPolQueue(MAX_QUEUE);
    readQry(txt, polQueue, paths, checkedPaths, geoList);
    endReport(txt);

    freeCheckedPaths(checkedPaths);
    freePaths(paths);
    freeGeoList(geoList);
    freePolQueue(polQueue);

    return 0;
}