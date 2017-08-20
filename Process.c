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

void free_process(Process* process){
    free(process);
}

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
    
    process -> state = WAITING;
    
    return process;
}

void print_process(Process* process){
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
