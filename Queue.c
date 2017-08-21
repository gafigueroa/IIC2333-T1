//
//  Queue.c
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#include "Queue.h"
#include <stdlib.h>

#define LEFT(x) 2*x
#define RIGHT(x) 2*x + 1
#define PARENT(x) x/2
//Different ways that the elements in the queue are going to be organized
void organize_fcfs(Queue*);
void organize_roundrobin(Queue*);
void organize_priority(Queue*);

int QUEUE_LENGTH = 50;
int quantum = 3;


Queue* init_queue(int type){
    Queue* queue = malloc(sizeof(Queue));
    //queue -> head = NULL;
    if (type == FCFS){
        queue -> organize = organize_fcfs;
    }
    else if (type == ROUNDROBIN){
        queue -> organize = organize_roundrobin;
    }
    else if (type == PRIORITY){
        queue -> organize = organize_priority;
    }
    queue -> size = 1;
    queue -> node_array[0] = NULL;
    queue -> node_array = malloc(QUEUE_LENGTH * sizeof(node_queue*));
    return queue;
}


/**
 * @brief Initialize a new node with the process
 */
node_queue* init_node_queue(Process* process){
    node_queue* node = malloc(sizeof(node_queue));
    node -> process = process;
    return node;
}


/**
 * @brief Exchange position of two nodes on the node_array
 */
void swap(node_queue *n1, node_queue *n2) {
    node_queue temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}


/**
 * @brief Doubles de length of the node_array
 */
void increaseQueue(Queue *queue){
    QUEUE_LENGTH = QUEUE_LENGTH * 2;
    queue -> node_array = realloc(queue -> node_array, QUEUE_LENGTH * sizeof(node_queue*));
}

/**
 * @brief Add a process to the queue
 */
void enqueue(Queue* queue, Process* process){
     node_queue* node = init_node_queue(process);
     int i = (queue->size)++ ;
     if(queue->size > QUEUE_LENGTH){
       increaseQueue(queue);
     }
     while(i && node -> process -> priority < queue -> node_array[PARENT(i)] -> process -> priority) {
         queue -> node_array[i] = queue -> node_array[PARENT(i)];
         i = PARENT(i) ;
     }
     queue -> node_array[i] = node ;
}

/**
* @brief Make sure the min heap property isn't violated
*/
void minHeapify(Queue* queue, int i){
    int l = LEFT(i);
    int r = RIGHT(i);
    int min = i;
    if(l <= queue -> size && queue -> node_array[l] -> process -> priority <
      queue -> node_array[min] -> process -> priority){
        min = l;
      }
    if(r <= queue -> size && queue -> node_array[r] -> process -> priority <
      queue -> node_array[min] -> process -> priority){
        min = r;
      }
    if(min != i){
      swap(queue -> node_array[min], queue -> node_array[i]);
      minHeapify(queue, min);
    }
}

/**
* @brief Pop and return the process with max priority in the queue
*/
Process* dequeue(Queue* queue){
    if(queue -> size < 1){
      return NULL
    }
    node_queue* minNode = queue -> node_array[1];
    *queue -> node_array[1] = *queue -> node_array[queue -> size];
    queue -> size--;
    minHeapify(queue, 1);
    return minNode -> process;
}


void organize_fcfs(Queue* queue){
    /*
     Este scheduler elige cada proceso en el orden en que entraron a la cola, sin importar la
     prioridad asociada a cada uno.
     */
}

void organize_roundrobin(Queue* queue){
    /*
     Este scheduler asigna un quantum Qk a un proceso con identificador k en función de su prioridad Pk.
     */

}

void organize_priority(Queue* queue){
    /*
     Este scheduler ordena los procesos por orden de prioridad. En caso de que dos o más procesos tengan igual prioridad,
     éstos se atienden según FCFS.
     */
}

void free_queue(Queue* queue){
    for(int i=0;i<queue->size;i++){
      free_process(queue -> node_array[i] -> process);
    }
    free(queue -> node_array);
    free(queue);
}

void change_quantum(int new_quantum){
    quantum = new_quantum;
}
