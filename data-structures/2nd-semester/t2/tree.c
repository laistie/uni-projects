#include "tree.h"
#include "svg.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "txt.h"

struct node{ //TERNARY TREE NODE
    struct coordinates{
        double x, y;
    }coordinates;
    char type;
    void* element;
    bool activity;
    bool destruction;
    bool hit;
    struct node* lessX, *lessY, *greaterY;
};

struct tree{ //TERNARY TREE
    int size;
    struct node* root;
};

void* newTree(){
    struct tree* new = (struct tree*)malloc(sizeof(struct tree));
    new->size = 0;
    new->root = NULL;
    return new;
}

void* newNode(double x, double y, char type, void* element){
    struct node* new = (struct node*)malloc(sizeof(struct node));
    new->coordinates.x = x;
    new->coordinates.y = y;
    new->type = type;
    new->element = element;
    new->activity = true;
    new->destruction = new->hit = false;
    new->lessX = new->lessY = new->greaterY = NULL;
    return new;
}

bool isRoot(void* tree, void* node){
    if(getRoot(tree) == node){
        return true;
    }
    else{
        return false;
    }
}

void* insertTree(double x, double y, void* tree, void* node, char type, void* element){
    struct tree* auxT = tree;
    struct node* aux = node;
    if(!node){
        node = newNode(x, y, type, element);
        if(getSize(tree) == 0){
            auxT->root = node;
        }
        auxT->size++;
        return node;
    }
    if(x < aux->coordinates.x){
        aux->lessX = insertTree(x, y, tree, aux->lessX, type, element);
    }
    else if(y < aux->coordinates.y){
        aux->lessY = insertTree(x, y, tree, aux->lessY, type, element);
    }
    else{
        aux->greaterY = insertTree(x, y, tree, aux->greaterY, type, element);
    }
    return node;
}

void* getRoot(void* tree){
    struct tree* aux = tree;
    return aux->root;
}

int getSize(void* tree){
    struct tree* aux = tree;
    return aux->size;
}

char getType(void* node){
    struct node* aux = node;
    return aux->type;
}

void* getElement(void* node){
    struct node* aux = node;
    return aux->element;
}

bool getActivity(void* node){
    struct node* aux = node;
    return aux->activity;
}

bool getDestruction(void* node){
    struct node* aux = node;
    return aux->destruction;
}

bool getHit(void* node){
    struct node* aux = node;
    return aux->hit;
}

void setInactive(void* node){
    struct node* aux = node;
    aux->activity = false;
}

void setDestroyed(void* node){
    struct node* aux = node;
    aux->destruction = true;
}

void setHit(void* node){
    struct node* aux = node;
    aux->hit = true;
}

void printIndentation(int n){
    for(int i = 0; i < n; i++){
        printf("-");
    }
}

void printTreeNodes(void* node, int depth){
    struct node* aux = node;
    if(!node){
        return;
    }
    printIndentation(depth);
    printf("(%lf, %lf)\n", aux->coordinates.x, aux->coordinates.y);
    printTreeNodes(aux->lessX, depth);
    printTreeNodes(aux->lessY, depth + 1);
    printTreeNodes(aux->greaterY, depth + 1);
    printIndentation(depth);
}

void printTree(void* tree){
    printf("\n=== PRINTING TREE ===\n");
    printTreeNodes(getRoot(tree), 0);
}

void transverseTreeNodes(FILE* svg, void* node, int depth){
    struct node* aux = node;
    if(!node){
        return;
    }
    transverseTreeNodes(svg, aux->lessX, depth);
    transverseTreeNodes(svg, aux->lessY, depth + 1);
    transverseTreeNodes(svg, aux->greaterY, depth + 1);
    char type = getType(aux);
    void* element = getElement(aux);
    int id;
    double x1, y1, x2, y2, r, w, h;
    char colorBorder[20], colorFill[20], a, txt[30];
    if(getActivity(node) && !getDestruction(node)){
        if(type == 'c'){
            id = getCircleId(element);
            x1 = getCircleX(element);
            y1 = getCircleY(element);
            r = getCircleR(element);
            strcpy(colorBorder, getCircleBorder(element));
            strcpy(colorFill, getCircleFill(element));
            drawCircle(svg, id, x1, y1, r, colorBorder, colorFill);
        }
        else if(type == 'r'){
            id = getRectId(element);
            x1 = getRectX(element);
            y1 = getRectY(element);
            w = getRectW(element);
            h = getRectH(element);
            strcpy(colorBorder, getRectBorder(element));
            strcpy(colorFill, getRectFill(element));
            drawRect(svg, id, x1, y1, w, h, colorBorder, colorFill);
        }
        else if(type == 'l'){
            id = getLineId(element);
            x1 = getLineX1(element);
            y1 = getLineY1(element);
            x2 = getLineX2(element);
            y2 = getLineY2(element);
            strcpy(colorBorder, getLineBorder(element));
            drawLine(svg, id, x1, y1, x2, y2, colorBorder);
        }
        else if(type == 't'){
            id = getTxtId(element);
            x1 = getTxtX(element);
            y1 = getTxtY(element);
            strcpy(colorBorder, getTxtBorder(element));
            strcpy(colorFill, getTxtFill(element));
            a = getA(element);
            strcpy(txt, getTxt(element));
            drawText(svg, id, x1, y1, colorBorder, colorFill, a, txt);
        }
        if(getHit(node)){
            drawBe(svg, x1, y1);
        }
    }
}

void transverseTree(FILE* svg, void* tree){
    transverseTreeNodes(svg, getRoot(tree), 0);
}

int transverseTreeTp(FILE* svg, FILE* txt, void* node, int depth, double x, double y, int checks){
    struct node* aux = node;
    if(!node){
        return checks;
    }
    checks = transverseTreeTp(svg, txt, aux->lessX, depth, x, y, checks);
    checks = transverseTreeTp(svg, txt, aux->lessY, depth + 1, x, y, checks);
    checks = transverseTreeTp(svg, txt, aux->greaterY, depth + 1, x, y, checks);
    char type = getType(aux);
    void* element = getElement(aux);
    bool checker = false;
    if(type == 'c'){
        checker = checkCircle(element, x, y);
    }
    else if(type == 'r'){
        checker = checkRect(element, x, y);
    }
    else if(type == 'l'){
        checker = checkLine(element, x, y);
    }
    else if(type == 't'){
        checker = checkTxt(element, x, y);
    }
    if(checks == 0 && checker){
        fprintf(txt, "\n[*] tp %lf %lf\n", x, y);
        writeTp(txt, element, type);
        setDestroyed(node);
        checks++;
    }
    else if(checker){
        writeTp(txt, element, type);
        setDestroyed(node);
        checks++;
    }
    return checks;
}

int transverseTreeTr(FILE* svg, FILE* txt, void* tree, void* root, void* node, int depth, double x, double y, int id, int checks){
    struct node* aux = node;
    if(!node){
        return checks;
    }
    checks = transverseTreeTr(svg, txt, tree, root, aux->lessX, depth, x, y, id, checks);
    checks = transverseTreeTr(svg, txt, tree, root, aux->lessY, depth + 1, x, y, id, checks);
    checks = transverseTreeTr(svg, txt, tree, root, aux->greaterY, depth + 1, x, y, id, checks);
    char type = getType(aux);
    void* element = getElement(aux);
    void* newElement;
    double x1, y1, x2, y2, r, w, h;
    char colorBorder[20], colorFill[20], a, texto[30];
    bool checker = false;
    if(type == 'c'){
        checker = checkCircle(element, x, y);
        if(checker){
            x1 = getCircleX(element);
            y1 = getCircleY(element);
            r = getCircleR(element);
            strcpy(colorBorder, getCircleBorder(element));
            strcpy(colorFill, getCircleFill(element));
            newElement = newCircle(id + checks, x1 + x, y1 + y, r, colorFill, colorBorder);
            root = insertTree(x1 + x, y1 + y, tree, root, type, newElement);
        }
    }
    else if(type == 'r'){
        checker = checkRect(element, x, y);
        if(checker){
            x1 = getRectX(element);
            y1 = getRectY(element);
            w = getRectW(element);
            h = getRectH(element);
            strcpy(colorBorder, getCircleBorder(element));
            strcpy(colorFill, getCircleFill(element));
            newElement = newRect(id + checks, x1 + x, y1 + y, w, h, colorFill, colorBorder);
            root = insertTree(x1 + x, y1 + y, tree, root, type, newElement);
        }
    }
    else if(type == 'l'){
        checker = checkLine(element, x, y);
        if(checker){
            x1 = getLineX1(element);
            y1 = getLineY1(element);
            x2 = getLineX2(element);
            y2 = getLineY2(element);
            strcpy(colorBorder, getLineBorder(element));
            newElement = newLine(id + checks, x1 + x, y1 + y, x2 + x, y2+ y, colorBorder);
            root = insertTree(x1 + x, y1 + y, tree, root, type, newElement);
        }
    }
    else if(type == 't'){
        checker = checkTxt(element, x, y);
        if(checker){
            x1 = getTxtX(element);
            y1 = getTxtY(element);
            strcpy(colorBorder, getTxtBorder(element));
            strcpy(colorFill, getTxtFill(element));
            a = getA(element);
            strcpy(texto, getTxt(element));
            newElement = newTxt(id + checks, x1 + x, y1 + y, colorFill, colorBorder, a, texto);
            root = insertTree(x1 + x, y1 + y, tree, root, type, newElement);
        }
    }
    if(checks == 0 && checker){
        fprintf(txt, "\n[*] tr %lf %lf\n", x, y);
        writeTr(txt, element, type, x, y, id, checks);
        checks++;
    }
    else if(checker){
        writeTr(txt, element, type, x, y, id, checks);
        checks++;
    }
    return checks;
}

void updateProtection(FILE* txt, void* node, void* element, char type, double area, double elementArea, double v){
    double reduction = v * elementArea / area;
    double protectionLvl;
    if(type == 'c'){
        protectionLvl = updateCircleProtect(element, reduction);
    }
    else if(type == 'r'){
        protectionLvl = updateRectProtect(element, reduction);
    }
    else if(type == 'l'){
        protectionLvl = updateLineProtect(element, reduction);
    }
    else if(type == 't'){
        protectionLvl = updateTxtProtect(element, reduction);
    }
    if(protectionLvl <= 0){
        setInactive(node);
    }
    bool activity = getActivity(node);
    writeBe(txt, element, type, activity);
}

void transverseTreeBe(FILE* svg, FILE* txt, void* node, int depth, double x, double y, double w, double h, double v){
    struct node* aux = node;
    if(!node){
        return ;
    }
    transverseTreeBe(svg, txt, aux->lessX, depth, x, y, w, h, v);
    transverseTreeBe(svg, txt, aux->lessY, depth + 1, x, y, w, h, v);
    transverseTreeBe(svg, txt, aux->greaterY, depth + 1, x, y, w, h, v);
    char type = getType(aux);
    void* element = getElement(aux);
    double x1, y1, x2, y2, r, elementW, elementH, elementArea;
    double area = w * h;
    bool checker = false;
    if(type == 'c'){
        x1 = getCircleX(element);
        y1 = getCircleY(element);
        r = getCircleR(element);
        elementArea = 3.14 * pow(r, 2);
        checker = beCheckCircle(x1, y1, r, x, y, w, h);
    }
    else if(type == 'r'){
        x1 = getRectX(element);
        y1 = getRectY(element);
        elementW = getRectW(element);
        elementH = getRectH(element);
        elementArea = elementW * elementH;
        checker = beCheckRect(x1, y1, elementW, elementH, x, y, w, h);
    }
    else if(type == 'l'){
        x1 = getLineX1(element);
        y1 = getLineY1(element);
        x2 = getLineX2(element);
        y2 = getLineY2(element);
        double distance = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
        elementArea = 0.1 * distance;
        checker = beCheckLine(x1, y1, x2, y2, x, y, w, h);
    }
    else if(type == 't'){
        x1 = getTxtX(element);
        y1 = getTxtY(element);
        elementArea = 0.1;
        checker = beCheckText(x1, y1, x, y, w, h);
    }
    if(checker){
        setHit(node);
        updateProtection(txt, node, element, type, area, elementArea, v);
    }
    return;
}

double transverseTreePoints(void* node, int depth, double totalPoints){
    struct node* aux = node;
    if(!node){
        return totalPoints;
    }
    totalPoints = transverseTreePoints(aux->lessX, depth, totalPoints);
    totalPoints = transverseTreePoints(aux->lessY, depth + 1, totalPoints);
    totalPoints = transverseTreePoints(aux->greaterY, depth + 1, totalPoints);
    char type = getType(aux);
    void* element = getElement(aux);
    double points = 0;
    if(!getActivity(node)){ //INACTIVATION
        if(type == 'c'){
            points = 75;
        }
        else if(type == 'r'){
            points = 90;
        }
        else if(type == 'l'){
            points = 50;
        }
        else if(type == 't'){
            points = 30;
        }
    }
    else if(getDestruction(node)){ //DESTRUCTION
        if(type == 'c'){
            double r = getCircleR(element);
            points = 75 / (3.14 * pow(r, 2) / 5);
        }
        else if(type == 'r'){
            double w = getRectW(element);
            double h = getRectH(element);
            points = 90 / (w * h / 5);
        }
        else if(type == 'l'){
            points = 150;
        }
        else if(type == 't'){
            points = 500;
        }
    }
    totalPoints = totalPoints + points;
    return totalPoints;
}

double transverseTreeMaxPoints(void* node, int depth, double maxPoints, char* qryFunction){
    struct node* aux = node;
    if(!node){
        return maxPoints;
    }
    maxPoints = transverseTreeMaxPoints(aux->lessX, depth, maxPoints, qryFunction);
    maxPoints = transverseTreeMaxPoints(aux->lessY, depth + 1, maxPoints, qryFunction);
    maxPoints = transverseTreeMaxPoints(aux->greaterY, depth + 1, maxPoints, qryFunction);
    char type = getType(aux);
    void* element = getElement(aux);
    double points;
    if(strcmp(qryFunction, "be") == 0){ //IF ONLY BE FUNCTION, GEOMETRIC SHAPES ONLY CAN BE INACTIVATED
        if(type == 'c'){
            points = 60;
        }   
        else if(type == 'r'){
            points = 90;
        }
        else if(type == 'l'){
            points = 50;
        }
        else if(type == 't'){
            points = 30;
        }
    }
    else{ //IF ANY TORPEDO FUNCTION IS INCLUDED ON .QRY FILE, CONSIDER GEOMETRIC SHAPES CAN BE DESTROYED
        if(type == 'c'){
            double r = getCircleR(element);
            points = 75 / (3.14 * pow(r, 2) / 5);
        }
        else if(type == 'r'){
            double w = getRectW(element);
            double h = getRectH(element);
            points = 90 / (w * h / 5);
        }
        else if(type == 'l'){
            points = 150;
        }
        else if(type == 't'){
            points = 500;
        }
    }
    maxPoints = maxPoints + points;
    return maxPoints;
}

void freeNodes(void* node){ 
    struct node* aux = node;
    if(!node){
        return;
    }
    freeNodes(aux->lessX);
    freeNodes(aux->lessY);
    freeNodes(aux->greaterY);
    char type = getType(aux);
    if(type == 'c'){
        freeCircle(aux->element);
    }
    else if(type == 'r'){
        freeRect(aux->element);
    }
    else if(type == 'l'){
        freeLine(aux->element);
    }
    else if(type == 't'){
        freeTxt(aux->element);
    }
    free(aux);
}

void freeTree(void* tree){
    freeNodes(getRoot(tree));
    free(tree);
}