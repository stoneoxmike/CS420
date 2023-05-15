#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <semaphore.h>
#include "sem_name.h"


void print_usage() {
    printf("\n");
    printf("  usage: rmsem [-s semaphore_name]\n");
    printf("               [-s semaphore_name] : the name of the named semaphore to remove; if no semaphore name is specified,\n");
    printf("                                     then the default semaphore name from sem_name.h will be used.\n");
    printf("\n");
}


int main(int argc, char** argv)
{
    const char* sem_to_unlink;
    bool user_specified_semaphore = false;


    // Parse args using getopt
    int c;
    while ((c = getopt(argc, argv, ":s:")) != -1) {
        switch(c) {
            case 's':
                sem_to_unlink = optarg;
                user_specified_semaphore = true;
                break;
            case ':':
                printf("option -%c provided without argument, using default semaphore name\n", optopt);
                break;
            case '?':
                fprintf(stderr, "unrecognized option: -%c\n", optopt);
                print_usage();
                exit(EXIT_FAILURE);
        }
    }


    // print out a quick status message and set the semaphore to unlink if one wasn't specified by the user
    if (user_specified_semaphore) {
        printf("Trying to remove user specified semaphore with name: %s\n", sem_to_unlink);
    } else {
        sem_to_unlink = SEM_NAME;    // set a default semaphore name from the sem_name file
        printf("Trying to remove default semaphore with name: %s\n", sem_to_unlink);
    }


    // call unlink to remove the named semaphore
    if (sem_unlink(sem_to_unlink) == -1) {
        perror("sem_unlink");
        printf("Semaphore with name '%s' does not exist, failed to unlink\n", sem_to_unlink);
    } else {
        printf("Semaphore with name '%s' successfully unlinked\n", sem_to_unlink);
    }

    return 0;
}

