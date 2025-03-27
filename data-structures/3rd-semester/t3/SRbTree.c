#include "SRbTree.h"
#include "libraries.h"
#include "dot.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "txt.h"
#include "info.h"

struct TreeNode{
    struct TreeNode* parent;
    double x, y;
    Info info;
    double mbbx1, mbby1, mbbx2, mbby2;
    char color; // 'R' RED; 'B' BLACK
    struct TreeNode* left, *right;
};

struct SRbTree{
    double epsilon;
    struct TreeNode* root;
    struct TreeNode* nil;
};

SRbTree createSRb(double epsilon){
    struct SRbTree* new = (struct SRbTree*)malloc(sizeof(struct SRbTree));
    if(!new) return NULL;
    new->epsilon = epsilon;
    new->root = new->nil = NULL;
    return new;
}

void printTree(Node node){
    if(node){
        struct TreeNode* aux = node;
        if(aux->left) printTree(aux->left);
        if(aux->right) printTree(aux->right);
        printf("%p %c (%.2lf %.2lf)\n", aux, aux->color, aux->x, aux->y);
        if(aux->parent) printf("\tparent %p: %c (%.2lf %.2lf)\n", aux->parent, aux->parent->color, aux->parent->x, aux->parent->y);
        if(aux->right) printf("\tright child %p: %c (%.2lf %.2lf)\n", aux->right, aux->right->color, aux->right->x, aux->right->y);
        if(aux->left) printf("\tleft child %p: %c (%.2lf %.2lf)\n", aux->left, aux->left->color, aux->left->x, aux->left->y);
        printf("\n");
    }
}

bool isRoot(SRbTree tree, Node node){
    struct SRbTree* treeAux = tree;
    if(treeAux->root == node) return true;
    return false;
}

Node getUncle(Node node){
    struct TreeNode* aux = node;
    if(aux->parent){
        if(aux->parent->parent){
            if(aux->parent->parent->left != aux->parent){
                return aux->parent->parent->left;
            }
            return aux->parent->parent->right;
        }
    }
    return NULL;
}

Info getInfoFromNode(struct TreeNode* node){
    return node->info;
}

char getColor(struct TreeNode* node){
    return node->color;
}

void rightRotate(struct SRbTree* tree, struct TreeNode* x){ //RIGHT ROTATION
    struct TreeNode* y = x->left;
    if(y){   
        x->left = y->right;
        if(y->right != tree->nil){
            y->right->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == tree->nil){
            tree->root = y;
        }
        else if(x == x->parent->right){
            x->parent->right = y;
        }
        else{
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }
}

void leftRotate(struct SRbTree* tree, struct TreeNode* x){  //LEFT ROTATION
    struct TreeNode* y = x->right;
    x->right = y->left;
    if(y->left != tree->nil){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == tree->nil){
        tree->root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void fixTree(struct SRbTree* tree, struct TreeNode* z){
    while(z->parent && z->parent->color == 'R'){ // PARENT IS RED
        if(z->parent == z->parent->parent->left){ //PARENT IS LEFT CHILD
            struct TreeNode* y = z->parent->parent->right;
            if(y && y->color == 'R'){ //RED UNCLE
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->right){ //NODE IS RIGHT CHILD
                    z = z->parent;
                    leftRotate(tree, z);
                }
                //CASE 3
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(tree, z->parent->parent);
            }
        }
        else{ //PARENT IS RIGHT CHILD
            struct TreeNode* y = z->parent->parent->left;
            if(y && y->color == 'R'){ //RED UNCLE
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else{
                if(z == z->parent->left){ //NODE IS RIGHT CHILD
                    z = z->parent;
                    rightRotate(tree, z);
                } 
                //CASE 3
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                leftRotate(tree, z->parent->parent);
            }
        }

    }
    tree->root->color = 'B';
    tree->root->parent = tree->nil;
}

Node linkNode(struct SRbTree* tree, struct TreeNode* z, double epsilon){
    struct TreeNode* y = tree->nil; //variable for the parent of the added node
    struct TreeNode* x = tree->root;
    while(x != tree->nil) {
        y = x;
        if(z->x < x->x || (fabs(z->x - x->x) < tree->epsilon && z->y < x->y)){
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if(y == tree->nil){ //newly added node is root
        tree->root = z;
    }
    else if(z->x < y->x || (fabs(z->x - y->x) < tree->epsilon && z->y < y->y)){//data of child is less than its parent, left child
        y->left = z;
    }
    else{
        y->right = z;
    }
    z->right = tree->nil;
    z->left = tree->nil;
    z->color = 'R';
    fixTree(tree, z);
    return tree->root;
}

Node insertSRb(SRbTree t, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info){
    struct TreeNode* new = (struct TreeNode*)calloc(1, sizeof(struct TreeNode));
    new->x = x;
    new->y = y;
    new->info = info;
    new->mbbx1 = mbbX1;
    new->mbby1 = mbbY1;
    new->mbbx2 = mbbX2;
    new->mbby2 = mbbY2;
    struct SRbTree* tree = t;
    tree->root = linkNode(tree, new, tree->epsilon);
    if(!new) return NULL;
    return new;
}

Node traverseSearchNode(struct TreeNode* n, double xa, double ya){
    struct TreeNode* node = n;
    if(node == NULL){
        return NULL;
    }
    if(fabs(node->x - xa) <= 0 && fabs(node->y - ya) <= 0){
        return node;
    }
    if ((xa < node->x) || (xa == node->x && ya < node->y)){
        return traverseSearchNode(node->left, xa, ya);
    }
    else{
        return traverseSearchNode(node->right, xa, ya);
    }
}

Node getNodeSRb(SRbTree t, double xa, double ya, double* mbbX1, double* mbbY1, double* mbbX2, double* mbbY2){
    struct SRbTree* tree = t;
    struct TreeNode* aux = traverseSearchNode(tree->root, xa, ya);
    return aux;
}

void fixDeleteTree(struct SRbTree* tree, struct TreeNode* x){
    while(x != tree->root && x->color == 'B'){
        if(x == x->parent->left){
            struct TreeNode* w = x->parent->right;
            if(w->color == 'R'){ //CASE 1
                w->color = 'B';
                x->parent->color = 'R';
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if(w && w->left && w->left->color == 'B' && w->right && w->right->color == 'B'){ //CASE 2
                w->color = 'R';
                x = x->parent;
            }
            else{
                if(w && w->right && w->right->color == 'B'){
                    if(w->left){ //CASE 3
                        w->left->color = 'B';
                    }
                    w->color = 'R';
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                //CASE 4    
                w->color = x->parent->color;
                x->parent->color = 'B';
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        }
        else{
            struct TreeNode* w = x->parent->left;
            if(w && w->color == 'R'){ //CASE 1
                w->color = 'B';
                x->parent->color = 'R';
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if(w && w->left && w->left->color == 'B' && w->right && w->right->color == 'B'){ //CASE 2
                w->color = 'R';
                x = x->parent;
            }
            else{
                if(w && w->left && w->left->color == 'B'){
                    if(w && w->right){ //CASE 3
                        w->right->color = 'B';
                    }
                    w->color = 'R';
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                //CASE 4 
                if(w){
                    w->color = x->parent->color;
                }
                x->parent->color = 'B';
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
}

Node SRbMin(struct TreeNode* x){
    while(x->left){
        x = x->left;
    }
    return x;
}

void transplantSRb(struct SRbTree* tree, struct TreeNode* u, struct TreeNode* v){
    if(u->parent == tree->nil){ //U IS ROOT
        tree->root = v;
    }
    else if(u == u->parent->left){ //U IS LEFT CHILD
        u->parent->left = v;
    }
    else{ //U IS RIGHT CHILD
        u->parent->right = v;
    }
    if(v){
        v->parent = u->parent;
    }
}

Info removeSRb(SRbTree t, double xa, double ya, double* mbbX1, double* mbbY1, double* mbbX2, double* mbbY2){
    struct TreeNode* z = getNodeSRb(t, xa, ya, mbbX1, mbbY1, mbbX2, mbbY2);
    if(z){
        struct SRbTree* tree = t;
        struct TreeNode* y = z;
        struct TreeNode* x;
        char originalColor = y->color;
        if(z->left == tree->nil){
            x = z->right;
            transplantSRb(tree, z, z->right);
        }
        else if(z->right == tree->nil){
            x = z->left;
            transplantSRb(tree, z, z->left);
        }
        else{
            y = SRbMin(z->right);
            originalColor = y->color;
            x = y->right;
            if(y->parent == z && x){
                x->parent = y;
            }
            else{
                transplantSRb(tree, y, y->right);
                y->right = z->right;
                if(y->right){
                    y->right->parent = y;
                }
            }
            transplantSRb(tree, z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if(originalColor == 'B' && x){
            fixDeleteTree(tree, x);
        }
        Info info = getInfoFromNode(z);
        free(z);
        return info;
    }
    else return NULL;
}

void traversePrintTree(struct TreeNode* node, FILE* pDot, int depth){
    if(!node) return;
    traversePrintTree(node->right, pDot, depth);
    traversePrintTree(node->left, pDot, depth + 1);
    char c = getColor(node);
    char color[10];
    if(c == 'B'){
        strcpy(color, "black");
    }
    else{
        strcpy(color, "red");
    }
    Info infoNode = getInfoFromNode(node);
    InfoElement info = getInfoElement(infoNode);
    char element = getInfoType(infoNode);
    int id;
    double x, y;
    if(element == 'c'){
        id = getCircleId(info);
        x = getCircleX(info);
        y = getCircleY(info);
    }
    else if(element == 'r'){
        id = getRectId(info);
        x = getRectX(info);
        y = getRectY(info);
    }
    else if(element == 'l'){
        id = getLineId(info);
        x = getLineX1(info);
        y = getLineY1(info);
    }
    else if(element == 't'){
        id = getTxtId(info);
        x = getTxtX(info);
        y = getTxtY(info);
    }
    printNode(pDot, color, id, x, y);
    if(node->parent){
        int PId;
        Info PInfoNode = getInfoFromNode(node->parent);
        InfoElement PInfo = getInfoElement(PInfoNode);
        char Pelement = getInfoType(PInfoNode);
        if(Pelement == 'c'){
            PId = getCircleId(PInfo);
        }
        else if(Pelement == 'r'){
            PId = getRectId(PInfo);
        }
        else if(Pelement == 'l'){
            PId = getLineId(PInfo);
        }
        else if(Pelement == 't'){
            PId = getTxtId(PInfo);
        }
        printLink(pDot, id, PId);
    }
    if(!node->left || !node->right){
        printNLink(pDot, "nil", id);
    }
}

void printSRb(SRbTree t, char* nomeArq){
    struct SRbTree* tree = t;
    FILE* pDot = fopen(nomeArq, "a");
    traversePrintTree(tree->root, pDot, 0);
    fclose(pDot);
}

void traverseTree(struct TreeNode* node, FvisitaNo f, void* aux){
    if(!node) return;
    struct TreeNode* nodeLeft = node->left;
    struct TreeNode* nodeRight = node->right;
    Info info = getInfoFromNode(node);
    if(info) f(info, node->x, node->y, node->mbbx1, node->mbby1, node->mbbx2, node->mbby2, aux);
    traverseTree(nodeLeft, f, aux);
    traverseTree(nodeRight, f, aux);
}

void percursoProfundidade(SRbTree t, FvisitaNo fVisita, void* aux){
    struct SRbTree* tree = t;
    traverseTree(tree->root, fVisita, aux);
}

void freeTreeNodes(struct TreeNode* node){
    if(!node) return;
    freeTreeNodes(node->left);
    freeTreeNodes(node->right);
    freeInfo(node->info);
    free(node);
}

void killSRb(SRbTree t){
    struct SRbTree* tree = t;
    freeTreeNodes(tree->root);
    free(t);
}