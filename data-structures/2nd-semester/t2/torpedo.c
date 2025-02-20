#include "torpedo.h"

struct torpedo{ //LISTA DUPLAMENTE ENCADEADA COM TORPEDOS
    double x, y;
    int n;
    struct torpedo* next;
};

struct torpedo* headTp = NULL;

struct torpedo* headTr = NULL;

void* newTorpedoList(){
    struct torpedo* new = (struct torpedo*)malloc(sizeof(struct torpedo));
    return new;
}

void* newTorpedo(void* torpedoList, double x, double y, int n){
    struct torpedo* new = (struct torpedo*)malloc(sizeof(struct torpedo));
    new->x = x;
    new->y = y;
    new->n = n;
    new->next = NULL;
    return new;
}

void insertTorpedo(void* torpedoList, char type, double x, double y, int n){
    struct torpedo* new = newTorpedo(torpedoList, x, y, n);
    if(type == 'p'){
        if(headTp == NULL){
            headTp = new;
            return;
        }
        new->next = headTp;
        headTp = new;
    }
    else if(type == 'r'){
        if(headTr == NULL){
            headTr = new;
            return;
        }
        new->next = headTr;
        headTr = new;
    }
}

double getTpX(char type, int position){
    struct torpedo* aux;
    if(type == 'p'){
        aux = headTp;
    }
    else if(type == 'r'){
        aux = headTr;
    }
    for(int i = 0; i < position; i++){
        aux = aux->next;
    }
    return aux->x;
}

double getTpY(char type, int position){
    struct torpedo* aux;
    if(type == 'p'){
        aux = headTp;
    }
    else if(type == 'r'){
        aux = headTr;
    }
    for(int i = 0; i < position; i++){
        aux = aux->next;
    }
    return aux->y;
}

int getTpN(char type, int position){
    struct torpedo* aux;
    if(type == 'p'){
        aux = headTp;
    }
    else if(type == 'r'){
        aux = headTr;
    }
    for(int i = 0; i < position; i++){
        aux = aux->next;
    }
    return aux->n;
}

void freeTorpedo(char type, void* torpedoList){
    if(type == 'p'){
        if(headTp == NULL){
            free(torpedoList);
            return;
        }
        void* nodeAux, *currentHead, *nextHead;
        do{
            currentHead = headTp;
            nodeAux = currentHead;
            nextHead = headTp->next;
            headTp = headTp->next;
            free(nodeAux);
        } while(nextHead != NULL);
    }
    else if(type == 'r'){
        if(headTr == NULL){
            free(torpedoList);
            return;
        }
        void* nodeAux, *currentHead, *nextHead;
        do{
            currentHead = headTr;
            nodeAux = currentHead;
            nextHead = headTr->next;
            headTr = headTr->next;
            free(nodeAux);
        } while(nextHead != NULL);
    }
    free(torpedoList);
}

bool checkCircle(void* element, double x, double y){
    double circleX = getCircleX(element);
    double circleY = getCircleY(element);
    double circleR = getCircleR(element);
    double powX = (x - circleX) * (x - circleX);
    double powY = (y - circleY) * (y - circleY);
    if(powX + powY < circleR * circleR){
        return true;
    }
    return false;
}

bool checkRect(void* element, double x, double y){
    double limitX = getRectX(element) + getRectW(element);
    double limitY = getRectY(element) + getRectH(element);
    if(x > getRectX(element) && x < limitX && y > getRectY(element) && y < limitY){
        return true;
    }
    return false;
}

bool checkLine(void* element, double x, double y){
    double greaterX, lesserX, greaterY, lesserY;
    if(getLineX1(element) > getLineX2(element)){
        greaterX = getLineX1(element);
        lesserX = getLineX2(element);
    }
    else{
        greaterX = getLineX2(element);
        lesserX =  getLineX1(element);
    }
    if(getLineY1(element) > getLineY2(element)){
        greaterY = getLineY1(element);
        lesserY = getLineY2(element);
    }
    else{
        greaterY = getLineY2(element);
        lesserY = getLineY1(element);
    }
    double m = (greaterY - lesserY) / (greaterX - lesserX);
    double b = getLineY1(element) - (m * getLineX1(element));
    if(y == m * x + b){
        return true;
    }
    return false;
}

bool checkTxt(void* element, double x, double y){
    if(getTxtX(element) == x && getTxtY(element) == y){
        return true;
    }
    return false;
}

void mark(FILE* pfileSvg, void* tpList){
    struct torpedo* aux = headTp;
    if(aux == NULL){
        return;
    }
    int i = 0;
    double x, y;
    int n;
    while(aux != NULL){
        x = getTpX('p', i);
        y = getTpY('p', i);
        n = getTpN('p', i);
        if(n == 0){
            fprintf(pfileSvg,"\n\t<text x=\"%.2lf\" y=\"%.2lf\" style=\"font:7.5px sans-serif; stroke:gray; stroke-width:0.5; fill:gray; text-anchor:middle;\"> * </text>", x, y);
        }
        else if(n == 1){
            fprintf(pfileSvg,"\n\t<text x=\"%.2lf\" y=\"%.2lf\" style=\"font:7.5px sans-serif; stroke:red; stroke-width:0.5; fill: red; text-anchor:middle;\"> * </text>", x, y);
        }
        else{
            fprintf(pfileSvg,"\n\t<text x=\"%.2lf\" y=\"%.2lf\" style=\"font:7.5px sans-serif; stroke:red; stroke-width:0.5; fill: red; text-anchor:middle;\"> %d* </text>", x, y, n);
        }
        aux = aux->next;
        i++;
    }
}

void markTr(FILE* pfileSvg, void* trList){
    struct torpedo* aux = headTr;
    if(aux == NULL){
        return;
    }
    int i = 0;
    double x, y;
    int n;
    while(aux != NULL){
        x = getTpX('r', i);
        y = getTpY('r', i);
        n = getTpN('r', i);
        if(n == 0){
            fprintf(pfileSvg,"\n\t<text x=\"%.2lf\" y=\"%.2lf\" style=\"font:7.5px sans-serif; stroke:gray; stroke-width:0.5; fill:gray; text-anchor:middle;\"> @ </text>", x, y);
        }
        else if(n == 1){
            fprintf(pfileSvg,"\n\t<text x=\"%.2lf\" y=\"%.2lf\" style=\"font:7.5px sans-serif; stroke:red; stroke-width:0.5; fill: red; text-anchor:middle;\"> @ </text>", x, y);
        }
        else{
            fprintf(pfileSvg,"\n\t<text x=\"%.2lf\" y=\"%.2lf\" style=\"font:7.5px sans-serif; stroke:red; stroke-width:0.5; fill: red; text-anchor:middle;\"> %d@ </text>", x, y, n);
        }
        aux = aux->next;
        i++;
    }
}

void writeTp(FILE* txt, void* element, char type){
    int id;
    double x1, y1, x2, y2, r, w, h, energy;
    char colorBorder[20], colorFill[20], a, texto[30];
    if(type == 'c'){
        id = getCircleId(element);
        x1 = getCircleX(element);
        y1 = getCircleY(element);
        r = getCircleR(element);
        strcpy(colorBorder, getCircleBorder(element));
        strcpy(colorFill, getCircleFill(element));
        energy = getCircleEnergy(element);
        fprintf(txt, "círculo %d\n\tâncora em (%lf, %lf)\n\traio: %lf\n\tborda: %s\n\tpreenchimento: %s\n\tnível de energia: %lf\n", id, x1, y1, r, colorBorder, colorFill, energy);
    }
    else if(type == 'r'){
        id = getRectId(element);
        x1 = getRectX(element);
        y1 = getRectY(element);
        w = getRectW(element);
        h = getRectH(element);
        strcpy(colorBorder, getRectBorder(element));
        strcpy(colorFill, getRectFill(element));
        energy = getRectEnergy(element);
        fprintf(txt, "retângulo %d\n\tâncora em (%lf, %lf)\n\tlargura: %lf\n\taltura: %lf\n\tborda: %s\n\tpreenchimento: %s\n\tnível de energia: %lf\n", id, x1, y1, w, h, colorBorder, colorFill, energy);
    }
    else if(type == 'l'){
        id = getLineId(element);
        x1 = getLineX1(element);
        y1 = getLineY1(element);
        x2 = getLineX2(element);
        y2 = getLineY2(element);
        strcpy(colorBorder, getLineBorder(element));
        energy = getLineEnergy(element);
        fprintf(txt, "linha %d\n\textremidades em (%lf, %lf) (%lf, %lf)\n\tcor: %s\n\tnível de energia: %lf\n", id, x1, y1, x2, y2, colorBorder, energy);
    }
    else if(type == 't'){
        id = getTxtId(element);
        x1 = getTxtX(element);
        y1 = getTxtY(element);
        strcpy(colorBorder, getTxtBorder(element));
        strcpy(colorFill, getTxtFill(element));
        a = getA(element);
        strcpy(texto, getTxt(element));
        energy = getTxtEnergy(element);
        fprintf(txt, "texto %d\n\tâncora em (%lf, %lf)\n\tborda: %s\n\tpreenchimento: %s\n\tposição da âncora: %c\n\ttexto: %s\n\tnível de energia: %lf\n", id, x1, y1, colorBorder, colorFill, a, texto, energy);
    }
}

void writeNotTp(FILE* txt, double x, double y){
    fprintf(txt, "\n[*] tp %lf %lf\n\tÁGUA\n", x, y);
}

void writeTr(FILE* txt, void* element, char type, double dx, double dy, int start, int adder){
    int id;
    double x1, y1, x2, y2, r, w, h, energy;
    char colorBorder[20], colorFill[20], a, texto[30];
    if(type == 'c'){
        id = getCircleId(element);
        x1 = getCircleX(element);
        y1 = getCircleY(element);
        r = getCircleR(element);
        strcpy(colorBorder, getCircleBorder(element));
        strcpy(colorFill, getCircleFill(element));
        energy = getCircleEnergy(element);
        fprintf(txt, "círculo %d\n\tâncora em (%lf, %lf)\n\traio: %lf\n\tborda: %s\n\tpreenchimento: %s\n\tnível de energia: %lf\n", id, x1, y1, r, colorBorder, colorFill, energy);
        fprintf(txt, "círculo clone %d\n\tâncora em (%lf, %lf)\n\traio: %lf\n\tborda: %s\n\tpreenchimento: %s\n\tnível de energia: %lf\n", start + adder, x1 + dx, y1 + dy, r, colorFill, colorBorder, energy);
    }
    else if(type == 'r'){
        id = getRectId(element);
        x1 = getRectX(element);
        y1 = getRectY(element);
        w = getRectW(element);
        h = getRectH(element);
        strcpy(colorBorder, getRectBorder(element));
        strcpy(colorFill, getRectFill(element));
        energy = getRectEnergy(element);
        fprintf(txt, "retângulo %d\n\tâncora em (%lf, %lf)\n\tlargura: %lf\n\taltura: %lf\n\tborda: %s\n\tpreenchimento: %s\n\tnível de energia: %lf\n", id, x1, y1, w, h, colorBorder, colorFill, energy);
        fprintf(txt, "retângulo clone %d\n\tâncora em (%lf, %lf)\n\tlargura: %lf\n\taltura: %lf\n\tborda: %s\n\tpreenchimento: %s\n\tnível de energia: %lf\n", start + adder, x1 + dx, y1 + dy, w, h, colorFill, colorBorder, energy);
    }
    else if(type == 'l'){
        id = getLineId(element);
        x1 = getLineX1(element);
        y1 = getLineY1(element);
        x2 = getLineX2(element);
        y2 = getLineY2(element);
        strcpy(colorBorder, getLineBorder(element));
        energy = getLineEnergy(element);
        fprintf(txt, "linha %d\n\textremidades em (%lf, %lf) (%lf, %lf)\n\tcor: %s\n\tnível de energia: %lf\n", id, x1, y1, x2, y2, colorBorder, energy);
        fprintf(txt, "linha clone %d\n\textremidades em (%lf, %lf) (%lf, %lf)\n\tcor: %s\n\tnível de energia: %lf\n", start + adder, x1 + dx, y1 + dy, x2 + dx, y2 + dy, colorBorder, energy);
    }
    else if(type == 't'){
        id = getTxtId(element);
        x1 = getTxtX(element);
        y1 = getTxtY(element);
        strcpy(colorBorder, getTxtBorder(element));
        strcpy(colorFill, getTxtFill(element));
        a = getA(element);
        strcpy(texto, getTxt(element));
        energy = getTxtEnergy(element);
        fprintf(txt, "texto %d\n\tâncora em (%lf, %lf)\n\tborda: %s\n\tpreenchimento: %s\n\tposição da âncora: %c\n\ttexto: %s\n\tnível de energia: %lf\n", id, x1, y1, colorBorder, colorFill, a, texto, energy);
        fprintf(txt, "texto clone %d\n\tâncora em (%lf, %lf)\n\tborda: %s\n\tpreenchimento: %s\n\tposição da âncora: %c\n\ttexto: %s\n\tnível de energia: %lf\n", start + adder, x1 + dx, y1 + dy, colorFill, colorBorder, a, texto, energy);
    }
    start++;
}

void writeNotTr(FILE* txt, double x, double y){
    fprintf(txt, "\n[*] tr %lf %lf\n\tÁGUA\n", x, y);
}