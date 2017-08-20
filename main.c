//
//  main.c
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include "FileReader.h"
#include <string.h>

void handler(int code){

}

int main(int argc, const char * argv[]) {
    signal(SIGTSTP, handler);

    int array_size;
    Process** process_array = read_file("input.txt", &array_size);
    
    int i;
    for (i = 0; i < array_size; i++){
        print_process(process_array[i]);
    }
    
    
    return 0;
}
