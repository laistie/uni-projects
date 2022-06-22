#include "qry.h"

FILE* newReport(void* paths){
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".txt");
    FILE* pfileTxt = fopen(filename, "w+");
    if(pfileTxt == NULL){
        printf("\nErro: nao foi possivel abrir %s\n", filename);
        return NULL;
    }
    else{
        printf("\nArquivo %s aberto com sucesso\n", filename);
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
    else{
        printf("\nArquivo %s aberto com sucesso\n", filename);
    }
    fprintf(pfileSvg, "<svg viewBox=\" 0 -10 1000 1000\" xmlns=\"http://www.w3.org/2000/svg\">");
    fprintf(pfileSvg, "\n\t<defs>");
    fprintf(pfileSvg, "\n\t\t<marker id=\"arrowhead\" makerWidth=\"3.5\" markerHeight=\"5\" refX=\"0\" refY=\"2.5\" orient=\"auto\">");
    fprintf(pfileSvg, "\n\t\t\t<polygon points=\"0 0, 2.5 2.5, 0 5\"/>");
    fprintf(pfileSvg, "\n\t\t</marker>");
    fprintf(pfileSvg, "\n\t</defs>");
    fprintf(pfileSvg, "\n\t<line x1=\"-0.5\" y1=\"0\" x2=\"1000\" y2=\"0\" style=\"stroke:black;stroke-width:1\" marker-end=\"url(#arrowhead)\"/>");
    fprintf(pfileSvg, "\n\t<line x1=\"0\" y1=\"0\" x2=\"0\" y2=\"950\" style=\"stroke:black; stroke-width:1\" marker-end=\"url(#arrowhead)\"/>");
    fprintf(pfileSvg, "\n\t<text x=\"1010\" y=\"0\" style=\"font:7.5px sans-serif; stroke:black; stroke-width:0.5; text-anchor:start\">x</text>");
    fprintf(pfileSvg, "\n\t<text x=\"0\" y=\"960\" style=\"font:7.5px sans-serif; stroke:black; stroke-width:0.5; text-anchor:middle\">y</text>");
    fclose(pfileSvg);
}

void writeInp(FILE* txt, void* polQueue, char type, int id, void* element){
    double x = getCoordX(getCurrentCoordinates(polQueue));
    double y = getCoordY(getCurrentCoordinates(polQueue));
    char colorBorder[20], colorFill[20];
    if(type == 'c'){
        double r = getCircleR(element);
        strcpy(colorBorder, getCircleBorder(element));
        strcpy(colorFill, getCircleFill(element));
        fprintf(txt, "\n[*] inp %d\ncírculo\nâncora em (%lf, %lf)\nraio: %lf\nborda: %s\npreenchimento: %s\n", id, x, y, r, colorBorder, colorFill);
    }
    else if(type == 'r'){
        double w = getRectW(element);
        double h = getRectH(element);
        strcpy(colorBorder, getRectBorder(element));
        strcpy(colorFill, getRectFill(element));
        fprintf(txt, "\n[*] inp %d\nretângulo\nâncora em (%lf, %lf)\nlargura: %lf\naltura: %lf\nborda: %s\npreenchimento: %s\n", id, x, y, w, h, colorBorder, colorFill);
    }
    else if(type == 'l'){
        double x1 = getLineX1(element);
        double y1 = getLineY1(element);
        double x2 = getLineX2(element);
        double y2 = getLineY2(element);
        strcpy(colorBorder, getLineBorder(element));
        fprintf(txt, "\n[*] inp %d\ntexto\nextremidades em (%lf, %lf) (%lf, %lf)\ncor: %s\n", id, x1, y1, x2, y2, colorBorder);
    }
    else if(type == 't'){
        strcpy(colorBorder, getTxtBorder(element));
        strcpy(colorFill, getTxtFill(element));
        char a = getA(element);
        char texto[100];
        strcpy(texto, getTxt(element));
        fprintf(txt, "\n[*] inp %d\ntexto\nâncora em (%lf, %lf)\nborda: %s\npreenchimento: %s\nposição da âncora: %c\ntexto: %s\n", id, x, y, colorBorder, colorFill, a, texto);
    }
}

void inp(FILE* txt, void* queue, int id){
    int position = 0;
    char type;
    void* element;
    int idAux;
    do{
        type = getCurrentType(position);
        element = getCurrentElement(position);
        if(type == 'c'){
            idAux = getCircleId(element);
        }
        else if(type == 'r'){
            idAux = getRectId(element);
        }
        else if(type == 'l'){
            idAux = getLineId(element);
        }
        else if(type == 't'){
            idAux = getTxtId(element);
        }
        position++;
    } while(idAux != id);
    enqueue(queue, type, id, position);
    writeInp(txt, queue, type, id, element);
}

void writeRmp(FILE* txt, void* polQueue, void* coordinates){
    double x = getCoordX(coordinates);
    double y = getCoordY(coordinates);
    fprintf(txt, "\n[*] rmp\ncoordenada removida: (%lf, %lf)\n", x, y);
}

void rmp(FILE* txt, void* queue){
    void* coordinates = getFirstCoordinates(queue);
    writeRmp(txt, queue, coordinates);
    dequeue(queue, coordinates);
}

void writeClp(FILE* txt, bool removeValue){
    if(removeValue == true){
        fprintf(txt, "\n[*] clp\ntodas as coordenadas foram removidas\n");
    }
    else{
        fprintf(txt, "\n[*] clp\nerro ao remover coordenadas, a fila está vazia\n");
    }
}

void clp(FILE* txt, void* queue){
    writeClp(txt, freeAllCoordinates(queue));
}

void pol(FILE* txt, void* queue, void* paths, int start, double d, double e, char colorBorder[15], char colorFill[15]){
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".svg");
    FILE* pfileSvg = fopen(filename, "a");
    if(pfileSvg == NULL){
        printf("\nErro: nao foi possivel abrir %s\n", filename);
        return;
    }
    else{
        printf("\nArquivo %s aberto com sucesso\n", filename);
    }
    drawPolygon(pfileSvg, queue, start, d, e, colorBorder, colorFill);
    fclose(pfileSvg);
}

void drawGeo(FILE* svg, void* geometryList){
    int i = getGeoSize(geometryList);
    void* element;
    int visits, id;
    double x1, y1, x2, y2, r, w, h;
    char function, colorBorder[20], colorFill[20], a, txt[100];

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
}

void writeSel(FILE* txt, double x, double y, double w, double h){
    fprintf(txt, "\n[*] sel %lf %lf %lf %lf\n", x, y, w, h);
}

bool checkCircle(double circleX, double circleY, double circleR, double areaX, double areaY, double areaW, double areaH){
    double limitRight = areaX + areaW;
    double limitDown = areaY + areaH;
    if(circleX + circleR <= limitRight && circleY - circleR >= areaY && circleX - circleR >= areaX && circleY + circleR <= limitDown){
        return true;
    }
    else{
        return false;
    }
}

bool checkRect(double rectX, double rectY, double rectW, double rectH, double areaX, double areaY, double areaW, double areaH){
    double limitX = areaX + areaW;
    double limitY = areaY + areaH;
    double centerX = rectX + rectW / 2;
    double centerY = rectY + rectH / 2;
    if(centerX + rectW / 2 <= limitX && centerY - rectH / 2 >= areaY && centerX - rectW / 2 >= areaX && centerY + rectH / 2 <= limitY){
        return true;
    }
    else{
        return false;
    }
}

bool checkLine(double x1, double y1, double x2, double y2, double areaX, double areaY, double areaW, double areaH){
    double greaterX, lesserX, greaterY, lesserY;
    double limitX = areaX + areaW;
    double limitY = areaY + areaH;
    if(x1 > x2){
        greaterX = x1;
        lesserX = x2;
    }
    else{
        greaterX = x2;
        lesserX = x1;
    }
    if(y1 > y2){
        greaterY = y1;
        lesserY = y2;
    }
    else{
        greaterY = y2;
        lesserY = y1;
    }
    if(greaterX <= limitX && lesserX >= areaX && greaterY <= limitY && lesserY >= areaY){
        return true;
    }
    else{
        return false;
    }
}

bool checkText(double x, double y, double areaX, double areaY, double areaW, double areaH){
   double limitX = areaX + areaW;
   double limitY = areaY + areaH;
   if(x >= areaX && x <= limitX && y >= areaY && y <= limitY){
       return true;
   }
   return false;
}

void drawSelected(FILE* svg, double x, double y){
    fprintf(svg, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" stroke=\"red\" stroke-width=\"1\" fill-opacity=\"0\"/>", x, y);
}

int checkSel(FILE* txt, FILE* svg, void* selectedList, void* geometryList, double x, double y, double w, double h){
    int n = 0;

    int i = getGeoSize(geometryList);
    void* element;
    int visits, id;
    double x1, y1, x2, y2, r, elementW, elementH;
    char function;

    for(visits = 0; visits <= i; visits++){
        function = getCurrentType(visits);
        element = getCurrentElement(visits);
        if(function == 'c'){
            x1 = getCircleX(element);
            y1 = getCircleY(element);
            r = getCircleR(element);
            if(checkCircle(x1, y1, r, x, y, w, h) == true){
                drawSelected(svg, x1, y1);
                id = getCircleId(element);
                fprintf(txt, "%d: círculo\n", id);
                insertSel(selectedList, id, function);
                n++;
            }
        }
        else if(function == 'r'){
            x1 = getRectX(element);
            y1 = getRectY(element);
            elementW = getRectW(element);
            elementH = getRectH(element);
            if(checkRect(x1, y1, elementW, elementH, x, y, w, h) == true){
                drawSelected(svg, x1, y1);
                id = getRectId(element);
                fprintf(txt, "%d: retângulo\n", id);
                insertSel(selectedList, id, function);
                n++;
            }
        }
        else if(function == 'l'){
            x1 = getLineX1(element);
            y1 = getLineY1(element);
            x2 = getLineX2(element);
            y2 = getLineY2(element);
            if(checkLine(x1, y1, x2, y2, x, y, w, h) == true){
                drawSelected(svg, x1, y1);
                id = getLineId(element);
                fprintf(txt, "%d: linha\n", id);
                insertSel(selectedList, id, function);
                n++;
            }
        }
        else if(function == 't'){
            x1 = getTxtX(element);
            y1 = getTxtY(element);
            if(checkText(x1, y1, x, y, w, h) == true){
                drawSelected(svg, x1, y1);
                id = getTxtId(element);
                fprintf(txt, "%d: texto\n", id);
                insertSel(selectedList, id, function);
                n++;
            }
        }
    }
    return n;
}

int sel(void* paths, FILE* txt, void* selectedList, int selections, void* geometryList, double x, double y, double w, double h){
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".svg");
    FILE* selSvg = fopen(filename, "a");
    if(selSvg == NULL){
        printf("\nErro: nao foi possivel abrir %s\n", filename);
        return 0;
    }
    else{
        printf("\nArquivo %s aberto com sucesso\n", filename);
    }
    writeSel(txt, x, y, w, h);
    if(selections == 0){
        drawGeo(selSvg, geometryList);
    }
    fprintf(selSvg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill-opacity: 0; stroke:red; stroke-width:1; stroke-dasharray: 1 1\"/>", x, y, w, h);
    int n = checkSel(txt, selSvg, selectedList, geometryList, x, y, w, h);
    fclose(selSvg);
    return n;
}

void writeSelPlus(FILE* txt, double x, double y, double w, double h){
    fprintf(txt, "\n[*] sel+ %lf %lf %lf %lf\n", x, y, w, h);
}

int selPlus(void* paths, FILE* txt, void* selectedList, void* geometryList, double x, double y, double w, double h, int n){
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".svg");
    FILE* selSvg = fopen(filename, "a");
    if(selSvg == NULL){
        printf("\nErro: nao foi possivel abrir %s\n", filename);
        return 0;
    }
    else{
        printf("\nArquivo %s aberto com sucesso\n", filename);
    }
    fprintf(selSvg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill-opacity: 0; stroke:red; stroke-width:1; stroke-dasharray: 1 1\"/>", x, y, w, h);
    writeSelPlus(txt, x, y, w, h);
    int nAll = n + checkSel(txt, selSvg, selectedList, geometryList, x, y, w, h);
    fprintf(txt, "figuras anteriormente selecionadas: %d\ntotal de figuras selecionadas: %d\n", n, nAll);
    fclose(selSvg); 
    return nAll;
}

void writeDels(FILE* txt){
    fprintf(txt, "\n[*] dels\n");
}   

void dels(void* paths, FILE* txt, void* selectedList, void* geometryList){
    drawAxis(paths);
    writeDels(txt);

    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".svg");
    FILE* selSvg = fopen(filename, "a");
    if(selSvg == NULL){
        printf("\nErro: nao foi possivel abrir %s\n", filename);
        return;
    }
    else{
        printf("\nArquivo %s aberto com sucesso\n", filename);
    }

    int i = getGeoSize(geometryList);
    void* element;
    int id;
    double x1, y1, x2, y2, r, w, h;
    char function, colorBorder[20], colorFill[20], a, text[100];

    for(int visits = 0; visits <= i; visits++){
        function = getCurrentType(visits);
        element = getCurrentElement(visits);
        if(function == 'c'){
            id = getCircleId(element);
            x1 = getCircleX(element);
            y1 = getCircleY(element);
            r = getCircleR(element);
            strcpy(colorBorder, getCircleBorder(element));
            strcpy(colorFill, getCircleFill(element));
            if(checkSelected(selectedList, function, id) == false){
                drawCircle(selSvg, id, x1, y1, r, colorBorder, colorFill);
            }
            else{
                fprintf(txt, "%d: círculo\n\tx: %lf \n\ty: %lf \n\tr: %lf \n\tcb: %s \n\tcf: %s\n", id, x1, y1, r, colorBorder, colorFill);
            }
        }
        else if(function == 'r'){
            id = getRectId(element);
            x1 = getRectX(element);
            y1 = getRectY(element);
            w = getRectW(element);
            h = getRectH(element);
            strcpy(colorBorder, getRectBorder(element));
            strcpy(colorFill, getRectFill(element));
            if(checkSelected(selectedList, function, id) == false){
                drawRect(selSvg, id, x1, y1, w, h, colorBorder, colorFill);
            }
            else{
                fprintf(txt, "%d: retângulo\n\tx: %lf \n\ty: %lf \n\tw: %lf \n\th: %lf \n\tcb: %s \n\tcf: %s\n", id, x1, y1, w, h, colorBorder, colorFill);
            }
        }
        else if(function == 'l'){
            id = getLineId(element);
            x1 = getLineX1(element);
            y1 = getLineY1(element);
            x2 = getLineX2(element);
            y2 = getLineY2(element);
            strcpy(colorBorder, getLineBorder(element));
            if(checkSelected(selectedList, function, id) == false){
                drawLine(selSvg, id, x1, y1, x2, y2, colorBorder);
            }
            else{
                fprintf(txt, "%d: linha\n\tx1: %lf \n\ty1: %lf \n\tx2: %lf \n\ty2: %lf \n\tcolor: %s\n", id, x1, y1, x2, y2, colorBorder);
            }
        }
        else if(function == 't'){
            id = getTxtId(element);
            x1 = getTxtX(element);
            y1 = getTxtY(element);
            strcpy(colorBorder, getTxtBorder(element));
            strcpy(colorFill, getTxtFill(element));
            a = getA(element);
            strcpy(text, getTxt(element));
            if(checkSelected(selectedList, function, id) == false){   
                drawText(selSvg, id, x1, y1, colorBorder, colorFill, a, text);
            }
            else{
                fprintf(txt, "%d: texto\n\tx: %lf\n\ty: %lf\n\tcb: %s\n\tcp: %s\n\ta: %c\n\ttxt: %s\n", id, x1, y1, colorBorder, colorFill, a, text);
            }
        }
    }
    fclose(selSvg); 
}

void dps(void* paths, void* selectedList, void* geometryList, int i, double dx, double dy, char colorBorder[20], char colorFill[20]){
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".svg");
    FILE* selSvg = fopen(filename, "a");
    if(selSvg == NULL){
        printf("\nErro: nao foi possivel abrir %s\n", filename);
        return;
    }
    else{
        printf("\nArquivo %s aberto com sucesso\n", filename);
    }

    int selSize = getSelSize(selectedList);
    int idAux, visitsAux, geoId;
    double x1, y1, x2, y2, r, w, h;
    char typeAux, function, a, text[100];
    void* element, *elementInserted;

    for(int visits = 0; visits < selSize; visits++){
        idAux = getSelId(selectedList, visits);
        typeAux = getSelType(selectedList, visits);
        visitsAux = -1;
        do{
            visitsAux++;
            function = getCurrentType(visitsAux);
            element = getCurrentElement(visitsAux);
            if(function == 'c'){
                geoId = getCircleId(element);
            }
            else if(function == 'r'){
                geoId = getRectId(element);
            }
            else if(function == 'l'){
                geoId = getLineId(element);
            }
            else if(function == 't'){
                geoId = getTxtId(element);
            }
        }while(geoId != idAux || function != typeAux);

        if(typeAux == 'c'){
            x1 = getCircleX(element) + dx;
            y1 = getCircleY(element) + dy;
            r = getCircleR(element);
            elementInserted = newCircle(i, x1, y1, r, colorBorder, colorFill);
            insertGeo(geometryList, typeAux, elementInserted);
            drawCircle(selSvg, i, x1, y1, r, colorBorder, colorFill);
        }
        else if(typeAux == 'r'){
            x1 = getRectX(element) + dx;
            y1 = getRectY(element) + dy;
            w = getRectW(element);
            h = getRectH(element);
            elementInserted = newRect(i, x1, y1, w, h, colorBorder, colorFill);
            insertGeo(geometryList, typeAux, elementInserted);
            drawRect(selSvg, i, x1, y1, w, h, colorBorder, colorFill);
        }
        else if(typeAux == 'l'){
            x1 = getLineX1(element) + dx;
            y1 = getLineY1(element) + dy;
            x2 = getLineX2(element) + dx;
            y2 = getLineY2(element) + dy;
            elementInserted = newLine(i, x1, y1, x2, y2, colorBorder);
            insertGeo(geometryList, typeAux, elementInserted);
            drawLine(selSvg, i, x1, y1, x2, y2, colorBorder);
        }
        else if(typeAux == 't'){
            x1 = getTxtX(element) + dx;
            y1 = getTxtY(element) + dy;
            a = getA(element);
            strcpy(text, getTxt(element));
            elementInserted = newTxt(i, x1, y1, colorBorder, colorFill, a, text);
            insertGeo(geometryList, typeAux, elementInserted);
            drawText(selSvg, i, x1, y1, colorBorder, colorFill, a, text);
        }
        i++;
    }
    fclose(selSvg);
}

void ups(void* paths, void* selectedList, void* geometryList, char cb[20], char cp[20], double dx, double dy, int n){
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".svg");
    FILE* selSvg = fopen(filename, "a");
    if(selSvg == NULL){
        printf("\nErro: nao foi possivel abrir %s\n", filename);
        return;
    }
    else{
        printf("\nArquivo %s aberto com sucesso\n", filename);
    }

    int absN = n;
    if(n < 0){
        absN = -1 * n;
    }

    int idAux = getLastSel(selectedList);
    char typeAux = getLastType(selectedList);
    int geoId, id;
    double x1, y1, x2, y2, r, w, h;
    char function, colorBorder[20], colorFill[20], a, txt[100];
    int visitsAux = -1;
    void* element;

    do{
        visitsAux++;
        function = getCurrentType(visitsAux);
        element = getCurrentElement(visitsAux);
        if(function == 'c'){
            geoId = getCircleId(element);
        }
        else if(function == 'r'){
            geoId = getRectId(element);
        }
        else if(function == 'l'){
            geoId = getLineId(element);
        }
        else if(function == 't'){
            geoId = getTxtId(element);
        }
    }while(geoId != idAux || function != typeAux);
    if(n > 0){
        element = getNextElement(visitsAux);
        visitsAux++;
    }
    else{
        element = getPrevElement(visitsAux);
        visitsAux--;
    }

    drawAxis(paths);
    int i = 1;
    for(int visits = 0; visits < absN; visits++){
        if(function == 'c'){
            setCircleX(element, getCircleX(element) + i * dx);
            setCircleY(element, getCircleY(element) + i * dy);
            setCircleBorder(element, cb);
            setCircleFill(element, cp);
        }
        else if(function == 'r'){
            setRectX(element, getRectX(element) + i * dx);
            setRectY(element, getRectY(element) + i * dy);
            setRectBorder(element, cb);
            setRectFill(element, cp);
        }
        else if(function == 'l'){
            setLineX1(element, getLineX1(element) + i * dx);
            setLineY1(element, getLineY1(element) + i * dy);
            setLineX2(element, getLineX2(element) + i * dx);
            setLineY2(element, getLineY2(element) + i * dy);
            setLineColor(element, cb);
        }
        else if(function == 't'){
            setTxtX(element, getTxtX(element) + i * dx);
            setTxtY(element, getTxtY(element) + i * dy);
            setTxtBorder(element, cb);
            setTxtFill(element, cp);
        }
        if(n > 0){
            element = getNextElement(visitsAux);
            visitsAux++;
            rmvFirstSel(selectedList);
        }
        else{
            element = getPrevElement(visitsAux);
            visitsAux--;
            rmvLastSel(selectedList);
        }
        function = getElementType(element);
        i++;
    }

    i = getGeoSize(geometryList);
    for(int visits = 0; visits <= i; visits++){
        function = getCurrentType(visits);
        element = getCurrentElement(visits);
        if(function == 'c'){
            id = getCircleId(element);
            x1 = getCircleX(element);
            y1 = getCircleY(element);
            r = getCircleR(element);
            strcpy(colorBorder, getCircleBorder(element));
            strcpy(colorFill, getCircleFill(element));
            drawCircle(selSvg, id, x1, y1, r, colorBorder, colorFill);
        }
        else if(function == 'r'){
            id = getRectId(element);
            x1 = getRectX(element);
            y1 = getRectY(element);
            w = getRectW(element);
            h = getRectH(element);
            strcpy(colorBorder, getRectBorder(element));
            strcpy(colorFill, getRectFill(element));
            drawRect(selSvg, id, x1, y1, w, h, colorBorder, colorFill);
        }
        else if(function == 'l'){
            id = getLineId(element);
            x1 = getLineX1(element);
            y1 = getLineY1(element);
            x2 = getLineX2(element);
            y2 = getLineY2(element);
            strcpy(colorBorder, getLineBorder(element));
            drawLine(selSvg, id, x1, y1, x2, y2, colorBorder);
        }
        else if(function == 't'){
            id = getTxtId(element);
            x1 = getTxtX(element);
            y1 = getTxtY(element);
            strcpy(colorBorder, getTxtBorder(element));
            strcpy(colorFill, getTxtFill(element));
            a = getA(element);
            strcpy(txt, getTxt(element));
            drawText(selSvg, id, x1, y1, colorBorder, colorFill, a, txt);
        }
    }
    fclose(selSvg);
}

void endQry(void* paths){
    char filename[150];
    strcpy(filename, getPathOut(paths));
    strcat(filename, "/");
    strcat(filename, getCatGeoQry(paths));
    strcat(filename, ".svg");
    FILE* qrySvg = fopen(filename, "a");
    if(qrySvg == NULL){
        printf("\nErro: nao foi possivel abrir %s\n", filename);
        return;
    }
    else{
        printf("\nArquivo %s aberto com sucesso\n", filename);
    }
    fprintf(qrySvg, "\n</svg>");
    fclose(qrySvg);
}

void readQry(FILE* txt, void* queue, void* paths, void* checkedPaths, void* geometryList){
    char filename[150];
    strcpy(filename, getPathIn(paths));
    strcat(filename, "/");
    strcat(filename, getGivenQry(paths));
    strcat(filename, ".qry");
    FILE* pfileQry = fopen(filename, "r");
    if(pfileQry == NULL){
        printf("\nErro: nao foi possivel abrir %s\n", filename);
        return;
    }
    else{
        printf("\nArquivo %s aberto com sucesso\n", filename);
    }

    drawAxis(paths);
    char svg[150];
    strcpy(svg, getPathOut(paths));
    strcat(svg, "/");
    strcat(svg, getCatGeoQry(paths));
    strcat(svg, ".svg");
    FILE* pfileSvg = fopen(svg, "a");
    if(pfileSvg == NULL){
        printf("\nErro: nao foi possivel abrir %s\n", filename);
        return;
    }
    else{
        printf("\nArquivo %s aberto com sucesso\n", filename);
    }
    drawGeo(pfileSvg, geometryList);
    fclose(pfileSvg);

    void* selectedList = newSelList();
    int selections = 0, nSel = 0;
    char function[5];
    while(!feof(pfileQry)){
        fscanf(pfileQry, "%s ", function);
        if(strcmp(function, "inp") == 0){
            int id;
            fscanf(pfileQry, "%d", &id);
            inp(txt, queue, id);
        }
        else if(strcmp(function, "rmp") == 0){
            rmp(txt, queue);
        }
        else if(strcmp(function, "clp") == 0){
            clp(txt, queue);
        }
        else if(strcmp(function, "pol") == 0){
            int start;
            double d, e;
            char colorBorder[20], colorFill[20];
            fscanf(pfileQry, "%d %lf %lf %s %s", &start, &d, &e, colorBorder, colorFill);
            pol(txt, queue, paths, start, d, e, colorBorder, colorFill);
        }
        else if(strcmp(function, "sel") == 0){
            selections++;
            double x, y, w, h;
            fscanf(pfileQry, "%lf %lf %lf %lf", &x, &y, &w, &h);
            if(selections > 0){
                rmvSelAll();
            }
            nSel = sel(paths, txt, selectedList, selections, geometryList, x, y, w, h);
        }
        else if(strcmp(function, "sel+") == 0){
            double x, y, w, h;
            fscanf(pfileQry, "%lf %lf %lf %lf", &x, &y, &w, &h);
            nSel = selPlus(paths, txt, selectedList, geometryList, x, y, w, h, nSel);
        }
        else if(strcmp(function, "dels") == 0){
            dels(paths, txt, selectedList, geometryList);
        }
        else if(strcmp(function, "dps") == 0){
            int i;
            double dx, dy;
            char colorBorder[20], colorFill[20];
            fscanf(pfileQry, "%d %lf %lf %s %s", &i, &dx, &dy, colorBorder, colorFill);
            dps(paths, selectedList, geometryList, i, dx, dy, colorBorder, colorFill);
        }
        else if(strcmp(function, "ups") == 0){
            char colorBorder[20], colorFill[20];
            double dx, dy;
            int n;
            fscanf(pfileQry, "%s %s %lf %lf %d", colorBorder, colorFill, &dx, &dy, &n);
            ups(paths, selectedList, geometryList, colorBorder, colorFill, dx, dy, n);
        }
    }
    fclose(pfileQry);
    endQry(paths);
    freeSelList(selectedList);
}