#include <stdio.h>
#include <stdlib.h>

int ARRLEN = 0;

struct Vertex {
    // int d;
    int value;
    //int visited;
    struct Vertex *next;
};

typedef struct Vertex Vertex;

// 48 in 3 blocks: 28 allocs 25 frees

struct QNode{
    // int randomQNode; // 64 in 3 blocks: 28 allocs, 25 frees
    Vertex *s;
    struct QNode *next;
    // struct QNode *NONE;
    
};

typedef struct QNode QNode;


struct Queue{
    // int randomQ;    // 56 in 3 blocks: 28 alloc, 25 frees
    // Vertex *none;
    QNode *first;     // dequeue here
    QNode *last;      // enqueue here
};

typedef struct Queue Queue;

int isEmpty(Queue *q){
    if (q->first == NULL) return 1; // is empty
    return 0; // is not empty
}

Queue *enqueue(Queue *q, Vertex *s){
    // puts S at the end of queue.
    QNode *newQNode = (QNode*)malloc(sizeof(QNode)); 
    newQNode->next = NULL;
    newQNode->s = s;
    // printf("Enqueued %d\n", s->value);

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

    QNode *tempFirst = q->first; 
    q->first = q->first->next;

    // delete queue->first here...
    free(tempFirst); 

    return s;
}


Queue *initQueue(){
    // mallocs and initializers NULL values for queue
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->first = malloc(sizeof(QNode));
    q->last = malloc(sizeof(QNode));
    q->first = q->last = NULL;
    return q;
}

void printQueue(Queue *q){
    // print contents of queue for debugging/readability
    int counter = 1;
    while (!isEmpty(q)) {
        printf("%d\n", counter);
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

    // go through all values and compare to max
    while ((fscanf(input, "%d", &int1) == 1) 
         && (fscanf(input, "%d", &int2) == 1))  { 
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

        Vertex *curr = (Vertex *)malloc(sizeof(Vertex));
        curr->value = int2;
        curr->next = NULL;
        //curr->visited = 0; 
        int1--; // because array starts at 0.

        if(arr[int1] == NULL) {
            // appoint head of the list 
            arr[int1] = curr;
        } else {
            // or else traverse to the end of the list and add
            Vertex *tempPtr = arr[int1];
            while(tempPtr->next != NULL){
                tempPtr = tempPtr->next;
            }

            tempPtr->next = curr;
        }
    } 

    fclose(input);
    return arr;
}

/*
    These functions are freeing all allocated memory 
*/

/* helper function to free a linked list */
void freeLinkedList(Vertex *lst){
    Vertex *tempList = lst;
    while(lst != NULL){
        Vertex *tempList = lst;
        lst = lst->next;
        free(tempList);
    }
}

/* helper function to free adjacency list */
void freeAdjArrHelper(int i, Vertex **arr) {
    if(i == ARRLEN-1){
        // we want to free the linked list
        freeLinkedList(arr[i]);
    } else {
        // we want to free linked list 
        freeLinkedList(arr[i]);
        // recursive call the func on the next item on arr
        freeAdjArrHelper(++i, arr);
    }
}

void freeAdjArr(Vertex **arr){
    // takes in an adjacency list and frees every allocated memory
    int index = 0;
    freeAdjArrHelper(index, arr);
    free(arr);
}

void freeQueue(Queue *q){
    //takes in a queue and frees all elements? 
    while(q->first != NULL){
        QNode *tempQNode = q->first;
        freeLinkedList(tempQNode->s);
        free(tempQNode);
        q->first = q->first->next;
    }

    free(q->first);
    free(q->last);
    free(q);
}


void bfs(Vertex **adjList){
    // use ARRLEN to create an array that keeps track of 
    // visited verticies
    int visited[ARRLEN]; 

    for(int i = 0; i < ARRLEN; i++) {
        // init all verticies to unvisited status
        visited[i] = 0;
    }

    // create a queue, initialize it.
    Queue *q = initQueue();
    Queue *tempQ = q;
    
    // enqueue first item. 
    int s = 0;
    q = enqueue(q, adjList[s]);

    printf("%d ", s+1);
    visited[s] = 1;

    while(!isEmpty(q)){
        Vertex *currVert = dequeue(q);
        Vertex *tempCurr = currVert;

        if(s == 0) {
            tempCurr = currVert;
            s++;
        } else {
            tempCurr = adjList[currVert->value-1];  
        }

        while(tempCurr != NULL){
            if (!visited[tempCurr->value - 1]) {
                printf("%d ", tempCurr->value);
                q = enqueue(q, tempCurr);
                visited[tempCurr->value-1]  = 1;
            }

            tempCurr = tempCurr->next;
        }

        visited[currVert->value - 1] = 2;
    }

    puts("");
}

void dfsVisit(Vertex* currList, int *visited){
    // visited[i] ++;
 
    while(currList != NULL){
        int i = currList->value - 1;

        if(visited[i] == 0) {
            printf("%d ", currList->value);
            visited[i] = 2;
            printf("visitedLINE261[%d] = %d\n", i, visited[i]);

            dfsVisit(currList, visited);
        }

        currList = currList->next;

    }
    // visited[i] = 2;
}


void dfs(Vertex **adjList){
    // use ARRLEN to create an array that keeps track of 
    // visited verticies
    int visited[ARRLEN]; 
    for(int i = 0; i < ARRLEN; i++) {
        // init all verticies to unvisited status
        visited[i] = 0;
    }

    for(int i = 0; i < ARRLEN; i++) {
        if(visited[i] == 0){
            // printf();
            visited[i] = 2;
            printf("visited[%d]LINE286 = %d\n", i, visited[i]);

            printf("%d ", i+1);
            dfsVisit(adjList[i], visited);
        }
    }
}







int main() {
    /* 
    // queue testing code-----------------------------------
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

    char *filename = "input";

    ARRLEN = getMaxVert(filename);
    Vertex **adjArr = (Vertex **)malloc(ARRLEN*sizeof(Vertex *));

    for (int i = 0; i < ARRLEN; i++) {
        adjArr[i] = NULL;
        // printf("%d\n", i);
    }
    
    adjArr = makeAdjList(adjArr, filename);
    bfs(adjArr);
    dfs(adjArr);

    freeAdjArr(adjArr);

    // int SIZEPLS = 10;
    // printf("size of SIZEPLS: %ld\n", sizeof(SIZEPLS));
    
    // dfs(adjA a
    // need to free all memeory ..
    // freeAdjArr(adjArr);

    return 0;
}