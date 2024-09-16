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


#define INTERNAL_BUFFER_SIZE (16 * 1024)

// enum for read_stream_flow() return values
enum RSTREAM_RET {
    CONTINUE,
    END_OF_FILE,
    ERR
};

int is_file_descriptor();
char* make_buffer(size_t size);
int make_rstream(const char* file_path);
int read_stream_flow(const char* file_path, char* buffer);    // read from the stream

#endif