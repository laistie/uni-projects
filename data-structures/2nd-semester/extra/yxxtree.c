#include "yxxtree.h"
#include "info.h"
#include "queue.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "txt.h"

struct treeNode{
    double x, y;
    Info info;
    bool removed;
    struct treeNode* se, *sm, *sd;
};

struct ternaryTree{
    double degFactor;
    int size;
    struct treeNode* root;
};

YxxTree newYxxTree(double fd){
    struct ternaryTree* new = (struct ternaryTree*)malloc(sizeof(struct ternaryTree));
    new->degFactor = fd;
    new->size = 0;
    new->root = NULL;
    return new;
}

Node allocNewNode(double x, double y, Info info){
    struct treeNode* new = (struct treeNode*)malloc(sizeof(struct treeNode));
    new->x = x;
    new->y = y;
    new->info = info;
    new->removed = false;
    new->se = new->sm = new->sd = NULL;
    return new;
}

int getSize(YxxTree tree){
    struct ternaryTree* aux = tree;
    return aux->size;
}

double getFd(YxxTree tree){
    struct ternaryTree* aux = tree;
    return aux->degFactor;
}

Node insertYxxT(YxxTree tree, Node node, double x, double y, Info info){
    struct ternaryTree* auxTree = tree;
    if(!node){
        node = allocNewNode(x, y, info);
        if(getSize(tree) == 0){
            auxTree->root = node;
        }
        auxTree->size++;
        return node;
    }
    struct treeNode* aux = node;
    if(y < aux->y){
        aux->se = insertYxxT(tree, aux->se, x, y, info);
    }
    else if(x < aux->x){
        aux->sm = insertYxxT(tree, aux->sm, x, y, info);
    }
    else{
        aux->sd = insertYxxT(tree, aux->sd, x, y, info);
    }
    return node;
}

Node transverseGetNode(Node node, double x, double y, double epsilon, Node requested){
    struct treeNode* aux = node;
    if(fabs(aux->x - x) < epsilon && fabs(aux->y - y) < epsilon){
        return node;
    }
    if(aux->se){
        requested = transverseGetNode(aux->se, x, y, epsilon, requested);
    }
    if(aux->sm){
        requested = transverseGetNode(aux->sm, x, y, epsilon, requested);
    }
    if(aux->sd){
        requested = transverseGetNode(aux->sd, x, y, epsilon, requested);
    }
    return requested;
}

Node getNodeYxxT(YxxTree tree, double x, double y, double epsilon){
    Node node = getRoot(tree);
    node = transverseGetNode(getRoot(tree), x, y, epsilon, node);
    return node;
}

Info getInfoFromNode(Node node){
    struct treeNode* aux = node;
    return aux->info;
}

Node getRoot(YxxTree tree){
    struct ternaryTree* aux = tree;
    return aux->root;
}

bool getStatus(Node node){
    struct treeNode* aux = node;
    return aux->removed;
}

bool goSe(Node node, double y){ //A REGIÃO SE ESTENDE ACIMA DO PONTO
    struct treeNode* aux = node;
    if(y <= aux->y){
        return true;
    }
    return false;
}

bool goSm(Node node, double x, double y){ //A REGIÃO SE ESTENDE ABAIXO E À ESQUERDA DO PONTO
    struct treeNode* aux = node;
    if(y >= aux->y && x <= aux->x){
        return true;
    }
    return false;
}

bool goSd(Node node, double x, double y){ //A REGIÃO SE ESTENDE ABAIXO E À DIREITA DO PONTO
    struct treeNode* aux = node;
    if(y >= aux->y && x >= aux->x){
        return true;
    }
    return false;
}

bool checkInsideArea(Info i, double x1, double y1, double x2, double y2){
    bool checker;
    if(getInfoType(i) == 'c'){
        checker = checkCircle(getInfoFromInfo(i), x1, y1, x2, y2);
    }
    else if(getInfoType(i) == 'r'){
        checker = checkRect(getInfoFromInfo(i), x1, y1, x2, y2);
    }
    else if(getInfoType(i) == 'l'){
        checker = checkLine(getInfoFromInfo(i), x1, y1, x2, y2);
    }
    else if(getInfoType(i) == 't'){
        checker = checkTxt(getInfoFromInfo(i), x1, y1, x2, y2);
    }
    return checker;
}

void transverseSearch(YxxTree tree, Node node, List list, int depth, double x1, double y1, double x2, double y2){
    struct treeNode* auxNode = node;
    if(auxNode->se){
        if(goSe(auxNode, y1)){
            transverseSearch(tree, auxNode->se, list, depth, x1, y1, x2, y2);
        }
    }
    if(auxNode->sm){
        if(goSm(auxNode, x1, y2)){
            transverseSearch(tree, auxNode->sm, list, depth, x1, y1, x2, y2);
        }
    }
    if(auxNode->sd){
        if(goSd(auxNode, x2, y2)){
            transverseSearch(tree, auxNode->sd, list, depth, x1, y1, x2, y2);
        }
    }
    if(checkInsideArea(auxNode->info, x1, y1, x2, y2)){
        insertList(list, getInfoFromNode(node));
    }
}

List getNodesDentroRegiaoYxxT(YxxTree tree, double x1, double y1, double x2, double y2){
    List list = newList();
    transverseSearch(tree, getRoot(tree), list, 0, x1, y1, x2, y2);
    return list;
}

void transverseYxxT(Node node, FvisitaNo f, void* aux, int depth){
    if(!node){
        return;
    }
    struct treeNode* nodeAux = node;
    transverseYxxT(nodeAux->se, f, aux, depth);
    transverseYxxT(nodeAux->sm, f, aux, depth + 1);
    transverseYxxT(nodeAux->sd, f, aux, depth + 1);
    Info info = getInfoFromNode(node);
    f(info, nodeAux->x, nodeAux->y, aux);
}

void visitaProfundidadeYxxT(YxxTree tree, FvisitaNo f, void* aux){
    transverseYxxT(getRoot(tree), f, aux, 0);
}

int compare(void* a, void* b){
    return(*(double*)a - *(double*)b);
}

void reorganizeTreeNodes(Info i, double x, double y, void* aux){
    if(getRear(aux) == 97){
        //qsort(aux, 97, sizeof(void*), compare);
        freeQueue(aux);
        aux = newQueue(97);
        enqueue(aux, x, y);
    }
}

void rebuildTree(YxxTree tree){
    Queue coordinatesNodesArray = newQueue(97);
    visitaProfundidadeYxxT(tree, reorganizeTreeNodes, coordinatesNodesArray);
}

int getRmvTotal(Node node, int depth, int total){
    if(!node){
        return total;
    }
    struct treeNode* nodeAux = node;
    total = getRmvTotal(nodeAux->se, depth, total);
    total = getRmvTotal(nodeAux->sm, depth + 1, total);
    total = getRmvTotal(nodeAux->sd, depth + 1, total);
    if(getStatus(node)){
        total++;
    }
    return total;
}

void removeNoYxxT(YxxTree tree, Node node){
    struct treeNode* aux = node;
    aux->removed = true;
    int totalRmv = getRmvTotal(getRoot(tree), 0, 0);
    int totalNodes = getSize(tree);
    if(totalRmv / totalNodes > getFd(tree)){
        printf("WARNING: should rebuild tree\n");
    }
}

void printTreeNodes(Node node, int depth){
    if(!node){
        return;
    }
    struct treeNode* aux = node;
    printTreeNodes(aux->se, depth);
    printTreeNodes(aux->sm, depth + 1);
    printTreeNodes(aux->sd, depth + 1);
    printf("(%lf, %lf)", aux->x, aux->y);
}

void printTree(YxxTree tree){
    printf("\n===TREE===\n");
    printTreeNodes(getRoot(tree), 0);
}

void freeTreeNodes(Node node){ 
    if(!node){
        return;
    }
    struct treeNode* aux = node;
    freeTreeNodes(aux->se);
    freeTreeNodes(aux->sm);
    freeTreeNodes(aux->sd);
    freeInfo(aux->info);
    free(aux);
}

void freeTree(YxxTree tree){
    freeTreeNodes(getRoot(tree));
    free(tree);
}