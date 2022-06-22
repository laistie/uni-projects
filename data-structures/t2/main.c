#include "libraries.h"
#include "argv.h"
#include "geo.h"
#include "paths.h"
#include "svg.h"
#include "tree.h"
#include "qry.h"

int main(int argc, char* argv[]){
    void* paths = newPaths();
    void* checkedPaths = newCheckedPaths();

    setArgv(argc, argv, paths, checkedPaths);

    if(checkCheckedPaths(checkedPaths) == false){
        printf("Erro: parametro(s) obrigatório(s) faltando\n");
        freeCheckedPaths(checkedPaths);
        freePaths(paths);
        return 0;
    }

    void* tree = getGeoParameters(getPathIn(paths), getGivenGeo(paths));

    FILE* svg = newSvg(getPathOut(paths), getFileGeo(paths));
    writeSvg(svg, tree);

    FILE* txt = newReport(paths);

    readQry(txt, tree, paths, checkedPaths);
    endReport(txt);

    freeTree(tree);
    freeCheckedPaths(checkedPaths);
    freePaths(paths);
}