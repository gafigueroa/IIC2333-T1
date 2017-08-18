//
//  Scheduler.c
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#include "Scheduler.h"
#include <stdlib.h>


Process scheduling_fcfs(Queue* queue);
Process scheduling_roundrobin(Queue* queue);
Process scheduling_priority(Queue* queue);

Scheduler* init_scheduling(int type){
    Scheduler* scheduler = malloc(sizeof(Scheduler));
    scheduler -> queue = init_queue(type);
    
    if (type == FCFS){
        scheduler -> scheduling = scheduling_fcfs;
    }
    else if (type == ROUNDROBIN){
        scheduler -> scheduling = scheduling_roundrobin;
    }
    else if (type == PRIORITY){
        scheduler -> scheduling = scheduling_priority;
    }
    
    return scheduler;
}

void free_schedule(Scheduler* scheduler){
    free(scheduler -> queue);
    free(scheduler);
}
