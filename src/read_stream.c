#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "read_stream.h"

static int fd = -1;
static int read_size = INTERNAL_BUFFER_SIZE; // size of bytes to read using read() syscall


// check if fd exists
int is_file_descriptor() {
    return fd >= 0;
}

// create internal buffer
char* make_buffer(size_t size) {
    if(size == 0) {
        size = INTERNAL_BUFFER_SIZE;
    }

    read_size = size;

    char* internal_buffer = malloc(size);
    if(internal_buffer == NULL) {
        perror("Internal buffer error");
        return NULL;
    }

    return internal_buffer;
}

// create a stream for reading
int make_rstream(const char* file_path) {
    fd = open(file_path, O_RDONLY);
    if(fd < 0) {
        perror("could not create read stream");
        return -1;
    }

    return 0;
}

// read stream in flowing mode
int read_stream_flow(const char* file_path, char* buffer) {
    enum RSTREAM_RET value = CONTINUE;

    int isFd = is_file_descriptor();
    if(!isFd) {
        int result = make_rstream(file_path);
        if(result == -1){
            value = ERR;
            perror("could not create read stream");
            return value;
        }
    }

    ssize_t bytes_read = read(fd, buffer, read_size);
    if(bytes_read > 0) {
        return value;
    }else if(bytes_read == 0) {  // EOf reached
        close(fd);
        fd = -1;
        value = END_OF_FILE;
        return value;
    }else {
        value = ERR;
        return value;
    }
}