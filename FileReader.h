//
//  FileReader.h
//  IIC2333-T0
//
//  Created by Guillermo Figueroa on 8/19/17.
//  Copyright © 2017 Guillermo Figueroa. All rights reserved.
//

#ifndef FileReader_h
#define FileReader_h

#include "Queue.h"
#include <stdio.h>

/** @defgroup reader File Reader
 *  Reads the file
 */

/**
 * @ingroup reader
 * @brief Read a file containing a list of processes.
 *
 * @param filename The name of the file that's going to be opened
 * @param process_amount Returns in this variable the amount of processes found
 *
 * @return Returns the array of processes
 */
Process** read_file(const char* filename, int* process_amount);

Queue* read_file_queue(const char* filename, int* process_amount);

#endif /* FileReader_h */
