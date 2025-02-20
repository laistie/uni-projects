#include "queue.h"

struct queue{
    int front, rear, size;
    CoordinatesArr coordinates;
};

Queue newQueue(int size){
    struct queue* new = (struct queue*)malloc(sizeof(struct queue));
    new->front = new->rear =  0;
    new->size = size + 1; //QUEUE ALWAYS HAS A REMAINING FREE SLOT
    new->coordinates = malloc(sizeof(void*) * size);
    return new;
}

bool isFull(Queue queue){
    struct queue* aux = queue;
    if((aux->rear + 1) % aux->size == aux->front){
        return true;
    }
    return false;
}

bool isEmpty(Queue queue){
    struct queue* aux = queue;
    if(aux->front == aux->rear){
        return true;
    }
    return false;
}

int getRear(Queue queue){
    struct queue* aux = queue;
    return aux->rear;
}

Coordinates getFirstCoordinates(Queue queue){
    struct queue* aux = queue;
    return aux->coordinates[aux->front + 1];
}

Coordinates getCoordinatesAtPos(Queue queue, int position){
    struct queue* aux = queue;
    return aux->coordinates[position];
}

void enqueue(Queue queue, double x, double y){
    if(isFull(queue)){
        printf("\nErro: nao foi possivel adicionar elemento, fila circular estatica cheia\n");
        return;
    }
    struct queue* aux = queue;
    aux->rear++;
    Coordinates coordinates = newCoordinates();
    insertCoordinates(coordinates, x, y);
    if(aux->rear > aux->size){ //ALREADY REACHED THE END OF QUEUE, BUT ITS CIRCULAR AND THERES SPACE LEFT
        aux->rear = 0;
        aux->coordinates[aux->rear] = coordinates;
    }
    else{
        aux->coordinates[aux->rear] = coordinates;  
    }
}

void dequeue(Queue queue, Coordinates coordinates){
    if(isEmpty(queue)){
        printf("\nErro ao remover elemento: fila circular estatica vazia\n");
        return;
    }
    struct queue* aux = queue;
    freeCoordinates(coordinates);
    aux->front++;
}

void drawPolLines(FILE* pSvg, int sides, double d, double e, char color[20], double minX, double maxX, double minY, double maxY){
    int numberLines = (maxY - minY) / d;
    for(int i = 1; i <= numberLines; i++){
        double x1 = minX;
        double y1 = minY + i * d;
        double x2 = maxX;
        double y2 = y1;
        fprintf(pSvg, "\n\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:%s; stroke-width:%.2lf\"/>", x1, y1, x2, y2, color, e);
    }
}

void pol(FILE* pSvg, Queue queue, int i, double d, double e, char colorBorder[20], char colorFill[20]){
    if(isEmpty(queue)){
        printf("Erro: não foi possível desenhar o polígono, fila circular estática vazia\n");
        return;
    }
    fprintf(pSvg, "\n\t<polygon points=\"");
    struct queue* aux = queue;
    Coordinates coordinates;
    int sides = 0;
    double x, y, minX, maxX, minY, maxY;
    if(aux->rear > aux->front){
        for(int i = aux->front + 1; i <= aux->rear; i++){
            coordinates = getCoordinatesAtPos(queue, i);
            x = getXCoord(coordinates);
            y = getYCoord(coordinates);
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
            fprintf(pSvg, "%lf,%lf ", x, y);
            sides++;
        }
    }
    else{
        for(int i = aux->front; i <= 100 - aux->front; i++){
            coordinates = getCoordinatesAtPos(queue, i);
            x = getXCoord(coordinates);
            y = getYCoord(coordinates);
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
            fprintf(pSvg, "%lf,%lf ", x, y);
            sides++;
        }
        for(int i = 0; i <= aux->rear; i++){
            coordinates = getCoordinatesAtPos(queue, i);
            x = getXCoord(coordinates);
            y = getYCoord(coordinates);
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
            fprintf(pSvg, "%lf,%lf ", x, y);
            sides++;
        }
    }
    fprintf(pSvg, "\" style=\"fill-opacity: 0; stroke: %s\"/>", colorBorder);
    drawPolLines(pSvg, sides, d, e, colorFill, minX, maxX, minY, maxY);
}

bool freeAllCoordinates(Queue queue){
    struct queue* aux = queue;
    void* coordinates;
    if(isEmpty(queue) == 0){
        do{
            if(aux->front > aux->size){
                aux->front = 0;
            }
            coordinates = getFirstCoordinates(queue);
            freeCoordinates(coordinates);
            aux->front++;
        } while(aux->front != aux->rear);
        aux->front = aux->rear = 0;
        return true;
    }
    return false;
}

void freeQueue(Queue queue){
    struct queue* aux = queue;
    if(!isEmpty(queue)){
        struct queue* aux = queue;
        Coordinates coordinates;
        do{
            if(aux->front > aux->size){
                aux->front = 0;
            }
            coordinates = getFirstCoordinates(queue);
            freeCoordinates(coordinates);
            aux->front++;
        } while(aux->front != aux->rear);
    }
    free(aux->coordinates);
    free(aux);
}