#include "be.h"

struct beArea{
    double x, y, w, h;
    struct beArea* next;
};

struct beArea* headArea = NULL;

void* newAreaList(){
    struct beArea* new = (struct beArea*)malloc(sizeof(struct beArea));
    return new;
}

void* newArea(void* areaList, double x, double y, double w, double h){
    struct beArea* new = (struct beArea*)malloc(sizeof(struct beArea));
    new->x = x;
    new->y = y;
    new->w = w;
    new->h = h;
    new->next = NULL;
    return new;
}

void insertArea(void* areaList, double x, double y, double w, double h){
    struct beArea* new = newArea(areaList, x, y, w, h);
    if(headArea == NULL){
        headArea = new;
        return;
    }
    new->next = headArea;
    headArea = new;
}

void freeArea(void* areaList){
    if(headArea == NULL){
        free(areaList);
        return;
    }
    void* nodeAux, *currentHead, *nextHead;
    do{
        currentHead = headArea;
        nodeAux = currentHead;
        nextHead = headArea->next;
        headArea = headArea->next;
        free(nodeAux);
    } while(nextHead != NULL);
    free(areaList);
}

double getAreaX(int position){
    struct beArea* aux = headArea;
    for(int i = 0; i < position; i++){
        aux = aux->next;
    }
    return aux->x;
}

double getAreaY(int position){
    struct beArea* aux = headArea;
    for(int i = 0; i < position; i++){
        aux = aux->next;
    }
    return aux->y;
}

double getAreaW(int position){
    struct beArea* aux = headArea;
    for(int i = 0; i < position; i++){
        aux = aux->next;
    }
    return aux->w;
}

double getAreaH(int position){
    struct beArea* aux = headArea;
    for(int i = 0; i < position; i++){
        aux = aux->next;
    }
    return aux->h;
}

void drawBeArea(FILE* svg){
    struct beArea* aux = headArea;
    if(aux == NULL){
        return;
    }
    int i = 0;
    double x, y, w, h;
    while(aux != NULL){
        x = getAreaX(i);
        y = getAreaY(i);
        w = getAreaW(i);
        h = getAreaH(i);
        fprintf(svg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill-opacity: 0; stroke:red; stroke-width:1; stroke-dasharray: 1 1\"/>", x, y, w, h);
        aux = aux->next;
        i++;
    }
}

void drawBe(FILE* svg, double x, double y){
    fprintf(svg,"\n\t<text x=\"%.2lf\" y=\"%.2lf\" style=\"font:7.5px sans-serif; stroke:red; stroke-width:0.5; fill:red; text-anchor:middle;\"> . </text>", x, y);
}

bool beCheckCircle(double circleX, double circleY, double circleR, double areaX, double areaY, double areaW, double areaH){
    double limitRight = areaX + areaW;
    double limitDown = areaY + areaH;
    if(circleX + circleR <= limitRight && circleY - circleR >= areaY && circleX - circleR >= areaX && circleY + circleR <= limitDown){
        return true;
    }
    return false;
}

bool beCheckRect(double rectX, double rectY, double rectW, double rectH, double areaX, double areaY, double areaW, double areaH){
    double limitX = areaX + areaW;
    double limitY = areaY + areaH;
    double centerX = rectX + rectW / 2;
    double centerY = rectY + rectH / 2;
    if(centerX + rectW / 2 <= limitX && centerY - rectH / 2 >= areaY && centerX - rectW / 2 >= areaX && centerY + rectH / 2 <= limitY){
        return true;
    }
    return false;
}

bool beCheckLine(double x1, double y1, double x2, double y2, double areaX, double areaY, double areaW, double areaH){
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
    return false;
}

bool beCheckText(double x, double y, double areaX, double areaY, double areaW, double areaH){
   double limitX = areaX + areaW;
   double limitY = areaY + areaH;
   if(x >= areaX && x <= limitX && y >= areaY && y <= limitY){
       return true;
   }
   return false;
}

void writeBe(FILE* txt, void* element, char type, bool activity){
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
        if(activity){
            fprintf(txt, "círculo %d\n\tâncora em (%lf, %lf)\n\traio: %lf\n\tborda: %s\n\tpreenchimento: %s\n\tnível de energia: %lf\n", id, x1, y1, r, colorBorder, colorFill, energy);
        }
        else{
            fprintf(txt, "círculo %d REMOVIDO\n\tâncora em (%lf, %lf)\n\traio: %lf\n\tborda: %s\n\tpreenchimento: %s\n\tnível de energia: %lf\n", id, x1, y1, r, colorBorder, colorFill, energy);
        }
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
        if(activity){
            fprintf(txt, "retângulo %d\n\tâncora em (%lf, %lf)\n\tlargura: %lf\n\taltura: %lf\n\tborda: %s\n\tpreenchimento: %s\n\tnível de energia: %lf\n", id, x1, y1, w, h, colorBorder, colorFill, energy);
        }
        else{
            fprintf(txt, "retângulo %d REMOVIDO\n\tâncora em (%lf, %lf)\n\tlargura: %lf\n\taltura: %lf\n\tborda: %s\n\tpreenchimento: %s\n\tnível de energia: %lf\n", id, x1, y1, w, h, colorBorder, colorFill, energy);
        }
    }
    else if(type == 'l'){
        id = getLineId(element);
        x1 = getLineX1(element);
        y1 = getLineY1(element);
        x2 = getLineX2(element);
        y2 = getLineY2(element);
        strcpy(colorBorder, getLineBorder(element));
        energy = getLineEnergy(element);
        if(activity){
            fprintf(txt, "linha %d\n\textremidades em (%lf, %lf) (%lf, %lf)\n\tcor: %s\n\tnível de energia: %lf\n", id, x1, y1, x2, y2, colorBorder, energy);
        }
        else{
            fprintf(txt, "linha %d REMOVIDA\n\textremidades em (%lf, %lf) (%lf, %lf)\n\tcor: %s\n\tnível de energia: %lf\n", id, x1, y1, x2, y2, colorBorder, energy);
        }
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
        if(activity){
            fprintf(txt, "texto %d\n\tâncora em (%lf, %lf)\n\tborda: %s\n\tpreenchimento: %s\n\tposição da âncora: %c\n\ttexto: %s\n\tnível de energia: %lf\n", id, x1, y1, colorBorder, colorFill, a, texto, energy);
        }
        else{
            fprintf(txt, "texto %d REMOVIDO\n\tâncora em (%lf, %lf)\n\tborda: %s\n\tpreenchimento: %s\n\tposição da âncora: %c\n\ttexto: %s\n\tnível de energia: %lf\n", id, x1, y1, colorBorder, colorFill, a, texto, energy);
        }
    }
}