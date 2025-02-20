#include "inp.h"

struct inp{
    int id;
    Queue queue;
    FILE* pTxt;
};

void* newInp(int id, Queue queue, FILE* pTxt){
    struct inp* new = (struct inp*)malloc(sizeof(struct inp));
    new->id = id;
    new->queue = queue;
    new->pTxt = pTxt;
    return new;
}

void fInp(Info i, double x, double y, void* aux){
    struct inp* auxStructInp = aux;
    int id;
    if(getInfoType(i) == 'c'){
        id = getCircleId(getInfoFromInfo(i));
    }
    else if(getInfoType(i) == 'r'){
        id = getRectId(getInfoFromInfo(i));
    }
    else if(getInfoType(i) == 'l'){
        id = getLineId(getInfoFromInfo(i));
        double x1 = getLineX1(getInfoFromInfo(i));
        double y1 = getLineY1(getInfoFromInfo(i));
        double x2 = getLineX2(getInfoFromInfo(i));
        double y2 = getLineY2(getInfoFromInfo(i));
        if(x1 == x2){
            if(y1 < y2){
                y = y1;
                x = x1;
            }
            else{
                y = y2;
                x = x2;
            }
        }
        else if(x1 < x2){
            x = x2;
            y = y2;
        }
        else{
            x = x1;
            y = y1;
        }
    }
    else if(getInfoType(i) == 't'){
        id = getTxtId(getInfoFromInfo(i));
    }
    if(id == auxStructInp->id){
        fprintf(auxStructInp->pTxt, "coordenada inserida: (%lf, %lf)\n", x, y);
        if(getInfoType(i) == 'c'){
            double r = getCircleR(getInfoFromInfo(i));
            char colorBorder[20], colorFill[20];
            strcpy(colorBorder, getCircleBorder(getInfoFromInfo(i)));
            strcpy(colorFill, getCircleFill(getInfoFromInfo(i)));
            fprintf(auxStructInp->pTxt, "círculo\n\tx: %lf \n\ty: %lf \n\tr: %lf \n\tcb: %s \n\tcf: %s\n", x, y, r, colorBorder, colorFill);
        }
        else if(getInfoType(i) == 'r'){
            double w = getRectW(getInfoFromInfo(i));
            double h = getRectH(getInfoFromInfo(i));
            char colorBorder[20], colorFill[20];
            strcpy(colorBorder, getRectBorder(getInfoFromInfo(i)));
            strcpy(colorFill, getRectFill(getInfoFromInfo(i)));
            fprintf(auxStructInp->pTxt, "retângulo\n\tx: %lf \n\ty: %lf \n\tw: %lf \n\th: %lf \n\tcb: %s \n\tcf: %s\n", x, y, w, h, colorBorder, colorFill);
        }
        else if(getInfoType(i) == 'l'){
            char color[20];
            strcpy(color, getLineBorder(getInfoFromInfo(i)));
            double x1 = getLineX1(getInfoFromInfo(i));
            double y1 = getLineY1(getInfoFromInfo(i));
            double x2 = getLineX2(getInfoFromInfo(i));
            double y2 = getLineY2(getInfoFromInfo(i));
            fprintf(auxStructInp->pTxt, "linha\n\tx1: %lf \n\ty1: %lf \n\tx2: %lf \n\ty2: %lf \n\tcor: %s\n", x1, y1, x2, y2, color);
        }
        else if(getInfoType(i) == 't'){
            char colorBorder[20], colorFill[20], a, text[30];
            strcpy(colorBorder, getTxtBorder(getInfoFromInfo(i)));
            strcpy(colorFill, getTxtFill(getInfoFromInfo(i)));
            a = getA(getInfoFromInfo(i));
            strcpy(text, getTxt(getInfoFromInfo(i)));
            fprintf(auxStructInp->pTxt, "texto\n\tx: %lf\n\ty: %lf\n\tcb: %s\n\tcp: %s\n\ta: %c\n\ttxt: %s\n", x, y, colorBorder, colorFill, a, text);
        }
        enqueue(auxStructInp->queue, x, y);
    }
}