#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h>
#include "utils.h"
#include "verify.h"
#include "sem_name.h"



int main(int argc, char** argv)
{
	// NOTE: use these variables for your incoming arguments
    int num_procs = 0;      // DO NOT MODIFY THIS VARIABLE NAME
    int num_threads = 0;    // DO NOT MODIFY THIS VARIABLE NAME
    char* filename = NULL;  // DO NOT MODIFY THIS VARIABLE NAME


    // TODO: parse arguments
    int opt;
    while((opt = getopt(argc, argv, ":p:t:f:")) != -1) {
        switch(opt) {
            case 'p':
                num_procs = atoi(optarg);
                break;
            case 't':
                num_threads = atoi(optarg);
                break;
            case 'f':
                filename = optarg;
                break;
            case ':':
                perror("Option provided without argument");
                // should have exited
                break;
            case '?':
                perror("Unrecognized argument\n");
                // should have exited
                break;
        }
    }


    // TODO: open and write initial '0' to file
    FILE *filePointer = open_file(filename, "w");
    if (fprintf(filePointer, "%d\n", 0) < 0) {
        perror("Error writing newline");
        exit(EXIT_FAILURE);
    }
    close_file(filePointer);

	// TODO: open/create named semaphore (set your YCP username as SEM_NAME in sem_name.h)
    sem_t *semaphore;
    // flag should have been O_CREAT, S_IRUSR | S_IWUSR, 1
    if ((semaphore = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED) {
        perror("Error opening semaphore");
        // should have unlinked semaphore
        exit(EXIT_FAILURE);
    }


    // TODO: fork off child processes and wait for them to finish
    for (int i = 0; i < num_procs; i++) {
        int pid;
        if ((pid = fork()) < 0) {
            perror("Error forking main process");
            // don't need all this error checking
            // close and unlink semaphore
            if ((sem_close(semaphore)) < 0) {
                perror("Error closing semaphore");
                if ((sem_unlink(SEM_NAME)) < 0) {
                    perror("Error unlinking semaphore");
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_FAILURE);
            }
            if ((sem_unlink(SEM_NAME)) < 0) {
                perror("Error unlinking semaphore");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_FAILURE);
        } else if (pid == 0) {  // child process
            char str[4];
            int size = sizeof(str);
            int bytes = snprintf(str, size, "%d", num_threads);  // convert num_threads to string
            if (bytes >= size) {
                perror("Warning: Too many threads, num_threads truncated");
            }
            if (execlp("./fileWriter", "fileWriter", str, filename, NULL) < 0) {
                // don't need all this error checking
                perror("Error creating child");
                // close and unlink semaphore
                if ((sem_close(semaphore)) < 0) {
                    perror("Error closing semaphore");
                    if ((sem_unlink(SEM_NAME)) < 0) {
                        perror("Error unlinking semaphore");
                        exit(EXIT_FAILURE);
                    }
                    exit(EXIT_FAILURE);
                }
                if ((sem_unlink(SEM_NAME)) < 0) {
                    perror("Error unlinking semaphore");
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_FAILURE);
            }
        }
    }
    for (int i = 0; i < num_procs; i++) {
        wait(NULL);
    }
    
    // TODO: clean up and close named semaphore
    if ((sem_close(semaphore)) < 0) {
        perror("Error closing semaphore");
        if ((sem_unlink(SEM_NAME)) < 0) {
            perror("Error unlinking semaphore");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
    }
    if ((sem_unlink(SEM_NAME)) < 0) {
        perror("Error unlinking semaphore");
        exit(EXIT_FAILURE);
    }








    /////////////////////////////////////////////////////////////////////////////////////
    // IMPORTANT: The following function calls are intended to test the functionality
    //            of your program.  Do NOT remove these function calls from this file.
    //            BE SURE THAT ALL OF YOU CHILD PROCESSES HAVE TERMINATED BEFORE THIS POINT.
    /////////////////////////////////////////////////////////////////////////////////////
    verify_file_contents(num_procs, num_threads, filename);
    verify_semaphore_cleanup(SEM_NAME);

    return 0;
}

