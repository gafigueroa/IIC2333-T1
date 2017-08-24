//
//  FileReader.c
//  T1
//
//  Created by Guillermo Figueroa and Juan Cortés on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa and Juan Cortés. All rights reserved.
//
#include "FileReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 1024

#define NAME 0
#define PRIORITY_PROCESS 1
#define INITIAL_TIME 2
#define TIMES_SIZE 3
#define TIMES 4

/**
 * @brief Reads the file until it finds all the information of a process, then returns that process
 */
Process* find_next_process(FILE* file){
    char ch = fgetc(file);
    if (ch == EOF || ch == '\0'){
        return NULL;
    }
    int i = 0;
    
    char pname[NAME_SIZE] = "";
    int ppriority = 0;
    int pinitial_time = 0;
    int ptimes_size = 0;
    
    
    int temp_time = 0;
    int* ptimes = NULL;
    
    int actual = 0;
    
    while (ch != '\n' && ch != '\0' && ch != EOF){
        if (ch == ' '){
            actual++;
            if (actual == TIMES){
                ptimes_size = 2*ptimes_size - 1;
                ptimes = malloc(sizeof(int)*ptimes_size);
            }
            if (actual > TIMES){
                int pos = actual - TIMES - 1;
                ptimes[pos] = temp_time;
                temp_time = 0;
            }
        }
        else {
            switch (actual) {
                case NAME:
                    pname[i] = ch;
                    i++;
                    break;
                    
                case PRIORITY_PROCESS:
                    ppriority = 10*ppriority + ch - '0';
                    break;
                    
                case INITIAL_TIME:
                    pinitial_time = 10*pinitial_time + ch - '0';
                    break;
                    
                case TIMES_SIZE:
                    ptimes_size = 10*ptimes_size + ch - '0';
                    break;
                    
                default:
                    temp_time = 10*temp_time + ch - '0';
                    break;
            }
        }
        
        ch = fgetc(file);
    }
    int pos = actual - TIMES;
    ptimes[pos] = temp_time;
    
    Process* process = init_process(pname, ppriority, pinitial_time, ptimes_size, ptimes);
    
    return process;
}

/**
 * @brief Returns the amount of lines that the file contain
 */
int amount_lines_file(const char* filename){
    int amount_lines = 1;
    FILE* file = fopen(filename, "r");
    int ch = 0;
    int prev_ch = 0;
    if (file == NULL){
        return 0;
    }
    while(!feof(file))
    {
        prev_ch = ch;
        ch = fgetc(file);
        if(ch == '\n')
        {
            amount_lines++;
        }
    }
    if (prev_ch == '\n'){
        amount_lines--;
    }
    fclose(file);
    
    return amount_lines;
}

Process** read_file(const char* filename, int* process_amount){
    int amount_process = amount_lines_file(filename);
    
    *process_amount = amount_process;

    Process** process_array = calloc(sizeof(Process*),amount_process);
    int i = 0;
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("File not found\n");
        exit(2);
    }
    else {
        Process* process;
        for (process = find_next_process(file); process != NULL; process = find_next_process(file)){
            process_array[i] = process;
            i++;
        }
        fclose(file);
    }
    
    return process_array;
}

Queue* read_file_queue(const char* filename, int* process_amount){
    int amount_process = amount_lines_file(filename);
    
    *process_amount = amount_process;
    
    Queue* queue = init_queue(DEFAULT);
    int i = 0;
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("File not found\n");
        exit(2);
    }
    else {
        Process* process;
        for (process = find_next_process(file); process != NULL; process = find_next_process(file)){
            enqueue_priority(queue, process, process->initial_time);
            i++;
        }
        fclose(file);
    }
    
    return queue;
}
