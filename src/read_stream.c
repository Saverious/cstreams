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

    return buff;
}

char* read_stream(rstream* args) {
    if(stream_buffer_ptr == NULL && stream_buffer_size == 0) {
        fptr = fopen(args->file_path, "r");
        if(fptr == NULL) {
            perror("read_stream()->Invalid file path");
            return "ERR";
        }

        buffer_info* buff = make_rstream(args->file_path);
        stream_buffer_ptr = buff->buff_ptr;
        stream_buffer_size = buff->size;
    }

    size_t bytes_read = fread(stream_buffer_ptr, 1, stream_buffer_size, fptr);
    if(bytes_read < stream_buffer_size) {
        if(feof(fptr)) {  // EOF reached
            fclose(fptr);
            fptr = NULL;
            return stream_buffer_ptr;
        }else {
            perror("read_stream()-> Error in file");
            free(stream_buffer_ptr);
            return "ERR";
        }
    }

    return stream_buffer_ptr;
}