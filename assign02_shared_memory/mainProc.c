#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "ipcEx.h"


int main(int argc, char** argv)
{
    /* Print out usage statement when no value is specified */
    if (argc != 2) {
        printf("You must specify an integer value as an argument\n");
        return 1;
    }


    // TODO:
    // Insert your code here
    // string input to int
    int input = atoi(argv[1]);
    // create shared mem segment
    int segment_id = shmget(IPC_PRIVATE, sizeof(struct ipc_struct), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    if (segment_id < 0) {
        perror("Error");
        exit(1);
    }
    // create struct by attaching pointer to memory
    struct ipc_struct* shared_memory = (struct ipc_struct*) shmat(segment_id, NULL, 0);
    if (shared_memory < 0) {
        perror("Error");
        exit(1);
    }
    // store input in shared mem
    shared_memory->repeat_val = input;

    // convert segment_id to string
    char seg_id_string[128];
    snprintf(seg_id_string, 128, "%i", segment_id);
    printf("PARENT: Created shared memory with a segment ID of %i\n", segment_id);
    printf("PARENT: The child process should store its string in shared memory a total of %i times.\n\n\n", input);
    int pid = fork();
    if (pid == 0) {
        if (execlp("./childProc", "childProc", seg_id_string, NULL) < 0) {
            perror("Error");
            exit(1);
        }
    } else if (pid > 0) {
        wait(NULL);
    } else {
        exit(1);
    }
    printf("PARENT: Child with PID=%i complete\n", pid);
    printf("PARENT: Child left the following in the data buffer:\n");
    printf("========== Buffer Start ==========\n");
    printf("%s", shared_memory->data);
    printf("=========== Buffer End ===========\n\n");

    // detaches shared memory
    if (shmdt(shared_memory) < 0) {
        perror("Error");
        exit(1);
    }
    // remove shared mem id from system and delete shared mem
    if (shmctl(segment_id, IPC_RMID, 0) < 0) {
        perror("Error");
        exit(1);
    }
    printf("PARENT: Done\n");
    return 0;
}

