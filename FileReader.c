//
//  FileReader.c
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/19/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#include "FileReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 1024

#define NAME 0
#define PRIORITY 1
#define INITIAL_TIME 2
#define TIMES_SIZE 3
#define TIMES 4

Process* process_from_line(char* line){
    int i;
    char empty_char = '\0';
    
    char pname[NAME_SIZE] = "";
    int ppriority = 0;
    int pinitial_time = 0;
    int ptimes_size = 0;
    
    int temp_time = 0;
    int* ptimes = NULL;
    
    int actual = 0;
    
    for (i = 0; i < LINE_SIZE && line[i] != empty_char && line[i] != '\n'; i++){
        if (line[i] == ' '){
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
                    pname[i] = line[i];
                    break;
                    
                case PRIORITY:
                    ppriority = 10*ppriority + line[i] - '0';
                    break;
                    
                case INITIAL_TIME:
                    pinitial_time = 10*pinitial_time + line[i] - '0';
                    break;
                    
                case TIMES_SIZE:
                    ptimes_size = 10*ptimes_size + line[i] - '0';
                    break;

                default:
                    temp_time = 10*temp_time + line[i] - '0';
                    break;
            }
        }
    }
    int pos = actual - TIMES;
    ptimes[pos] = temp_time;
    
    Process* process = init_process(pname, ppriority, pinitial_time, ptimes_size, ptimes);
    
    return process;
}

int amount_lines_file(char* filename){
    int amount_lines = 1;
    FILE* file = fopen(filename, "r");
    int ch = 0;
    if (file == NULL){
        return 0;
    }
    while(!feof(file))
    {
        ch = fgetc(file);
        if(ch == '\n')
        {
            amount_lines++;
        }
    }
    
    fclose(file);
    
    return amount_lines;
}

Process** read_file(char* filename, int* process_amount){
    int amount_process = amount_lines_file(filename);
    
    *process_amount = amount_process;

    Process** process_array = calloc(sizeof(Process*),amount_process);
    int i = 0;
    
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        
    }
    else {
        char line[LINE_SIZE];
        while (fgets(line, sizeof(line), file)) {
            process_array[i] = process_from_line(line);
            i += 1;
        }
        
        fclose(file);
    }
    
    return process_array;
}
