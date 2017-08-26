//
//  Queue.h
//  T1
//
//  Created by Guillermo Figueroa and Juan Cortés on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa and Juan Cortés. All rights reserved.
//

#ifndef Queue_h
#define Queue_h


#include <stdio.h>
#include "Process.h"

#define FCFS 0
#define ROUNDROBIN 1
#define PRIORITY 2
#define DEFAULT 3

/** @defgroup queue Queue
 *  @brief Queue definition and all the functions on how to use it
 */


/**
 * @ingroup queue
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
 * @ingroup queue
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
    
    /*
     * The type of the queue
     */
    int type;
};
typedef struct Queue Queue;

/**
 * @ingroup queue
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
 * @ingroup queue
 * @brief Initialize the queue with the type. Then push all the elements of the array
 *
 * @param type The type of the queue:
 * 0: is for FCFS
 * 1: is for ROUNDROBIN
 * 2: is for PRIORITY
 * @param process_array Array of processes that are going to be added to the queue
 * @param size The size of the array of processes
 *
 * @return The queue that has been initialized
 */
Queue* init_queue_array_process(int type, Process** process_array, int size);

/**
 * @ingroup queue
 * @brief Push an element to the queue
 *
 * @param queue The queue where the element is going to be added
 * @param process The process that's going to be added to the queue
 */
void enqueue(Queue* queue, Process* process);

/**
 * @ingroup queue
 * @brief Push an element to the queue with the desired priority
 *
 * @param queue The queue where the element is going to be added
 * @param process The process that's going to be added to the queue
 * @param priority The priority we want to assign
 */
void enqueue_priority(Queue* queue, Process* process, int priority);

/**
 * @ingroup queue
 * @brief Gets the next element from the queue
 *
 * @param queue The queue from where we are going to get the element
 *
 * @return The next process from the queue
 */
Process* dequeue(Queue* queue);

/**
 * @ingroup queue
 * @brief Free the memory allocated by the queue
 *
 * @param queue The queue that's going to be freed
 */
void free_queue(Queue* queue);

/**
 * @ingroup queue
 * @brief Calculates the minimum priority stored in the queue
 */
int minPriority(Queue* queue);

/**
 * @ingroup queue
 * @brief Change the value of the quantum for round robin
 *
 * @param new_quantum The new value of the quantum
 */
void change_quantum(int new_quantum);


#endif /* Queue_h */
