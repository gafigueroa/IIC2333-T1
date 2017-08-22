//
//  Queue.h
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#ifndef Queue_h
#define Queue_h


#include <stdio.h>
#include "Process.h"

#define FCFS 0
#define ROUNDROBIN 1
#define PRIORITY 2

/**
 * @brief Declarations of the nodes of the queue
 */
struct node_queue {
    /**
     * The process stored in the node of the queue
     */
    Process* process;

    /**
     * Priority of the process calculated according to it's type
     */
    int priority;

};
typedef struct node_queue node_queue;

/**
 * @brief Declarations of the queue
 *
 * This struct defines how the queue works,
 * the method organize will depend of the type of the queue
 */
struct Queue {
    /**
    * Array of node_queue's
    */
    node_queue** node_array;

    /**
     * @brief Calculate the priority of the node depending on the scheduler type
     * @param Number from which it should calculate the priority:
     * @return Returns the calculated priority
     */
    int (*node_priority)(int);

    /*
    * Amount of elements in the node_array
    */
    int size;
};
typedef struct Queue Queue;

/**
 * @brief Initialize the queue with the type
 *
 * @param type The type of the queue:
 * 0: is for FCFS
 * 1: is for ROUNDROBIN
 * 2: is for PRIORITY
 *
 * @return The queue that has been initialized
 */
Queue* init_queue(int type);

/**
 * @brief Push an element to the queue
 *
 * @param queue The queue where the element is going to be added
 * @param process The process that's going to be added to the queue
 */
void enqueue(Queue* queue, Process* process);

/**
 * @brief Gets the next element from the queue
 *
 * @param queue The queue from where we are going to get the element
 *
 * @return The next process from the queue
 */
Process* dequeue(Queue* queue);

/**
 * @brief Free the memory allocated by the queue
 *
 * @param queue The queue that's going to be freed
 */
void free_queue(Queue* queue);

/**
 * @brief Change the value of the quantum for round robin
 *
 * @param new_quantum The new value of the quantum
 */
void change_quantum(int new_quantum);


#endif /* Queue_h */
