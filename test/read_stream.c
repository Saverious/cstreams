#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/include/read_stream.h"

int main() {
    char* file_path = "/home/nuclear/Documents/SWE/coding/C/files/txtFiles/bigSrc.txt";
    size_t size = 16 * 1024;
    rstream* buff = (rstream*) malloc(sizeof(rstream));
    if(buff == NULL) {
        perror("could not allocate memory");
        exit(EXIT_FAILURE);
    }

    buff->file_path = file_path;
    buff->buff_size = size;

    FILE* fptr = fopen("./bigDest.txt", "w");
    if(fptr == NULL) {
        perror("failed to open file for write");
        free(buff);
        exit(EXIT_FAILURE);
    }

    buffer_info* buffer;
    while(1) {
        buffer = read_stream(buff);
        if(buffer->err == -1) {
            perror("read_stream error");
            free(buff);
            free(buffer);
            fclose(fptr);
            exit(EXIT_FAILURE);
        }

        fwrite(buffer->buff_ptr, 1, buffer->size, fptr);

        if(buffer->size < size) {
            printf("\n *** EOF reached ***\n");
            break;
        }
    }
    
    fclose(fptr);
    free(buff);
    free(buffer);
    return 0;
}