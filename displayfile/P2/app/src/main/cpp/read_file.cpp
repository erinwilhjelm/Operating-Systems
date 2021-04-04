//
// Created by Erin wilhjelm on 2019-10-17.
//
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include "read_file.h"

char *read_file(const char *filename)
{

    int f = open(filename, O_RDONLY);

    if (errno == ENOENT)
    {
        return nullptr;
    }

    /* Get the buffer size */
    off_t size = lseek(f, 0, SEEK_END);
    lseek(f, 0, SEEK_SET); //rewind

    char *buffer = new char[size];

    read(f, buffer, size);

    //null terminate
    buffer[size] = '\0';

    close(f);
    return buffer;
}