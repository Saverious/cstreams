/**
 * read chunks from file, write to a new file
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "../src/include/read_stream.h"

int main() {
    char* srcFile = "./bigSrc.txt";
    char* destFile = "./bigDest.txt";
    char* buffer = make_buffer(0);
    if(buffer == NULL){
        printf("could not create internal buffer");
        exit(EXIT_FAILURE);
    }

    FILE* fptr = fopen(destFile, "wb");
    if(fptr == NULL){
        printf("could not open file for write\n");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    while(1){
        int result = read_stream_flow(srcFile, buffer);
        if(result == CONTINUE){
            size_t write_count = fwrite(buffer, 1, 16 * 1024, fptr);
            if(write_count < 16 * 1024){
                if(feof(fptr)){
                    //printf("EOF reached\n");
                    continue;
                }else if(ferror(fptr)){
                    perror("Error writing to file");
                    free(buffer);
                    fclose(fptr);
                    exit(EXIT_FAILURE);
                }else{
                    continue;
                }
            }
        }else if(result == END_OF_FILE){
            printf("** End of file reached ***\n");
            free(buffer);
            fclose(fptr);
            break;
        }else{
            perror("error in read_stream_flow");
            free(buffer);
            fclose(fptr);
            exit(EXIT_FAILURE);
        }
    }

    printf("finished IO operation\n");
    return 0;
}