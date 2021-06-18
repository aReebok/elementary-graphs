#include <stdio.h>
#include <stdlib.h>

struct Vertex {
    // int d;
    int value;
    int visited;
    struct Vertex *next;
};

typedef struct Vertex Vertex;

struct QNode{
    Vertex *s;
    struct QNode *next;
};

typedef struct QNode QNode;

struct Queue{
    QNode *first;     // dequeue here
    QNode *last;      // enqueue here
};

typedef struct Queue Queue;

int isEmpty(Queue *q){
    if (q->first == NULL) return 1; // is empty
    // puts("reached here LN 29-- not EMPTY");
    return 0; // is not empty
}

Queue *enqueue(Queue *q, Vertex *s){
    // puts S at the end of queue.
    QNode *newQNode = (QNode*)malloc(sizeof(QNode)); 
    newQNode->next = NULL;
    newQNode->s = s;

    if(isEmpty(q)) { // no items in queue...
        q->first = q->last = newQNode;
        return q;
    }

    q->last->next = newQNode; // add to the end of queue
    q->last = newQNode;       // change *last

    return q;
}

Vertex *dequeue(Queue *q){
    // removes and returns first item on queue.
    Vertex *s = q->first->s;
    q->first = q->first->next;
    return s;
}


Queue *initQueue(Queue *q){
    q->first = malloc(sizeof(QNode));
    q->last = malloc(sizeof(QNode));
    q->first = q->last = NULL;
    return q;
}

void printQueue(Queue *q){
    int counter = 1;
    // printf("reached here 66\n");
    while (!isEmpty(q)) {
        // printf("reached here 68\n");
        printf("hi----%d\n", counter);
        dequeue(q);
        counter++;
    }
}

int getMaxVert(const char *filename){
    // here we will look for the largest number in file 
    // this is how we can created our array for our adjacency list.
    int max = -1; 
    int int1; int int2;
    int1 = int2 = 0;
    FILE *input = fopen(filename, "r");     // r for read only

    if(input == NULL) {
        printf("Error: given file does not exist...\n"); 
        exit(-1);
    }

    while ( (fscanf(input, "%d", &int1) == 1) 
         && (fscanf(input, "%d", &int2) == 1) )  { 
        if(int1 > max) max = int1;
        if(int2 > max) max = int2;
    } 

    fclose(input);

    return max;
}

Vertex **makeAdjList(Vertex **arr, const char *f){
    // here we will put linkedlist into the adj list, 
    // and keep adding
    int int1, int2;
    FILE *input = fopen(f, "r");     // r for read only

    if(input == NULL) {
        printf("Error: given file does not exist...\n"); 
        exit(-1);
    }

    while ( (fscanf(input, "%d", &int1) == 1) 
         && (fscanf(input, "%d", &int2) == 1) )  { 
        // if(int1 > max) max = int1;
        // if(int2 > max) max = int2;
        Vertex *curr = (Vertex *)malloc(sizeof(Vertex));
        curr->value = int2;
        curr->next = NULL;
        curr->visited = 0; 

        if(arr[int1] == NULL) {
            // appoint head of the list 
            arr[int1] = curr;
            // printf("index %d is NULL\n", int1);

        } else {
            // or else traverse to the end of the list and add
            Vertex *tempPtr = arr[int1];
            while(tempPtr->next != NULL){
                tempPtr = tempPtr->next;
            }
            
            tempPtr->next = curr;
            // printf("index %d is NOT NULL\n", int1);
        }
    } 

    fclose(input);

    return arr;
}

void bfs(Vertex **adjList){
    // Vertex **tempAdjList = adjList;
    // int i = 0;
    // while(tempAdjList[])

}

int main() {
    /* // testing code-----------------------------------
    //init queue
    Queue *q1 = malloc(sizeof(Queue));
    q1 = initQueue(q1);
    printf("Is the queue empty?: %d \n", isEmpty(q1));
    printQueue(q1); // prints nothign because q is empty

    // adding verticies.
    Vertex * v1 = malloc(sizeof(Vertex));
    q1 = enqueue(q1, v1);
    printf("Is the queue empty?: %d \n", isEmpty(q1));
    Vertex * v2 = malloc(sizeof(Vertex));
    v1->next = v2;
    // q1 = enqueue(q1, v2);
    
    // printf("reached her/e 84\n");
    printQueue(q1); // prints hi once because len(q) = 1
    //----------------------------------------------- */
    char *filename = "input.txt";

    int arrLen = getMaxVert(filename);
    
    Vertex **adjArr = (Vertex **)malloc(arrLen*sizeof(Vertex *));

    for (int i = 0; i < arrLen; i++) {
        adjArr[i] = NULL;
    }
    
    // Vertex *arr[arrLen];
    // *arr = adjArr;

    adjArr = makeAdjList(adjArr, filename);
    bfs(adjArr);

    return 0;
}