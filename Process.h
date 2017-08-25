//
//  Process.h
//  T1
//
//  Created by Guillermo Figueroa and Juan Cortés on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa and Juan Cortés. All rights reserved.
//

#ifndef Process_h
#define Process_h

#include <stdio.h>

#define NAME_SIZE 256

#define WAITING 1
#define RUNNING 2
#define READY 3

int time;
int process_finished;


/** @defgroup process Process
 *  @brief Definition of Process and all the functions related
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
     * The amount of time that the process has been executing in the actual time
     */
    int time_executed;
        
    /**
     * The total amount of time that the process has been waiting
     */
    int total_time_waiting;

    /**
     * Position of the array representing the actual time
     */
    int actual_time;
    
    /**
     * Amount of times that the process has been chosen by the scheduler
     */
    int chosen;
    
    /**
     * Amount of times that the process has been blocked by the scheduler
     */
    int blocked;

    /**
     * When the process is going to start
     */
    int initial_time;

    /**
     * The priority, takes values between 0 to 63, but mapped from 1 to 64
     */
    unsigned int priority:6;
    

    /**
    * Qk value for roundrobin, on other cases is 0
    */
    int qk;

    /**
    * amount of time from when a request was submitted until the first response is executed.
    */
    int response_time;

    /**
    * amount of time to execute a particular process
    */
    int turnaround_time;

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

/**
 * @ingroup process
 * @brief Free the memory allocated by the array of processes
 *
 * @param process_array The array that's going to be freed
 * @param size The size of the array
 */
void free_process_array(Process** process_array, int size);

/**
 * @ingroup process
 * @brief Change the current state of the process
 *
 * @param process The process that's going to be changed
 * @param state The new state of the process
 */
int change_state(Process* process, int state);

/**
 * @ingroup process
 * @brief Prints the information of the process
 *
 * @param process The process that's going to be printed
 */
void print_process(Process* process);

/**
 * @ingroup process
 * Gets the amount of time that the process can stay in the scheduler according to the current time that's being processed. For example, in round robin, if we have
 * a quantum 6 and our current time is 10, the max will be 6.
 */
int max_current_time_process(Process* process);

#endif /* Process_h */
