//
//  Scheduler.c
//  T1
//
//  Created by Guillermo Figueroa and Juan Cortés on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa and Juan Cortés. All rights reserved.
//

#include "Scheduler.h"
#include <stdlib.h>

int scheduler_time = 0;

Scheduler* init_scheduler(int type){
    Scheduler* scheduler = malloc(sizeof(Scheduler));
    scheduler -> ready_queue = init_queue(type);
    scheduler -> waiting_queue = init_queue(DEFAULT);
    scheduler -> process_in_execution = NULL;
    scheduler -> time_process = 0;
    return scheduler;
}

void free_schedule(Scheduler* scheduler){
    free_queue(scheduler -> ready_queue);
    free_queue(scheduler -> waiting_queue);
    free(scheduler);
}

int actual_max_time(Process* process){
    int pos = process -> actual_time;
    int max_actual_time = process -> times[pos];
    
    return max_actual_time;
}

int get_max_time_process(Scheduler* scheduler, Process* process){
    int pos = process -> actual_time;
    int max_actual_time = process -> times[pos];
    
    int initial_time_this_round = process -> time_executed - scheduler -> time_process;
    int max_time_left = max_actual_time - initial_time_this_round;
    
    if (process -> qk < max_time_left){
        return initial_time_this_round + process -> qk;
    }
    return max_actual_time;
}


/*
 * @brief Manage the current process being executed in the scheduler
 */
void tick_process_in_execution(Scheduler* scheduler){
    //Calcultes the amount of time that the process should be execute, 0 if there is no process
    int max_time_process = 0;
    if (scheduler -> process_in_execution){
        int pos = scheduler -> process_in_execution -> actual_time;
        max_time_process = scheduler -> process_in_execution -> times[pos];
    }else{
        printf("IDLE\n");
    }
    //If the process needs to stay longer, keep it on the scheduler
    if (scheduler -> time_process < max_time_process){
        scheduler -> time_process++;
        printf("Process: %s is RUNNING\n", scheduler -> process_in_execution -> name);
    }
    //In case that the process needs to stop
    else {
        if (scheduler -> process_in_execution != NULL){
            //change the state of the process to waiting and add it to the waiting queue
            if (change_state(scheduler -> process_in_execution, WAITING)){
                int pos = scheduler -> process_in_execution -> actual_time;
                int priority = scheduler_time + scheduler -> process_in_execution -> times[pos];
                printf("Process: %s is changing to WAITING with priority: %d\n", scheduler -> process_in_execution -> name, priority);
                enqueue_priority(scheduler -> waiting_queue, scheduler -> process_in_execution, priority);
            }
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

void tick_round(Scheduler* scheduler){
    if (!scheduler->process_in_execution){
        printf("IDLE\n");
    } else {
        //How much time the process has been executed
        int time_executed_process = scheduler -> process_in_execution -> time_executed;
        //How much time the process has to execute
        int time_to_execute = get_max_time_process(scheduler, scheduler->process_in_execution);
        if (time_executed_process < time_to_execute){
            scheduler -> time_process++;
            scheduler -> process_in_execution -> time_executed++;
            printf("Process: %s is RUNNING\n", scheduler -> process_in_execution -> name);
        } else {
            if (time_executed_process < actual_max_time(scheduler->process_in_execution)){
                if (change_state(scheduler -> process_in_execution,READY)){
                    enqueue(scheduler->ready_queue, scheduler->process_in_execution);
                    printf("Process: %s is changing to READY\n", scheduler -> process_in_execution -> name);
                }
            }
            else{
                //change the state of the process to waiting and add it to the waiting queue
                if (change_state(scheduler -> process_in_execution, WAITING)){
                    scheduler -> process_in_execution -> time_executed = 0;
                    int pos = scheduler -> process_in_execution -> actual_time;
                    int priority = scheduler_time + scheduler -> process_in_execution -> times[pos];
                    printf("Process: %s is changing to WAITING with priority: %d\n", scheduler -> process_in_execution -> name, priority);
                    enqueue_priority(scheduler -> waiting_queue, scheduler -> process_in_execution, priority);
                }
            }
            scheduler -> time_process = 0;
            scheduler -> process_in_execution = NULL;
        }
    }
    
    if (!scheduler -> process_in_execution){
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

/*
 * @brief Manage the current process being executed in the scheduler when roundrobin
 */
void tick_round_robin(Scheduler* scheduler){
    //If the process needs to stay longer, keep it on the scheduler
    if (scheduler -> process_in_execution){
        int time_executed_process = scheduler -> process_in_execution -> time_executed;
        int time_to_execute = get_max_time_process(scheduler, scheduler->process_in_execution);
        if (time_executed_process < time_to_execute){
            scheduler -> time_process++;
            scheduler -> process_in_execution -> time_executed++;
            printf("Process: %s is RUNNING\n", scheduler -> process_in_execution -> name);
        }
        else if (time_executed_process == time_to_execute){
            if (time_executed_process < actual_max_time(scheduler->process_in_execution)){
                if (change_state(scheduler -> process_in_execution,READY)){
                    enqueue(scheduler->ready_queue, scheduler->process_in_execution);
                }
            }else{
                //change the state of the process to waiting and add it to the waiting queue
                if (change_state(scheduler -> process_in_execution, WAITING)){
                    scheduler -> process_in_execution -> time_executed = 0;
                    int pos = scheduler -> process_in_execution -> actual_time;
                    int priority = scheduler_time + scheduler -> process_in_execution -> times[pos];
                    printf("Process: %s is changing to WAITING with priority: %d\n", scheduler -> process_in_execution -> name, priority);
                    enqueue_priority(scheduler -> waiting_queue, scheduler -> process_in_execution, priority);
                }
            }
            scheduler -> time_process = 0;
            scheduler -> process_in_execution = NULL;
            printf("IDLE\n");
            
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
    //In case that the process needs to stop
    else {
        printf("IDLE\n");
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
        if (change_state(process_ready, READY)){
            enqueue(scheduler -> ready_queue, process_ready);
        }
    }
}

/**
 * @brief Simulate one unit of time
 */
void tick(Scheduler* scheduler){
    printf("T:%d | ", scheduler_time);
    
    //Update the queues
    tick_update_queue(scheduler);
    
    //Manage the current process being executed
    if (scheduler -> ready_queue -> type == ROUNDROBIN){
        tick_round(scheduler);
    } else {
        tick_process_in_execution(scheduler);
    }
    scheduler_time++;

}
