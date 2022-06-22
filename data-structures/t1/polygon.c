#include "polygon.h"

struct polygonQueue{
    int front, rear;
    int size;
    void** coordinates; //VOID POINTER ARRAY OF COORDINATES
};

void* newPolQueue(int size){
    struct polygonQueue* new = (struct polygonQueue*)malloc(sizeof(struct polygonQueue));
    new->front = 0;
    new->rear = 0;
    new->size = size + 1; //QUEUE ALWAYS HAS A REMAINING FREE SLOT
    new->coordinates = malloc(sizeof(void*) * MAX_QUEUE);
    return new;
}

bool isFull(void* polQueue){
    struct polygonQueue* aux = polQueue;
    if((aux->rear + 1) % aux->size == aux->front){
        return true;
    }
    else{
        return false;
    }
}

bool isEmpty(void* polQueue){
    struct polygonQueue* aux = polQueue;
    if(aux->front == aux->rear){
        return 1;
    }
    else{
        return 0;
    }
}

void enqueue(void* polQueue, char type, int id, int position){
    if(isFull(polQueue) == true){
        printf("\nErro ao adicionar elemento: fila circular estatica cheia\n");
        return;
    }
    struct polygonQueue* aux = polQueue;
    aux->rear++;
    void* coordinates = newCoordinates();
    double x, y;
    x = getX(position, type);
    y = getY(position, type);
    insertCoordinates(coordinates, x, y);
    if(aux->rear > aux->size){ //ALREADY REACHED THE END OF QUEUE, BUT ITS CIRCULAR AND THERES SPACE LEFT
        aux->rear = 0;
        aux->coordinates[aux->rear] = coordinates;
    }
    else{
        aux->coordinates[aux->rear] = coordinates;  
    }
}

void dequeue(void* polQueue, void* coordinates){
    if(isEmpty(polQueue) == true){
        printf("\nErro ao remover elemento: fila circular estatica vazia\n");
        return;
    }
    struct polygonQueue* aux = polQueue;
    freeCoordinates(coordinates);
    aux->front++;
}

void* getCurrentCoordinates(void* polQueue){
    struct polygonQueue* aux = polQueue;
    return aux->coordinates[aux->rear];
}

void* getFirstCoordinates(void* polQueue){
    struct polygonQueue* aux = polQueue;
    return aux->coordinates[aux->front + 1];
}

void* getCoordinatesAt(void* polQueue, int position){
    struct polygonQueue* aux = polQueue;
    return aux->coordinates[position];
}

void drawPolLines(FILE* svg, void* polQueue, int start, int sides, double d, double e, char color[15], double minX, double maxX, double minY, double maxY){
    int numberLines = (maxY - minY) / d;
    double x1, y1, x2, y2;
    for(int i = 1; i <= numberLines; i++){
        x1 = minX;
        y1 = minY + i * d;
        x2 = maxX;
        y2 = y1;
        fprintf(svg, "\n\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:%s; stroke-width:%.2lf\"/>", x1, y1, x2, y2, color, e);
    }
}

void drawPolygon(FILE* svg, void* polQueue, int start, double d, double e, char colorBorder[15], char colorFill[15]){
    if(isEmpty(polQueue) == 1){
        printf("Erro: fila circular estatica vazia\n");
        return;
    }
    fprintf(svg, "\n\t<polygon points=\"");
    struct polygonQueue* aux = polQueue;
    void* coordinates;
    int sides = 0;
    double x, y, minX, maxX, minY, maxY;
    start = start % (aux->rear - aux->front);
    for(int i = start; i <= aux->rear; i++){
        coordinates = getCoordinatesAt(polQueue, i);
        x = getCoordX(coordinates);
        y = getCoordY(coordinates);
        if(i == start){
            minX = maxX = x;
            minY = maxY = y;
        }
        if(x < minX){
            minX = x;
        }
        if(x > maxX){
            maxX = x;
        }
        if(y < minY){
            minY = y;
        }
        if(y > maxY){
            maxY = y;
        }
        fprintf(svg, "%lf,%lf ", x, y);
        sides++;
    }
    if(aux->front < start){
        for(int i = aux->front + 1; i <= start; i++){
            coordinates = getCoordinatesAt(polQueue, i);
            x = getCoordX(coordinates);
            y = getCoordY(coordinates);
            if(x < minX){
                minX = x;
            }
            if(x > maxX){
                maxX = x;
            }
            if(y < minY){
                minY = y;
            }
            if(y > maxY){
                maxY = y;
            }
            fprintf(svg, "%lf,%lf ", x, y);
            sides++;
        }
    }
    fprintf(svg, "\" style=\"fill-opacity: 0; stroke: %s\"/>", colorBorder);
    drawPolLines(svg, polQueue, start, sides, d, e, colorFill, minX, maxX, minY, maxY);
}

bool freeAllCoordinates(void* polQueue){
    struct polygonQueue* aux = polQueue;
    void* coordinates;
    if(isEmpty(polQueue) == 0){
        do{
            if(aux->front > aux->size){
                aux->front = 0;
            }
            coordinates = getFirstCoordinates(polQueue);
            freeCoordinates(coordinates);
            aux->front++;
        } while(aux->front != aux->rear + 1);
        aux->front = aux->rear = 0;
        return true;
    }
    else{
        return false;
    }
}

void freePolQueue(void* polQueue){
    struct polygonQueue* aux = polQueue;
    void* coordinates;
    if(isEmpty(polQueue) == 0){
        do{
            if(aux->front > aux->size){
                aux->front = 0;
            }
            coordinates = getFirstCoordinates(polQueue);
            freeCoordinates(coordinates);
            aux->front++;
        } while(aux->front != aux->rear + 1);
    }
    free(aux->coordinates);
    free(aux);
}