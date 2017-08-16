//
//  Scheduler.h
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#ifndef Scheduler_h
#define Scheduler_h

#include <stdio.h>
#include "Queue.h"

#define QUANTUM 5

/**
 * @brief Declarations of the scheduler
 */
struct Scheduler {
    Queue* queue;
    Process (*scheduling)(Queue*);
};
typedef struct Scheduler Scheduler;

/**
 * @brief Initialize the scheduler with the type provided
 *
 * @param type The type of the queue:
 * 0: is for FCFS
 * 1: is for ROUNDROBIN
 * 2: is for PRIORITY
 */
Scheduler* init_scheduler(int type);


#endif /* Scheduler_h */
