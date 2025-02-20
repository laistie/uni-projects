#include "libraries.h"
#include "argv.h"
#include "geo.h"
#include "paths.h"
#include "qry.h"
#include "svg.h"
#include "yxxtree.h"

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
    
    YxxTree tree = getGeoParameters(paths);

    FILE* pGeoSvg = newSvg(getPathOut(paths), getFileGeo(paths));
    writeSvg(pGeoSvg, tree);
    closeSvg(pGeoSvg);

    if(getCheckedQry(checkedPaths)){
        FILE* pTxt = newReport(paths);
        readQry(pTxt, tree, paths, checkedPaths);
        endReport(pTxt);    
    }

    freeTree(tree);
    freeCheckedPaths(checkedPaths);
    freePaths(paths);
}