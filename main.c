//
//  main.c
//  T1
//
//  Created by Guillermo Figueroa and Juan Cortés on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa and Juan Cortés. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "FileReader.h"
#include "Scheduler.h"
#include <string.h>


int array_size;
Process** process_array;
Scheduler* scheduler;
Queue* process_queue;

void handler(int code){
    free_process_array(process_array, array_size);
    free_schedule(scheduler);
    free_queue(process_queue);
    exit(1);
}

int main(int argc, const char * argv[]) {
    signal(SIGINT, handler);

    //If the amount of arguments is not enough
    if (argc <= 2){
        printf("How to use the program:\n./simulator <type of scheduler> <filename> [<quantum>]\n");
        return 1;
    }
    
    //If we have a value for the quantum, we need to set it
    if (argc == 4){
        int new_quantum = atoi(argv[3]);
        change_quantum(new_quantum);
    }
    
    //Read the file and creates the processes
    process_array = read_file(argv[2], &array_size);
    process_queue = init_queue_array_process(DEFAULT, process_array, array_size);
    
    //Initialize the scheduler depending on the type
    if (!strcmp(argv[1], "fcfs")){
        scheduler = init_scheduler(FCFS);
    }
    else if (!strcmp(argv[1], "roundrobin")){
        scheduler = init_scheduler(ROUNDROBIN);
    }
    else if (!strcmp(argv[1], "priority")){
        scheduler = init_scheduler(PRIORITY);
    } else {
        printf("Type of sheduler incorrect. Please choose between fcfs, roundrobin and priority");
    }
    
    
    int time;
    for (time = 0; time < 200; time++){
        while (time == minPriority(process_queue)){
            Process* process_to_schedule = dequeue(process_queue);
            schedule(scheduler, process_to_schedule);
        }
        tick(scheduler);
    }
    

    free_process_array(process_array, array_size);
    free_schedule(scheduler);
    free_queue(process_queue);
    
    return 0;
}
