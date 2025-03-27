#include "mc.h"

struct mc{
    SRbTree tree;
    double dx, dy, x, y, w, h;
    FILE* pTxt;
};

void* newMc(SRbTree tree, double dx, double dy, double x, double y, double w, double h, FILE* pTxt){
    struct mc* new = (struct mc*)malloc(sizeof(struct mc));
    new->tree = tree;
    new->dx = dx;
    new->dy = dy;
    new->x = x;
    new->y = y;
    new->w = w;
    new->h = h;
    new->pTxt = pTxt;
    return new;
}

bool checkCircle(double circleX, double circleY, double circleR, double areaX, double areaY, double areaW, double areaH){
    double limitRight = areaX + areaW;
    double limitDown = areaY + areaH;
    if(circleX + circleR <= limitRight && circleY - circleR >= areaY && circleX - circleR >= areaX && circleY + circleR <= limitDown){
        return true;
    }
    return false;
}

void updateMc(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux){
    struct mc* auxMcStruct = aux;
    if(getInfoType(i) == 'c'){
        int id = getCircleId(getInfoFromInfo(i));
        double x1 = getCircleX(getInfoFromInfo(i));
        double y1 = getCircleY(getInfoFromInfo(i));
        double r = getCircleR(getInfoFromInfo(i));
        if(checkCircle(x1, y1, r, auxMcStruct->x, auxMcStruct->y, auxMcStruct->w, auxMcStruct->h)){
            Info info = removeSRb(auxMcStruct->tree, x1, y1, &mbbX1, &mbbY1, &mbbX2, &mbbY2);
            setCircleX(getInfoFromInfo(info), x1 + auxMcStruct->dx);
            setCircleY(getInfoFromInfo(info), y1 + auxMcStruct->dy);
            char colorBorder[20], colorFill[20];
            strcpy(colorBorder, getCircleBorder(getInfoFromInfo(info)));
            strcpy(colorFill, getCircleFill(getInfoFromInfo(info)));
            double circleMbbX1 = getCircleMBBX1(x1, r);
            double circleMbbY1 = getCircleMBBY1(y1, r);
            double circleMbbX2 = getCircleMBBX2(x1, r);
            double circleMbbY2 = getCircleMBBY2(y1, r);
            fprintf(auxMcStruct->pTxt, "peixe %d\n", id);
            fprintf(auxMcStruct->pTxt, "\tposição inicial: (%lf, %lf)\n\tposição final: (%lf, %lf)\n\tr: %lf\n\tcb: %s\n\tcf: %s\n", x1, y1, getCircleX(getInfoFromInfo(i)), getCircleY(getInfoFromInfo(i)), r, colorBorder, colorFill);
            insertSRb(auxMcStruct->tree, x1 + auxMcStruct->dx, y1 + auxMcStruct->dy, circleMbbX1, circleMbbY1, circleMbbX2, circleMbbY2, info);
        }
    }
}  