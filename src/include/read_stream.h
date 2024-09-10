/**
 * @file read_stream.h
 * @author Saverious Ipeni
 * @brief read_stream.h is a header file that contains the function prototype for read_stream.c
 *        which defines the read_stream function that reads a file in chunks of 16KB, or a specified,
 *        custom buffer size.
 * @version 0.1
 * @date 2024-09-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef READ_STREAM_H
#define READ_STREAM_H
#include <stddef.h>


typedef struct {
    char* file_path;
    size_t buff_size;
}rstream;

typedef struct buff_info{
    char* buff_ptr;
    size_t size;
    int err;
}buffer_info;

buffer_info* make_rstream(char* file_path); // create a read stream
buffer_info* read_stream(rstream* args);    // read from the stream

#endif