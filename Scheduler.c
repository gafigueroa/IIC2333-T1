//
//  Scheduler.c
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#include "Scheduler.h"
#include <stdlib.h>


Scheduler* init_scheduling(int type){
    Scheduler* scheduler = malloc(sizeof(Scheduler));
    scheduler -> ready_queue = init_queue(type);
    scheduler -> waiting_queue = init_queue(FCFS);
    
    return scheduler;
}

void free_schedule(Scheduler* scheduler){
    free(scheduler -> ready_queue);
    free(scheduler -> waiting_queue);
    free(scheduler);
}
