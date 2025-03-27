#include "lr.h"

struct lr{
    int i;
    char lado[3];
    double d, x, y, w, h, energy, points;
    bool found;
    Lista list;
    SRbTree tree;
    FILE* pTxt;
};

void* newLr(int i, char lado[3], double d, double w, double h, SRbTree tree, FILE* pTxt){
    struct lr* new = (struct lr*)malloc(sizeof(struct lr));
    new->i = i;
    strcpy(new->lado, lado);
    new->d = d;
    new->w = w;
    new->h = h;
    new->found = false;
    new->tree = tree;
    new->pTxt = pTxt;
    return new;
}

void setCoordLr(void* lr, double x, double y){
    struct lr* lrAux = lr;
    lrAux->x = x;
    lrAux->y = y;
}

void setInitEnergy(void* lr, double energy){
    struct lr* lrAux = lr;
    lrAux->energy = energy;
}

void updateEnergy(void* lr){
    struct lr* lrAux = lr;
    lrAux->energy = lrAux->energy * 1.5;
}

void setLrList(void* lr, Lista list){
    struct lr* lrAux = lr;
    lrAux->list = list;
}

void setPoints(void* lr, double points){
    struct lr* lrAux = lr;
    lrAux->points = points; 
}

void updatePoints(void* lr, double points){
    struct lr* lrAux = lr;
    lrAux->points = lrAux->points + points;
}

double getPoints(void* lr){
    struct lr* lrAux = lr;
    return lrAux->points;
}

bool checkLrCircle(double circleX, double circleY, double circleR, double areaX, double areaY, double areaW, double areaH){
    double limitRight = areaX + areaW;
    double limitDown = areaY + areaH;
    if(circleX + circleR <= limitRight && circleY - circleR >= areaY && circleX - circleR >= areaX && circleY + circleR <= limitDown){
        return true;
    }
    return false;
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
    return false;
}

bool checkText(double x, double y, double areaX, double areaY, double areaW, double areaH){
   double limitX = areaX + areaW;
   double limitY = areaY + areaH;
   if(x >= areaX && x <= limitX && y >= areaY && y <= limitY){
       return true;
   }
   return false;
}

void checkLr(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux){
    struct lr* auxLrStruct = aux;
    if(getInfoType(i) == 'c'){ //PEIXE M$5,00
        double x1 = getCircleX(getInfoFromInfo(i));
        double y1 = getCircleY(getInfoFromInfo(i));
        double r = getCircleR(getInfoFromInfo(i));
        if(checkLrCircle(x1, y1, r, auxLrStruct->x, auxLrStruct->y, auxLrStruct->w, auxLrStruct->h)){
            int id = getCircleId(getInfoFromInfo(i));
            char colorBorder[20], colorFill[20];
            strcpy(colorBorder, getCircleBorder(getInfoFromInfo(i)));
            strcpy(colorFill, getCircleFill(getInfoFromInfo(i)));
            fprintf(auxLrStruct->pTxt, "\tpeixe %d capturado valor: M$5,00\n", id);
            updatePoints(auxLrStruct, 5);
            fprintf(auxLrStruct->pTxt, "\t\tx: %lf\n\t\ty: %lf\n\t\tr: %lf\n\t\tcb: %s\n\t\tcf: %s\n", x1, y1, r, colorBorder, colorFill);
            Info info = removeSRb(auxLrStruct->tree, x, y, &mbbX1, &mbbY1, &mbbX2, &mbbY2);
            freeInfo(info);
        }
    }
    else if(getInfoType(i) == 'l'){ //CAMARÃO M$1,00
        double x1 = getLineX1(getInfoFromInfo(i));
        double y1 = getLineY1(getInfoFromInfo(i));
        double x2 = getLineX2(getInfoFromInfo(i));
        double y2 = getLineY2(getInfoFromInfo(i));
        if(checkLine(x1, y1, x2, y2, auxLrStruct->x, auxLrStruct->y, auxLrStruct->w, auxLrStruct->h)){
            int id = getLineId(getInfoFromInfo(i));
            char colorBorder[20];
            strcpy(colorBorder, getLineBorder(getInfoFromInfo(i)));
            fprintf(auxLrStruct->pTxt, "\tcamarão %d capturado valor: M$1,00\n", id);
            updatePoints(auxLrStruct, 1);
            fprintf(auxLrStruct->pTxt, "\t\tx1: %lf\n\t\ty1: %lf\n\t\tx2: %lf\n\t\ty2: %lf\n\t\tcor: %s\n", x1, y1, x2, y2, colorBorder);
            Info info = removeSRb(auxLrStruct->tree, x, y, &mbbX1, &mbbY1, &mbbX2, &mbbY2);
            freeInfo(info);
        }
    }
    else if(getInfoType(i) == 't'){ // >-|-< LAGOSTA M$20,00, $ MOEDA +0.5e
        double x1 = getTxtX(getInfoFromInfo(i));
        double y1 = getTxtY(getInfoFromInfo(i));
        if(checkText(x1, y1, auxLrStruct->x, auxLrStruct->y, auxLrStruct->w, auxLrStruct->h)){
            int id = getTxtId(getInfoFromInfo(i));
            char colorBorder[20], colorFill[20], a, txt[100];
            strcpy(colorBorder, getTxtBorder(getInfoFromInfo(i)));
            strcpy(colorFill, getTxtFill(getInfoFromInfo(i)));
            a = getA(getInfoFromInfo(i));
            strcpy(txt, getTxt(getInfoFromInfo(i)));
            if(strcmp(txt, ">-|-<") == 0){
                fprintf(auxLrStruct->pTxt, "\tlagosta %d capturada valor: M$20,00\n", id);
                updatePoints(auxLrStruct, 20);
            }
            else if(strcmp(txt, "$") == 0){
                fprintf(auxLrStruct->pTxt, "\tmoeda %d capturada\n", id);
                updateEnergy(auxLrStruct);
            }
            else{
                fprintf(auxLrStruct->pTxt, "\tdetrito %d capturado\n", id);
            }
            fprintf(auxLrStruct->pTxt, "\t\tx: %lf\n\t\ty: %lf\n\t\tcb: %s\n\t\tcp: %s\n\t\ta: %c\n\t\ttexto: %s\n", x1, y1, colorBorder, colorFill, a, txt);
            Info info = removeSRb(auxLrStruct->tree, x, y, &mbbX1, &mbbY1, &mbbX2, &mbbY2);
            freeInfo(info);
        }
    }
}

void updateLr(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux){
    struct lr* auxLrStruct = aux;
    if(!auxLrStruct->found){
        if(getInfoType(i) == 'r'){
            int id = getRectId(getInfoFromInfo(i));
            if(id == auxLrStruct->i){
                auxLrStruct->found = true;
                double energy = getRectEnergy(getInfoFromInfo(i));
                setInitEnergy(auxLrStruct, energy);
                double cast = (auxLrStruct->w * auxLrStruct->h / 25) * (auxLrStruct->d / 5);
                if(energy < cast){
                    fprintf(auxLrStruct->pTxt, "\tnau %d sem energia suficiente para lançar rede\n", id);
                    return;
                }
                fprintf(auxLrStruct->pTxt, "\tenergia da nau %d antes do lançamento: %lf\n", id, getRectEnergy(getInfoFromInfo(i)));
                setRectEnergy(getInfoFromInfo(i), energy - cast);
                if(strcmp(auxLrStruct->lado, "PP") == 0){ // POPA, MENOR COORDENADA Y
                    double cannon = getRectX(getInfoFromInfo(i)) + (getRectW(getInfoFromInfo(i)) / 2);
                    setCoordLr(auxLrStruct, cannon, getRectY(getInfoFromInfo(i)) - auxLrStruct->d);
                    percursoProfundidade(auxLrStruct->tree, checkLr, auxLrStruct);
                    insertList(auxLrStruct->list, 'l', auxLrStruct->x, auxLrStruct->y, auxLrStruct->w, auxLrStruct->h);
                }
                else if(strcmp(auxLrStruct->lado, "PR") == 0){ // PROA, MAIOR COORDENADA Y
                    double cannon = getRectX(getInfoFromInfo(i)) + (getRectW(getInfoFromInfo(i)) / 2);
                    setCoordLr(auxLrStruct, cannon, getRectY(getInfoFromInfo(i)) + getRectH(getInfoFromInfo) + auxLrStruct->d);
                    percursoProfundidade(auxLrStruct->tree, checkLr, auxLrStruct);
                    insertList(auxLrStruct->list, 'l', auxLrStruct->x, auxLrStruct->y, auxLrStruct->w, auxLrStruct->h);
                }
                else if(strcmp(auxLrStruct->lado, "EB") == 0){ // ESTIBORDO, MENOR COORDENADA X
                    double cannon = getRectY(getInfoFromInfo(i)) + (getRectH(getInfoFromInfo(i)) / 2);
                    setCoordLr(auxLrStruct, getRectX(getInfoFromInfo(i)) - auxLrStruct->d , cannon);
                    percursoProfundidade(auxLrStruct->tree, checkLr, auxLrStruct);
                    insertList(auxLrStruct->list, 'l', auxLrStruct->x, auxLrStruct->y, auxLrStruct->w, auxLrStruct->h);
                }
                else if(strcmp(auxLrStruct->lado, "BB") == 0){ // BOMBORDO, MAIOR COORDENADA X
                    double cannon =  getRectY(getInfoFromInfo(i)) + (getRectH(getInfoFromInfo(i)) / 2);
                    setCoordLr(auxLrStruct, getRectX(getInfoFromInfo(i)) + getRectW(getInfoFromInfo(i)) + auxLrStruct->d, cannon);
                    percursoProfundidade(auxLrStruct->tree, checkLr, auxLrStruct);
                    insertList(auxLrStruct->list, 'l', auxLrStruct->x, auxLrStruct->y, auxLrStruct->w, auxLrStruct->h);
                }
                if(auxLrStruct->energy != energy){
                    setRectEnergy(getInfoFromInfo(i), auxLrStruct->energy);
                }
                fprintf(auxLrStruct->pTxt, "\tenergia restante da nau %d: %lf\n", id, getRectEnergy(getInfoFromInfo(i)));
            }
        }
    }
}