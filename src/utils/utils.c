#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "utils.h"

#define DEFAULT_BUFF_SIZE (16 * 1024) // 16kbs


size_t file_size(const char* file_path) {
    struct stat st;

    if(stat(file_path, &st) == 0) {
        return st.st_size;
    }else{
        return -1;
    }
}

size_t buff_size(const char* file_path) {
    if(file_path == NULL){
        perror("Invalid file path");
        exit(EXIT_FAILURE);
    }

    size_t buff_size;
    size_t sizeof_file = file_size(file_path);

    if(sizeof_file < DEFAULT_BUFF_SIZE && sizeof_file != (size_t) -1) {
        buff_size = sizeof_file;
    }else {
        buff_size = DEFAULT_BUFF_SIZE;
    }

    return buff_size;
}