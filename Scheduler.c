//
//  Scheduler.c
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#include "Scheduler.h"
#include <stdlib.h>

int scheduler_time = 0;

Scheduler* init_scheduler(int type){
    Scheduler* scheduler = malloc(sizeof(Scheduler));
    scheduler -> ready_queue = init_queue(type);
    scheduler -> waiting_queue = init_queue(FCFS);
    
    return scheduler;
}

void free_schedule(Scheduler* scheduler){
    free_queue(scheduler -> ready_queue);
    free_queue(scheduler -> waiting_queue);
    free(scheduler);
}

/*
 * @brief Manage the current process being executed in the scheduler
 */
void tick_process_in_execution(Scheduler* scheduler){
    //Calcultes the amount of time that the process should be execute, 0 if there is no process
    int max_time_process = 0;
    if (scheduler -> process_in_execution != NULL){
        int pos = scheduler -> process_in_execution -> actual_time;
        max_time_process = scheduler -> process_in_execution -> times[pos];
    }
    
    //If the process needs to stay longer, keep it on the scheduler
    if (scheduler -> time_process < max_time_process){
        scheduler -> time_process++;
    }
    //In case that the process needs to stop
    else {
        if (scheduler -> process_in_execution != NULL){
            //change the state of the process to waiting and add it to the waiting queue
            change_state(scheduler -> process_in_execution, WAITING);
            enqueue(scheduler -> waiting_queue, scheduler -> process_in_execution);
        }
        scheduler -> time_process = 0;
        //If there is no element in the ready queue, then change the process to null (idle)
        if (scheduler -> ready_queue -> size == 0){
            scheduler -> process_in_execution = NULL;
            
        //If we have processes that can execute, execute one
        } else {
            //Get the next process
            Process* process_exec = dequeue(scheduler -> ready_queue);
            //Change the process state to running and add it as the process being executed
            change_state(process_exec, RUNNING);
            scheduler -> process_in_execution = process_exec;
        }
    }
}

void schedule(Scheduler* scheduler, Process* process){
    enqueue(scheduler -> ready_queue, process);
}

/*
 * @brief Manage the state of the processes in the queues. Moves elements from waiting to ready if possible
 */
void tick_update_queue(Scheduler* scheduler){
    
    //If the process has waited enough, this for each process
    while (minPriority(scheduler->waiting_queue) == scheduler_time){
        Process* process_ready = dequeue(scheduler -> waiting_queue);
        change_state(process_ready, READY);
        enqueue(scheduler -> ready_queue, process_ready);
    }
}

void tick(Scheduler* scheduler){
    scheduler_time++;
    
    //Manage the current process being executed
    tick_process_in_execution(scheduler);
    
    //Update the queues
    tick_update_queue(scheduler);

}
