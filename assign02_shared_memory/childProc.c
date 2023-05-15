#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ipcEx.h"


int main(int argc, char** argv)
{
    char data_string[] = "Hello Shared Memory!\n";

    // TODO:
    // Insert your code here
    printf("CHILD: Received %i arguments\n", argc);
    char *segment_id_string = argv[1];
    int segment_id = atoi(segment_id_string);
    struct ipc_struct* shared_memory = (struct ipc_struct*) shmat(segment_id, NULL, 0);
    if (shared_memory < 0) {
        perror("Error");
        exit(1);
    }
    printf("CHILD: Attempting to access segment ID %i...\n", segment_id);
    printf("CHILD: Parent requested that I store my data %i times\n", shared_memory->repeat_val);
    for(int i = 0; i < shared_memory->repeat_val; i++) {
        snprintf(shared_memory->data + i*(sizeof(data_string)-1), sizeof(data_string),"%s", data_string);
    }
    if (shmdt(shared_memory) < 0) {
        perror("Error");
        exit(1);
    }
    printf("CHILD: Done copying data, exiting.\n\n\n");
  return 0;
}



