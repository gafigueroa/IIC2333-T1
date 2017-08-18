//
//  Process.c
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#include "Process.h"
#include <stdlib.h>


void free_process(Process* process){
    free(process);
}
