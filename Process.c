//
//  Process.c
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#include "Process.h"
#include <stdlib.h>

int next_pid = 0;

Process* init_process(char name[], int priority, int initial_time, int times_size, int* times){
    Process* process = malloc(sizeof(Process));
    
    process -> pid = next_pid;
    next_pid += 1;
    
    int i;
    for (i = 0; i < NAME_SIZE; i++){
        process -> name[i] = name[i];
    }
    
    process -> size_times = times_size;
    process -> times = times;
    
    process -> actual_time = 0;
    
    process -> initial_time = initial_time;
    
    process -> priority = priority;
    
    process -> state = READY;
    
    return process;
}

/*
 * 1 if the change was succesfull
 * 0 otherwise
 */
int change_state(Process* process, int state){
    switch (state) {
        case RUNNING:
            process -> state = RUNNING;
            return 1;
            
        case WAITING:
            if (process -> state == RUNNING){
                process -> actual_time++;
                if (process -> actual_time >= process -> size_times){
                    printf("Process finished\n");
                    return 0;
                }
                process -> state = WAITING;
            } else {
                printf("Error on changing the state to waiting by the process:\n");
                return 0;
            }
            return 1;
            
        case READY:
            if (process -> state == WAITING){
                process -> actual_time++;
                process -> state = READY;
                return 1;
            } else {
                printf("Error on changing the state to ready by the process:\n");
                return 0;
            }
            break;
            
        default:
            return 0;
    }
}

int max_current_time_process(Process* process){
    if (process){
        int pos = process -> actual_time;
        int max_time = process -> times[pos];
        return max_time;
    }
    return 0;
}

void print_process(Process* process){
    printf("going to print\n");
    if (process == NULL){
        printf("This process is empty\n");
        return;
    }
    printf("PID: %d\nNAME: %s\nINITIAL_TIME: %d\nPRIORITY: %d\nSTATE: %d\nSIZE TIMES: %d\n",
           process->pid,
           process->name,
           process->initial_time,
           process->priority,
           process->state,
           process->size_times);
    int i;
    for (i = 0; i < process -> size_times; i++){
        printf("TIME%d: %d\n", i, process->times[i]);
    }
    printf("\n");
}

void free_process(Process* process){
    free(process);
}

void free_process_array(Process** process_array, int size){
    int i;
    for (i = 0; i < size; i++){
        free_process(process_array[i]);
    }
    free(process_array);
}
