#include "d.h"

struct d{
    int i;
    char lado[3];
    double d, pointImpactX, pointImpactY;
    bool found;
    Lista list;
    SRbTree tree;
    FILE* pTxt;
};

void* newD(int i, char lado[3], double d, SRbTree tree, FILE* pTxt){
    struct d* new = (struct d*)malloc(sizeof(struct d));
    new->i = i;
    strcpy(new->lado, lado);
    new->d = d;
    new->found = false;
    new->tree = tree;
    new->pTxt = pTxt;
    return new;
}

double getPointImpactX(void* aux){
    struct d* dAux = aux;
    return dAux->pointImpactX;
}

double getPointImpactY(void* aux){
    struct d* dAux = aux;
    return dAux->pointImpactY;
}

void setPointImpact(void* d, double x, double y){
    struct d* dAux = d;
    dAux->pointImpactX = x;
    dAux->pointImpactY = y;
}

void setDList(void* d, Lista list){
    struct d* dAux = d;
    dAux->list = list;
}

void checkD(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux){
    struct d* auxDStruct = aux;
    if(getInfoType(i) == 'r'){
        double x1 = getRectX(getInfoFromInfo(i));
        double y1 = getRectY(getInfoFromInfo(i));
        double w = getRectW(getInfoFromInfo(i));
        double h = getRectH(getInfoFromInfo(i));
        if(checkRectHit(x1, y1, w, h, auxDStruct->pointImpactX, auxDStruct->pointImpactY)){
            int id = getRectId(getInfoFromInfo(i));
            char colorBorder[20], colorFill[20];
            strcpy(colorBorder, getRectBorder(getInfoFromInfo(i)));
            strcpy(colorFill, getRectFill(getInfoFromInfo(i)));
            fprintf(auxDStruct->pTxt, "\tnau %d atingida\n", id);
            fprintf(auxDStruct->pTxt, "\t\tx: %lf\n\t\ty: %lf\n\t\tw: %lf\n\t\th: %lf\n\t\tcb: %s\n\t\tcf: %s\n", x1, y1, w, h, colorBorder, colorFill);
            Info info = removeSRb(auxDStruct->tree, x, y, &mbbX1, &mbbY1, &mbbX2, &mbbY2);
            freeInfo(info);
        }
    }
}

void updateD(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux){
    struct d* auxDStruct = aux;
    if(!auxDStruct->found){
        if(getInfoType(i) == 'r'){
            int id = getRectId(getInfoFromInfo(i));
            if(id == auxDStruct->i){
                auxDStruct->found = true;
                double energy = getRectEnergy(getInfoFromInfo(i));
                if(energy < auxDStruct->d){
                    fprintf(auxDStruct->pTxt, "\tnau %d sem energia suficiente para disparar canhão\n", id);
                    return;
                }
                if(strcmp(auxDStruct->lado, "PP") == 0){ // POPA, MENOR COORDENADA Y
                    double cannon = getRectX(getInfoFromInfo(i)) + (getRectW(getInfoFromInfo(i)) / 2);
                    setPointImpact(auxDStruct, cannon, getRectY(getInfoFromInfo(i)) - auxDStruct->d);
                    fprintf(auxDStruct->pTxt, "\tponto de impacto (%lf, %lf)\n", auxDStruct->pointImpactX, auxDStruct->pointImpactY);
                    percursoProfundidade(auxDStruct->tree, checkD, auxDStruct);
                    insertList(auxDStruct->list, 'd', auxDStruct->pointImpactX, auxDStruct->pointImpactY, 0, 0);
                }
                else if(strcmp(auxDStruct->lado, "PR") == 0){ // PROA, MAIOR COORDENADA Y
                    double cannon = getRectX(getInfoFromInfo(i)) + (getRectW(getInfoFromInfo(i)) / 2);
                    setPointImpact(auxDStruct, cannon, getRectY(getInfoFromInfo(i)) + getRectH(getInfoFromInfo) + auxDStruct->d);
                    fprintf(auxDStruct->pTxt, "\tponto de impacto (%lf, %lf)\n", auxDStruct->pointImpactX, auxDStruct->pointImpactY);
                    percursoProfundidade(auxDStruct->tree, checkD, auxDStruct);
                    insertList(auxDStruct->list, 'd', auxDStruct->pointImpactX, auxDStruct->pointImpactY, 0, 0);
                }
                else if(strcmp(auxDStruct->lado, "EB") == 0){ // ESTIBORDO, MENOR COORDENADA X
                    double cannon = getRectY(getInfoFromInfo(i)) + (getRectH(getInfoFromInfo(i)) / 2);
                    setPointImpact(auxDStruct, getRectX(getInfoFromInfo(i)) - auxDStruct->d , cannon);
                    fprintf(auxDStruct->pTxt, "\tponto de impacto (%lf, %lf)\n", auxDStruct->pointImpactX, auxDStruct->pointImpactY);
                    percursoProfundidade(auxDStruct->tree, checkD, auxDStruct);
                    insertList(auxDStruct->list, 'd', auxDStruct->pointImpactX, auxDStruct->pointImpactY, 0, 0);
                }
                else if(strcmp(auxDStruct->lado, "BB") == 0){ // BOMBORDO, MAIOR COORDENADA X
                    double cannon =  getRectY(getInfoFromInfo(i)) + (getRectH(getInfoFromInfo(i)) / 2);
                    setPointImpact(auxDStruct, getRectX(getInfoFromInfo(i)) + getRectW(getInfoFromInfo(i)) + auxDStruct->d, cannon);
                    fprintf(auxDStruct->pTxt, "\tponto de impacto (%lf, %lf)\n", auxDStruct->pointImpactX, auxDStruct->pointImpactY);
                    percursoProfundidade(auxDStruct->tree, checkD, auxDStruct);
                    insertList(auxDStruct->list, 'd', auxDStruct->pointImpactX, auxDStruct->pointImpactY, 0, 0);
                }
                setRectEnergy(getInfoFromInfo(i), energy - auxDStruct->d);
                fprintf(auxDStruct->pTxt, "\tenergia restante (nau %d): %lf\n", id, getRectEnergy(getInfoFromInfo(i)));
            }
        }
    }
}