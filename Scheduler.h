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

/**
 * @brief Declarations of the scheduler
 */
struct Scheduler {
    Queue* ready_queue;
    Queue* waiting_queue;
};
typedef struct Scheduler Scheduler;

/**
 * @brief Initialize the scheduler with the type provided
 *
 * @param type The type of the queue:
 * 0: is for FCFS
 * 1: is for ROUNDROBIN
 * 2: is for PRIORITY
 *
 * @return The scheduler that has been initalized
 */
Scheduler* init_scheduler(int type);

/**
 * @brief Schedule a process to be done
 *
 * @param scheduler The scheduler that's going to be used
 * @param process The process that's going to be scheduled
 *
 */
void schedule(Scheduler* scheduler, Process* process);

/**
 * @brief Simulate one unit of time
 *
 */
void tick(Scheduler* scheduler);

/**
 * @brief Free the memory allocated by the scheduler
 *
 * @param scheduler The scheduler that's going to be freed
 *
 */
void free_schedule(Scheduler* scheduler);

#endif /* Scheduler_h */
