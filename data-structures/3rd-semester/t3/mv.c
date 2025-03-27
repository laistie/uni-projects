#include "mv.h"

struct mv{
    SRbTree tree;
    int id;
    double dx, dy;
    FILE* pTxt;
    bool moved;
};

void* newMv(SRbTree tree, int id, double dx, double dy, FILE* pTxt){
    struct mv* new = (struct mv*)malloc(sizeof(struct mv));
    new->tree = tree;
    new->id = id;
    new->dx = dx;
    new->dy = dy;
    new->pTxt = pTxt;
    new->moved = false;
    return new;
}

void updateMv(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux){
    struct mv* auxMvStruct = aux;
    if(!auxMvStruct->moved){
        if(getInfoType(i) == 'c'){
            int id = getCircleId(getInfoFromInfo(i));
            if(id == auxMvStruct->id){
                double x1 = getCircleX(getInfoFromInfo(i));
                double y1 = getCircleY(getInfoFromInfo(i));
                setCircleX(getInfoFromInfo(i), x1 + auxMvStruct->dx);
                setCircleY(getInfoFromInfo(i), y1 + auxMvStruct->dy);
                double r = getCircleR(getInfoFromInfo(i));
                char colorBorder[20], colorFill[20];
                strcpy(colorBorder, getCircleBorder(getInfoFromInfo(i)));
                strcpy(colorFill, getCircleFill(getInfoFromInfo(i)));
                double circleMbbX1 = getCircleMBBX1(x1, r);
                double circleMbbY1 = getCircleMBBY1(y1, r);
                double circleMbbX2 = getCircleMBBX2(x1, r);
                double circleMbbY2 = getCircleMBBY2(y1, r);
                fprintf(auxMvStruct->pTxt, "círculo %d\n", id);
                fprintf(auxMvStruct->pTxt, "\tposição inicial: (%lf, %lf)\n\tposição final: (%lf, %lf)\n\tr: %lf\n\tcb: %s\n\tcf: %s\n", x1, y1, getCircleX(getInfoFromInfo(i)), getCircleY(getInfoFromInfo(i)), r, colorBorder, colorFill);
                auxMvStruct->moved = true;
                Info info = removeSRb(auxMvStruct->tree, x, y, &mbbX1, &mbbY1, &mbbX2, &mbbY2);
                insertSRb(auxMvStruct->tree, x1 + auxMvStruct->dx, y1 + auxMvStruct->dy, circleMbbX1, circleMbbY1, circleMbbX2, circleMbbY2, info);
            }
        }
        else if(getInfoType(i) == 'r'){
            int id = getRectId(getInfoFromInfo(i));
            if(id == auxMvStruct->id){
                double x1 = getRectX(getInfoFromInfo(i));
                double y1 = getRectY(getInfoFromInfo(i));
                setRectX(getInfoFromInfo(i), x1 + auxMvStruct->dx);
                setRectY(getInfoFromInfo(i), y1 + auxMvStruct->dy);
                double w = getRectW(getInfoFromInfo(i));
                double h = getRectH(getInfoFromInfo(i));
                char colorBorder[20], colorFill[20];
                strcpy(colorBorder, getRectBorder(getInfoFromInfo(i)));
                strcpy(colorFill, getRectFill(getInfoFromInfo(i)));
                double energy = getRectEnergy(getInfoFromInfo(i));
                double d = sqrt(pow(getRectX(getInfoFromInfo(i)) - x1, 2) + pow(getRectY(getInfoFromInfo(i)) - y1, 2));
                setRectEnergy(getInfoFromInfo(i), energy - (d / 5));
                fprintf(auxMvStruct->pTxt, "retângulo %d\n", id);
                fprintf(auxMvStruct->pTxt, "\tposição inicial: (%lf, %lf)\n\tposição final: (%lf, %lf)\n\tw: %lf\n\th: %lf\n\tcb: %s\n\tcf: %s\n\tenergy: %lf\n", x1, y1, getRectX(getInfoFromInfo(i)), getRectY(getInfoFromInfo(i)), w, h, colorBorder, colorFill, getRectEnergy(getInfoFromInfo(i)));
                auxMvStruct->moved = true;
                Info info = removeSRb(auxMvStruct->tree, x, y, &mbbX1, &mbbY1, &mbbX2, &mbbY2);
                insertSRb(auxMvStruct->tree, x1 + auxMvStruct->dx, y1 + auxMvStruct->dy, x1, y1, x1 + w, y1 + h, info);
            }
        }
        else if(getInfoType(i) == 'l'){
            int id = getLineId(getInfoFromInfo(i));
            if(id == auxMvStruct->id){
                double x1 = getLineX1(getInfoFromInfo(i));
                double y1 = getLineY1(getInfoFromInfo(i));
                double x2 = getLineX2(getInfoFromInfo(i));
                double y2 = getLineY2(getInfoFromInfo(i));
                setLineX1(getInfoFromInfo(i), x1 + auxMvStruct->dx);
                setLineY1(getInfoFromInfo(i), y1 + auxMvStruct->dy);
                setLineX2(getInfoFromInfo(i), x2 + auxMvStruct->dx);
                setLineY2(getInfoFromInfo(i), y2 + auxMvStruct->dy);
                char colorBorder[20];
                strcpy(colorBorder, getLineBorder(getInfoFromInfo(i)));
                fprintf(auxMvStruct->pTxt, "linha %d\n", id);
                fprintf(auxMvStruct->pTxt, "\tposição inicial: (%lf, %lf) (%lf, %lf)\n\tposição final: (%lf, %lf) (%lf, %lf)\n\tcor: %s\n", x1, y1, x2, y2, getLineX1(getInfoFromInfo(i)), getLineY1(getInfoFromInfo(i)), getLineX2(getInfoFromInfo(i)), getLineY2(getInfoFromInfo(i)), colorBorder);
                auxMvStruct->moved = true;
                Info info = removeSRb(auxMvStruct->tree, x, y, &mbbX1, &mbbY1, &mbbX2, &mbbY2);
                x1 = getLineX1(getInfoFromInfo(i));
                y1 = getLineY1(getInfoFromInfo(i));
                x2 = getLineX2(getInfoFromInfo(i));
                y2 = getLineY2(getInfoFromInfo(i));
                if(x1 > x2){
                    insertSRb(auxMvStruct->tree, x1, y1, x1, y1, x2, y2, info);
                }else{ 
                    insertSRb(auxMvStruct->tree, x1, y1, x2, y2, x1, y1, info);
                }
            }
        }
        else if(getInfoType(i) == 't'){
            int id = getTxtId(getInfoFromInfo(i));
            if(id == auxMvStruct->id){
                double x1 = getTxtX(getInfoFromInfo(i));
                double y1 = getTxtY(getInfoFromInfo(i));
                setTxtX(getInfoFromInfo(i), x1 + auxMvStruct->dx);
                setTxtY(getInfoFromInfo(i), y1 + auxMvStruct->dy);
                char colorBorder[20], colorFill[20], a, txt[100];
                strcpy(colorBorder, getTxtBorder(getInfoFromInfo(i)));
                strcpy(colorFill, getTxtFill(getInfoFromInfo(i)));
                a = getA(getInfoFromInfo(i));
                strcpy(txt, getTxt(getInfoFromInfo(i)));
                fprintf(auxMvStruct->pTxt, "texto %d\n", id);
                fprintf(auxMvStruct->pTxt, "\tposição inicial: (%lf, %lf)\n\tposição final: (%lf, %lf)\n\tcb: %s\n\tcp: %s\n\ta: %c\n\ttexto: %s\n", x1, y1, getTxtX(getInfoFromInfo(i)), getTxtY(getInfoFromInfo(i)), colorBorder, colorFill, a, txt);
                auxMvStruct->moved = true;
                Info info = removeSRb(auxMvStruct->tree, x, y, &mbbX1, &mbbY1, &mbbX2, &mbbY2);
                x1 = getLineX1(getInfoFromInfo(i));
                y1 = getLineY1(getInfoFromInfo(i));
                insertSRb(auxMvStruct->tree, x1, y1, x1, y1, x1, y1, info);
            }
        }
    }   
}