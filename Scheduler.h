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

/** @defgroup scheduler Scheduler
 *  This includes all the elements of the scheduler
 */


/**
 * @ingroup scheduler
 * @brief Declarations of the scheduler
 */
struct Scheduler {
    /**
     * The processes that are ready and can be executed
     */
    Queue* ready_queue;
    
    /**
     * The processes that are waiting. The priority corresponds to when the element needs to leave the queue
     */
    Queue* waiting_queue;
    
    /**
     * The process that's being executed
     */
    Process* process_in_execution;
    
    /**
     * The amount of time that the process has been being executed
     */
    int time_process;
};
typedef struct Scheduler Scheduler;

/**
 * @ingroup scheduler
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
 * @ingroup scheduler
 * @brief Schedule a process to be done
 *
 * @param scheduler The scheduler that's going to be used
 * @param process The process that's going to be scheduled
 *
 */
void schedule(Scheduler* scheduler, Process* process);

/**
 * @ingroup scheduler
 * @brief Simulate one unit of time
 *
 */
void tick(Scheduler* scheduler);

/**
 * @ingroup scheduler
 * @brief Free the memory allocated by the scheduler
 *
 * @param scheduler The scheduler that's going to be freed
 *
 */
void free_schedule(Scheduler* scheduler);

#endif /* Scheduler_h */
