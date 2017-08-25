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

void print_stats(){
    printf("\n----------------STATS---------------\n");
    printf("N° of finished process: %d\n", process_finished);
    printf("Simulation time: %d\n", time);
    printf("PROCESSES:\n");
    for(int i=0;i<array_size;i++){
      Process* proc = process_array[i];
      printf("Process name: %s\n", proc -> name);
      printf("   N° of times chosen: %d\n", proc -> chosen);
      printf("   N° of times blocked: %d\n", proc -> blocked);
      if(proc -> turnaround_time != -1){
        printf("   Turnaround time: %d\n", proc -> turnaround_time);
      }
      else{
        printf("   Turnaround time: the process didn't finish\n");
      }
      if(proc -> response_time != -1){
        printf("   Response time: %d\n", proc -> response_time);
      }
      else{
        printf("   response_time: The process never started\n");
      }
      printf("   Waiting time: %d\n", proc -> turnaround_time - total_executing_time(proc));
    }
    printf("--------------------------------------\n");
}

void handler(int code){
    print_stats();
    free_process_array(process_array, array_size);
    free_schedule(scheduler);
    free_queue(process_queue);
    exit(1);
}

int main(int argc, const char * argv[]) {
    process_finished = 0;
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


    for (time = 0; time < 200; time++){
        while (time == minPriority(process_queue)){
            Process* process_to_schedule = dequeue(process_queue);
            printf("Scheduler choose the process %s to execute on cpu\n", process_to_schedule -> name);
            schedule(scheduler, process_to_schedule);
        }
        tick(scheduler);
    }

    print_stats();
    free_process_array(process_array, array_size);
    free_schedule(scheduler);
    free_queue(process_queue);

    return 0;
}
