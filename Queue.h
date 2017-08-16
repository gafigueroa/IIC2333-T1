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
    Process process;
    
    /**
     * The next node
     */
    struct node_queue* next;
    
};
typedef struct node_queue node_queue;

/**
 * @brief Declarations of the queue
 */
struct Queue {
    node_queue* head;
    void (*organize)(struct Queue*);
};
typedef struct Queue Queue;

/**
 * @brief Initialize the queue with the type
 * 
 * @param type The type of the queue:
 * 0: is for FCFS
 * 1: is for ROUNDROBIN
 * 2: is for PRIORITY
 */
Queue* init_queue(int type);



#endif /* Queue_h */
