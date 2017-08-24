//
//  FileReader.h
//  T1
//
//  Created by Guillermo Figueroa and Juan Cortés on 8/16/17.
//  Copyright © 2017 Guillermo Figueroa and Juan Cortés. All rights reserved.
//

#ifndef FileReader_h
#define FileReader_h

#include "Queue.h"
#include <stdio.h>

/** @defgroup reader File Reader
 *  @brief Reads the file and creates the processes
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

/**
 * @ingroup reader
 * @brief Read a file containing a list of processes.
 *
 * @param filename The name of the file that's going to be opened
 * @param process_amount Returns in this variable the amount of processes found
 *
 * @return Returns a queue of the processes ordered by the initial time
 */
Queue* read_file_queue(const char* filename, int* process_amount);

#endif /* FileReader_h */
