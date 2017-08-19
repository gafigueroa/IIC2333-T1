//
//  main.c
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include "Scheduler.h"

void handler(int code){
    
}

int main(int argc, const char * argv[]) {
    signal(SIGTSTP, handler);

    return 0;
}
