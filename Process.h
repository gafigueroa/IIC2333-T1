//
//  Process.h
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#ifndef Process_h
#define Process_h

#include <stdio.h>

#define NAME_SIZE 256

struct Process {
    /**
     * The id of the process
     */
    int pid;
    
    /**
     * The name of the process
     */
    char name[NAME_SIZE];
    
    
    //Manage times
    
    /**
     * The priority, takes values between 0 to 63, but mapped from 1 to 64
     */
    int priority:6;
    
    /**
     * The state of the process:
     * 0: NULL
     * 1: Waiting
     * 2: Running
     * 3: Ready
     */
    int state:2;
    
};

typedef struct Process Process;

/**
 * @brief Initialize a new process
 *
 * @param pid The id of the process
 * @param name The name of the process
 * @param priority The priority, takes values between 0 to 63, but mapped from 1 to 64
 *
 * @return The queue that has been initialized
 */
Process* init_process(int pid, char* name, int times_size, int* times, int priority);

/**
 * @brief Free the memory allocated by the process
 *
 * @param process The process that's going to be freed
 */
void free_process(Process* process);

#endif /* Process_h */
