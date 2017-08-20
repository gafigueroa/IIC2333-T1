//
//  FileReader.h
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/19/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#ifndef FileReader_h
#define FileReader_h

#include "Process.h"
#include <stdio.h>

Process** read_file(char* filename, int* process_amount);

#endif /* FileReader_h */
