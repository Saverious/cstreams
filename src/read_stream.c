#include <stdlib.h>
#include <stdio.h>

#include "read_stream.h"
#include "./utils/utils.h"

static char* stream_buffer_ptr = NULL;
static size_t stream_buffer_size = 0;
static FILE* fptr = NULL;

buffer_info* make_rstream(char* file_path) {
    size_t mem_size = buff_size(file_path);
    
    char* buffer = malloc(mem_size);
    if(buffer == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    buffer_info* buff = (buffer_info*) malloc(sizeof(buffer_info));
    buff->buff_ptr = buffer;
    buff->size = mem_size;
    buff->err = 0;

    return buff;
}

buffer_info* read_stream(rstream* args) {
    buffer_info* binfo = (buffer_info*) malloc(sizeof(buffer_info));
    if(binfo == NULL) {
        perror("could not allocate memory");
        exit(EXIT_FAILURE);
    }

    buffer_info* err_buff = (buffer_info*) malloc(sizeof(buffer_info));
    if(err_buff == NULL) {
        perror("could not allocate memory");
        exit(EXIT_FAILURE);
    }

    err_buff->buff_ptr = NULL;
    err_buff->size = (size_t) -1;
    err_buff->err = -1;
    
    if(stream_buffer_ptr == NULL && stream_buffer_size == 0) {
        fptr = fopen(args->file_path, "r");
        if(fptr == NULL) {
            perror("read_stream()->Invalid file path");
            return err_buff;
        }

        buffer_info* buff = make_rstream(args->file_path);
        stream_buffer_ptr = buff->buff_ptr;
        stream_buffer_size = buff->size;
    }

    size_t bytes_read = fread(stream_buffer_ptr, 1, stream_buffer_size, fptr);
    binfo->buff_ptr = stream_buffer_ptr;
    binfo->size = bytes_read;
    binfo->err = 0;

    if(bytes_read < stream_buffer_size) {
        if(feof(fptr)) {  // EOF reached
            fclose(fptr);
            fptr = NULL;
            return binfo;
        }else {
            perror("read_stream()-> Error in file");
            free(stream_buffer_ptr);
            free(binfo);
            return err_buff;
        }
    }

    return binfo;
}