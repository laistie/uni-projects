#include "list.h"

struct listNode{
    Element element;
    struct listNode* prev, *next;
};

struct list{
    struct listNode* head;
    int size;
};

struct listNode* cwHead;

List newList(){
    struct list* new = (struct list*)malloc(sizeof(struct list));
    new->head = NULL;
    new->size = 0;
    return new;
}

ListNode newElement(Element element){
    struct listNode* new = (struct listNode*)malloc(sizeof(struct listNode));
    new->element = element;
    new->prev = new->next = NULL;
    return new;
}

void insertList(List list, Element element){
    struct list* auxList = list;
    struct listNode* new = newElement(element);
    if(!auxList->head){
        auxList->head = new;
        cwHead = auxList->head;
        auxList->size++;
        return;
    }
    struct listNode* auxNode = auxList->head;
    while(auxNode->next){
        auxNode = auxNode->next;
    }
    auxNode->next = new;
    new->prev = auxNode;
    auxList->size++;
}

int getListSize(List list){
    struct list* aux = list;
    return aux->size;
}

bool checkIsInList(Element element){
    struct listNode* aux = cwHead;
    if(!aux){
        return false;
    }
    while(aux){
        if(element == aux->element){
            return true;
        }
        aux = aux->next;
    }
    return false;
}

bool checkIsEmptyList(List list){
    struct list* aux = list;
    if(!aux->head){
        return true;
    }
    return false;
}

Element getElementAtPos(int position){
    struct listNode* aux = cwHead;
    for(int i = 0; i < position; i++){
        aux = aux->next;
    }
    return aux->element;
}

Element getLastElement(){
    struct listNode* aux = cwHead;
    while(aux->next){
        aux = aux->next;
    }
    return aux->element;
}

void drawSelection(FILE* pSvg, double x, double y){
    fprintf(pSvg, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"2.5\" stroke=\"red\" stroke-width=\"1\" fill-opacity=\"0\"/>", x, y);
}

void reportSelections(FILE* pTxt, FILE* pSvg){
    struct listNode* aux = cwHead;
    if(!aux){
        printf("Erro: lista de figuras selecionadas vazia\n");
        return;
    }
    int id;
    while(aux){
        if(getInfoType(aux->element) == 'c'){
            id = getCircleId(getInfoFromInfo(aux->element));
            drawSelection(pSvg, getCircleX(getInfoFromInfo(aux->element)), getCircleY(getInfoFromInfo(aux->element)));
            fprintf(pTxt, "%d: círculo\n", id);
        }
        else if (getInfoType(aux->element) == 'r'){
            id = getRectId(getInfoFromInfo(aux->element));
            drawSelection(pSvg, getRectX(getInfoFromInfo(aux->element)), getRectY(getInfoFromInfo(aux->element)));
            fprintf(pTxt, "%d: retângulo\n", id);
        }
        else if (getInfoType(aux->element) == 'l'){
            id = getLineId(getInfoFromInfo(aux->element));
            drawSelection(pSvg, getLineX1(getInfoFromInfo(aux->element)), getLineY1(getInfoFromInfo(aux->element)));
            fprintf(pTxt, "%d: linha\n", id);
        }
        else if (getInfoType(aux->element) == 't'){
            id = getTxtId(getInfoFromInfo(aux->element));
            drawSelection(pSvg, getTxtX(getInfoFromInfo(aux->element)), getTxtY(getInfoFromInfo(aux->element)));
            fprintf(pTxt, "%d: texto\n", id);
        }
        aux = aux->next;
    }
}

void reportDeletions(FILE* pTxt){
    struct listNode* aux = cwHead;
    if(!aux){
        printf("Erro: lista de figuras selecionadas vazia\n");
        return;
    }
    int id;
    while(aux){
        if(getInfoType(aux->element) == 'c'){
            id = getCircleId(getInfoFromInfo(aux->element));
            double x = getCircleX(getInfoFromInfo(aux->element));
            double y = getCircleY(getInfoFromInfo(aux->element));
            double r = getCircleR(getInfoFromInfo(aux->element));
            char colorBorder[20], colorFill[20];
            strcpy(colorBorder, getCircleBorder(getInfoFromInfo(aux->element)));
            strcpy(colorFill, getCircleFill(getInfoFromInfo(aux->element)));
            fprintf(pTxt, "%d: círculo\n\tx: %lf \n\ty: %lf \n\tr: %lf \n\tcb: %s \n\tcf: %s\n", id, x, y, r, colorBorder, colorFill);
        }
        else if (getInfoType(aux->element) == 'r'){
            id = getRectId(getInfoFromInfo(aux->element));
            double x = getRectX(getInfoFromInfo(aux->element));
            double y = getRectY(getInfoFromInfo(aux->element));
            double w = getRectW(getInfoFromInfo(aux->element));
            double h = getRectH(getInfoFromInfo(aux->element));
            char colorBorder[20], colorFill[20];
            strcpy(colorBorder, getRectBorder(getInfoFromInfo(aux->element)));
            strcpy(colorFill, getRectFill(getInfoFromInfo(aux->element)));
            fprintf(pTxt, "%d: retângulo\n\tx: %lf \n\ty: %lf \n\tw: %lf \n\th: %lf \n\tcb: %s \n\tcf: %s\n", id, x, y, w, h, colorBorder, colorFill);
        }
        else if (getInfoType(aux->element) == 'l'){
            id = getLineId(getInfoFromInfo(aux->element));
            double x1 = getLineX1(getInfoFromInfo(aux->element));
            double y1 = getLineY1(getInfoFromInfo(aux->element));
            double x2 = getLineX2(getInfoFromInfo(aux->element));
            double y2 = getLineY2(getInfoFromInfo(aux->element));
            char color[20];
            strcpy(color, getLineBorder(getInfoFromInfo(aux->element)));
            fprintf(pTxt, "%d: linha\n\tx1: %lf \n\ty1: %lf \n\tx2: %lf \n\ty2: %lf \n\tcolor: %s\n", id, x1, y1, x2, y2, color);
        }
        else if (getInfoType(aux->element) == 't'){
            id = getTxtId(getInfoFromInfo(aux->element));
            double x = getTxtX(getInfoFromInfo(aux->element));
            double y = getTxtY(getInfoFromInfo(aux->element));
            char colorBorder[20], colorFill[20], a, text[100];
            strcpy(colorBorder, getTxtBorder(getInfoFromInfo(aux->element)));
            strcpy(colorFill, getTxtFill(getInfoFromInfo(aux->element)));
            a = getA(getInfoFromInfo(aux->element));
            strcpy(text, getTxt(getInfoFromInfo(aux->element)));
            fprintf(pTxt, "%d: texto\n\tx: %lf\n\ty: %lf\n\tcb: %s\n\tcp: %s\n\ta: %c\n\ttxt: %s\n", id, x, y, colorBorder, colorFill, a, text);
        }
        aux = aux->next;
    }
}

void mergeLists(List l1, List l2){
    struct list* auxL2 = l2;
    if(!auxL2->head){
        free(l2);
        return;
    }
    struct list* auxL1 = l1;
    cwHead = auxL1->head;
    struct listNode* auxNodeL2 = auxL2->head;
    if(auxNodeL2->next){
        while(auxNodeL2->next){
            insertList(l1, auxNodeL2->element);
            auxNodeL2 = auxNodeL2->next;
        }
    }
    else{
        insertList(l1, auxNodeL2->element);
    }
    freeList(l2);
}

void printList(){
    struct listNode* aux = cwHead;
    if(!aux){
        printf("Erro: lista de figuras selecionadas vazia\n");
        return;
    }
    printf("\n===SELECTED LIST===\n");
    while(aux){
        printf(" %p ->", aux->element);
        aux = aux->next;
    }
}

void freeList(List list){
    struct list* aux = list;
    if(!aux->head){
        free(list);
        return;
    }
    struct listNode* temp;
    while(aux->head){
        temp = aux->head;
        aux->head = aux->head->next;
        free(temp);
    }
    free(list);
}