#ifndef READ_FILE_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define READ_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <iostream>
#include <fstream>

using namespace std;

char *read_file(const char *filename);


#endif
