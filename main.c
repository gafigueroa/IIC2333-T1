//
//  main.c
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "FileReader.h"
#include "Scheduler.h"
#include <string.h>


void handler(int code){
    printf("STATS:\nJuan: 1\nViserion: 0\nWhite walkers: 2\n");
    exit(0);
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
    int array_size;
    Process** process_array = read_file(argv[2], &array_size);
    
    //Initialize the scheduler depending on the type
    Scheduler* scheduler;
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
    for (time = 0; 1; time++){
        
    }
    
    return 0;
}
