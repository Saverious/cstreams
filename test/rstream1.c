// /**
//  * read 1st chunk, print result in console
//  * 
//  */

// #include <stdio.h>
// #include <stdlib.h>
// #include "../src/include/read_stream.h"

// int main() {
//     char* myFile = "./bigSrc.txt";
//     char* buffer = make_buffer(0);
//     if(buffer == NULL){
//         printf("could not create internal buffer");
//         exit(EXIT_FAILURE);
//     }

//     int result = read_stream_flow(myFile, buffer);
//     if(result == CONTINUE){
//         printf("%s\n", buffer);
//         printf("*** end of chunk ***\n");
//     }else if(result == END_OF_FILE){
//         printf("** End of file reached ***\n");
//         free(buffer);
//     }else{
//         perror("error in read_stream_flow");
//         exit(EXIT_FAILURE);
//     }
// }