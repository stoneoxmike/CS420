#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <pthread.h>
#include "utils.h"
#include "verify.h"
#include "sem_name.h"

struct sem_struct {
    sem_t* semaphore;
    char* filename;
};

void *work(void *args) {
    struct sem_struct * s1 = args;
    char str[4];
    int current;
    // lock semaphore ERROR CHECK
    if (sem_wait(s1->semaphore) < 0) {
        perror("Error joining threads");
        if ((sem_close(s1->semaphore)) < 0) {
            perror("Error closing semaphore");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
    }
    // open file should have been r+
    FILE *filePointer = open_file(s1->filename, "r");
    // move pointer to end ERROR CHECK
    fseek(filePointer, -2, SEEK_END);
    // move pointer back 2 bytes fgetc(filePointer) != '\n'
    // need more error checking
    if (ftell(filePointer) > 3) {
        while (fgetc(filePointer) != '\n') {
            fseek(filePointer, -2, SEEK_CUR);
        }
    }
    // get int at pointer
    current = atoi(fgets(str, 4, filePointer)) + 1;
    // move pointer to end
    // this is awful, writing could've been like 2 lines
    close_file(filePointer);
    FILE *appendfp = fopen(s1->filename, "a");
    if (fprintf(appendfp, "%d\n", current) < 0) {
        perror("Error writing next number");
        // should have closed file and posted semaphore
        // should have used pthread_exit(NULL)
        exit(EXIT_FAILURE);
    }
    // close file
    close_file(filePointer);
    // unlock semaphore ERROR CHECK
    if (sem_post(s1->semaphore) < 0) {
        perror("Error joining threads");
        if ((sem_close(s1->semaphore)) < 0) {
            perror("Error closing semaphore");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
    }
    return NULL;
}

int main(int argc, char** argv)
{
	// NOTE: use these variables for your incoming arguments
    int num_threads;
    char* filename = NULL;

	// TODO: parse arguments
    if (argc != 3) {
        perror("Incorrect number of arguments");
        exit(EXIT_FAILURE);
    } else {
        num_threads = atoi(argv[1]);
        filename = argv[2];
    }

	// TODO: open/create named semaphore (set your YCP username as SEM_NAME in sem_name.h)
    sem_t *semaphore;
    // O_CREAT, 0644,
    if ((semaphore = sem_open(SEM_NAME, 0, 0666, 1)) == SEM_FAILED) {
        perror("Error opening semaphore");
        exit(EXIT_FAILURE);
    }


	// TODO: spawn threads to do the work and wait for them to finish
    pthread_t threads[num_threads];
    int thread_args[num_threads];
    struct sem_struct s1;
    s1.semaphore = semaphore;
    s1.filename = filename;
    for (int i = 0; i < num_threads; i++) {
        thread_args[i] = i;
        if ((pthread_create(&threads[i], NULL, work, &s1)) < 0) {
            perror("Error creating threads");
            if ((sem_close(semaphore)) < 0) {
                perror("Error closing semaphore");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < num_threads; i++) {
        if ((pthread_join(threads[i], NULL)) < 0) {
            perror("Error joining threads");
            if ((sem_close(semaphore)) < 0) {
                perror("Error closing semaphore");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_FAILURE);
        }
    }

    // TODO: clean up named semaphore
    if ((sem_close(semaphore)) < 0) {
        perror("Error closing semaphore");
        exit(EXIT_FAILURE);
    }






    /////////////////////////////////////////////////////////////////////////////////////
    // IMPORTANT: The following function call is intended to test the functionality
    //            of your program.  Do NOT remove this function call from this file.
    //            BE SURE THAT ALL OF YOU CHILD PROCESSES HAVE TERMINATED BEFORE THIS POINT.
    /////////////////////////////////////////////////////////////////////////////////////
#ifdef FILEWRITER_STANDALONE_MODE
    verify_file_contents(1, num_threads, filename);
#endif

    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
