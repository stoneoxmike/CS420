#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

/*
 *
 */
FILE* open_file(char* filename, char* rw) {
    FILE* fp;
    
    if ((fp = fopen(filename, rw)) == NULL) {
        if(strcmp(rw, "r") == 0) {
            fprintf(stderr, "Can't open file %s for reading\n", filename);
        } else if(strcmp(rw, "w") == 0) {
            fprintf(stderr, "Can't open file %s for writing\n", filename);
        } else {
            fprintf(stderr, "Can't open file %s for operation: %s\n", filename, rw);
        }
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    
    return fp;
}



/*
 *
 */
void close_file(FILE* fp) {
    if (fclose(fp) != 0) {
        fprintf(stderr, "There was a problem closing a file.\n");
        perror("fclose");
    }
}



