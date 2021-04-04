//
// Created by Erin wilhjelm on 2019-10-17.
//

#ifndef P2_READ_FILE_H
#define P2_READ_FILE_H


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <jni.h>

using namespace std;

char *read_file(const char *filename);


#endif //P2_READ_FILE_H
