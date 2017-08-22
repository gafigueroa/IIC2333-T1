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

#define WAITING 1
#define RUNNING 2
#define READY 3

/** @defgroup process Process
 *  This includes all the elements of process
 */

/**
 * @ingroup process
 */
struct Process {
    /**
     * The id of the process
     */
    int pid;
    
    /**
     * The name of the process
     */
    char name[NAME_SIZE];
    
    /**
     * Amount of times that are going to be processed
     */
    int size_times;
    
    /**
     * Array of ints representing the times that the process is going to be processing
     */
    int* times;
    
    /**
     * Position of the array representing the actual time
     */
    int actual_time;
    
    /**
     * When the process is going to start
     */
    int initial_time;
    
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
    unsigned int state:2;
    
};

typedef struct Process Process;

/**
 * @ingroup process
 * @brief Initialize a new process
 *
 * @param name The name of the process
 * @param priority The priority, takes values between 0 to 63, but mapped from 1 to 64
 *
 * @return The queue that has been initialized
 */
Process* init_process(char name[], int priority, int initial_time, int times_size, int* times);

/**
 * @ingroup process
 * @brief Free the memory allocated by the process
 *
 * @param process The process that's going to be freed
 */
void free_process(Process* process);

void free_process_array(Process** process_array, int size);

/**
 * @ingroup process
 * @brief Change the current state of the process
 *
 * @param process The process that's going to be changed
 * @param state The new state of the process
 */
void change_state(Process* process, int state);

/**
 * @ingroup process
 * @brief Prints the information of the process
 *
 * @param process The process that's going to be printed
 */
void print_process(Process* process);

#endif /* Process_h */
