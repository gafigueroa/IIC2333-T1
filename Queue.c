//
//  Queue.c
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#include "Queue.h"
#include <stdlib.h>
#include <math.h>

#define LEFT(x) 2*x
#define RIGHT(x) 2*x + 1
#define PARENT(x) x/2
//Different ways that the elements in the queue are going to be organized
void organize_fcfs(Queue*);
void organize_roundrobin(Queue*);
void organize_priority(Queue*);

int QUEUE_LENGTH = 50;
int FCFS_PRIORITY = -1;
int quantum = 3;


/**
* @brief Priority based on FIFO
*/
int calculate_fcfs(int process_priority){
    FCFS_PRIORITY++;
    return FCFS_PRIORITY;
}

/**
* @brief Calculate the priority based on round robin
*/
int calculate_roundrobin(int process_priority){
    int new_priority = process_priority * quantum;
    int exponent = process_priority / quantum;
    double dblExponent = (double)exponent;
    return (int)(new_priority + pow(-1.0, dblExponent) * process_priority);
}

/**
* @brief Use the process priority for the node_queue
*/
int calculate_priority(int process_priority){
    return process_priority;
}

/**
 * @brief Initialize a new node with the process
 */
node_queue* init_node_queue(Process* process){
    node_queue* node = malloc(sizeof(node_queue));
    node -> process = process;
    node -> priority = 0;
    return node;
}


Queue* init_queue(int type){
    Queue* queue = malloc(sizeof(Queue));
    if (type == FCFS){
        queue -> node_priority = calculate_fcfs;
    }
    else if (type == ROUNDROBIN){
        queue -> node_priority = calculate_roundrobin;
    }
    else if (type == PRIORITY){
        queue -> node_priority = calculate_priority;
    }
    queue -> node_array[0] = NULL;
    queue -> size = 0;
    queue -> node_array = malloc(QUEUE_LENGTH * sizeof(node_queue*));
    return queue;
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
     node -> priority = queue -> node_priority(process -> priority);
     while(i && node -> priority < queue -> node_array[PARENT(i)] -> priority) {
         queue -> node_array[i] = queue -> node_array[PARENT(i)];
         i = PARENT(i) ;
     }
     queue -> node_array[i] = node;
}

/**
* @brief Make sure the min heap property isn't violated
*/
void minHeapify(Queue* queue, int i){
    int l = LEFT(i);
    int r = RIGHT(i);
    int min = i;
    if(l <= queue -> size && queue -> node_array[l] -> priority >
      queue -> node_array[min] -> priority){
        min = l;
      }
    if(r <= queue -> size && queue -> node_array[r] -> priority <
      queue -> node_array[min] -> priority){
        min = r;
      }
    if(min != i){
      swap(queue -> node_array[min], queue -> node_array[i]);
      minHeapify(queue, min);
    }
}

int minPriority(Queue* queue){
  if(queue -> size < 1){
    return -1;
  }
  return queue -> node_array[1] -> priority;
}

/**
* @brief Pop and return the process with min priority in the queue
*/
Process* dequeue(Queue* queue){
    if(queue -> size < 1){
      return NULL;
    }
    node_queue* minNode = queue -> node_array[1];
    *queue -> node_array[1] = *queue -> node_array[queue -> size];
    queue -> size--;
    minHeapify(queue, 1);
    return minNode -> process;
}

void free_node_queue(node_queue* node){
    free_process(node -> process);
    free(node);
}

void free_queue(Queue* queue){
    for(int i=0;i<queue->size;i++){
      free_node_queue(queue -> node_array[i]);
    }
    free(queue -> node_array);
    free(queue);
}

void change_quantum(int new_quantum){
    quantum = new_quantum;
}
