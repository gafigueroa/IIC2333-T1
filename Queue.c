//
//  Queue.c
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#include "Queue.h"
#include <stdlib.h>

void organize_fcfs(Queue*);
void organize_roundrobin(Queue*);
void organize_priority(Queue*);

Queue* init_queue(int type){
    Queue* queue = malloc(sizeof(Queue));
    queue -> head = NULL;
    if (type == FCFS){
        queue -> organize = organize_fcfs;
    }
    else if (type == ROUNDROBIN){
        queue -> organize = organize_roundrobin;
    }
    else if (type == PRIORITY){
        queue -> organize = organize_priority;
    }
    return queue;
}
