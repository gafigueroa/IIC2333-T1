//
//  Queue.c
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#include "Queue.h"
#include <stdlib.h>

//Different ways that the elements in the queue are going to be organized
void organize_fcfs(Queue*);
void organize_roundrobin(Queue*);
void organize_priority(Queue*);

int quantum = 3;

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

/**
 * @brief Initialize a new node with the process
 */
node_queue* init_node_queue(Process* process){
    node_queue* node = malloc(sizeof(node_queue));
    node -> process = process;
    node -> next = NULL;
    return node;
}

void enqueue(Queue* queue, Process* process){
    /*
     Agregar un elemento en la queue, es necesario volver a ordenarla despues de agregar el elemento
     */
}

Process* dequeue(Queue* queue){
    /*
     Obtener un elemento de la queue, es necesario volver a ordenarla despues de sacar el elemento
     */
    return NULL;
}

void organize_fcfs(Queue* queue){
    /*
     Este scheduler elige cada proceso en el orden en que entraron a la cola, sin importar la
     prioridad asociada a cada uno.
     */
}

void organize_roundrobin(Queue* queue){
    /*
     Este scheduler asigna un quantum Qk a un proceso con identificador k en función de su prioridad Pk.
     */
}

void organize_priority(Queue* queue){
    /*
     Este scheduler ordena los procesos por orden de prioridad. En caso de que dos o más procesos tengan igual prioridad,
     éstos se atienden según FCFS.
     */
}

void free_queue(Queue* queue){
    node_queue* node = queue -> head;
    node_queue* temp_node;
    while (node != NULL){
        free_process(node->process);
        temp_node = node;
        node = node -> next;
        free(temp_node);
    }
    free(queue);
}

void change_quantum(int new_quantum){
    quantum = new_quantum;
}




