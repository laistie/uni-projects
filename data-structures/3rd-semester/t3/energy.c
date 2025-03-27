#include "energy.h"

struct energy{
    double e;
    FILE* pTxt;
};

void* newEnergy(double e, FILE* pTxt){
    struct energy* new = (struct energy*)malloc(sizeof(struct energy));
    new->e = e;
    new->pTxt = pTxt;
    return new;
}

void setEnergy(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux){
    if(getInfoType(i) == 'r'){
        struct energy* auxStructEnergy = aux;
        setRectEnergy(getInfoFromInfo(i), auxStructEnergy->e);
        int id = getRectId(getInfoFromInfo(i));
        double w = getRectW(getInfoFromInfo(i));
        double h = getRectH(getInfoFromInfo(i));
        char colorBorder[20], colorFill[20];
        strcpy(colorBorder, getRectBorder(getInfoFromInfo(i)));
        strcpy(colorFill, getRectFill(getInfoFromInfo(i)));
        double energy = getRectEnergy(getInfoFromInfo(i));
        fprintf(auxStructEnergy->pTxt, "nau %d\n\tx: %lf \n\ty: %lf \n\tw: %lf \n\th: %lf \n\tcb: %s \n\tcf: %s\n\tenergy: %lf\n", id, x, y, w, h, colorBorder, colorFill, energy);
    }
}