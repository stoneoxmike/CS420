#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>
#include "utils.h"
#include "verify.h"


/////////////////////////////////////////////////////////////////////////////////////
// ** IMPORTANT: Do not change this code.  It is intended to verify the functionality
//               of your program. If your program doesn't work with this code, then
//               your program does not work.
/////////////////////////////////////////////////////////////////////////////////////


/*
 * Check the output file to see if everything went as planned.  A message
 * is printed to the terminal indicating if everything works correctly.
 */
void verify_file_contents(int num_procs, int num_threads, char* filename) {
    FILE *fpt = open_file(filename, "r");   // open the file for reading
    int max_value = num_procs * num_threads;
    int value;
    bool success = true;

    // The following loop will read the file after it has been written by all the
    // child processes and threads.  It will read each line and compare it to the
    // expected value.  If an error is encountered, the 'success' flag will be set
    // to false.
    for (int expected_value = 0; expected_value <= max_value; expected_value++) {
        fscanf(fpt, "%i", &value);
        if (expected_value != value) {
            success = false;
            break;
        }
    }

    // The last section checks to make sure there are no extra numbers in the file.
    // Attempt to read from the file -- if anything is found, then set the success flag to 0
    int rv = fscanf(fpt, "%i", &value);
    if (rv != -1) {
        success = false;
    }

    close_file(fpt);    // close the file

    printf("\nVerification of file contents: \n");
    if (success) {
        printf("-SUCCESS-\n\n");
    } else {
        printf("-EPIC FAIL-\n\n");
    }
}



/*
 * Check to see if the semaphore still exists by attempting to unlink it
 */
void verify_semaphore_cleanup(const char* semaphore_name) {
    // If sem_unlink returns 0, it successfully unlinked the semaphore.
    // That means the semaphore wasn't properly cleaned up prior to calling
    // this method!
    printf("Verification of semaphore cleanup: \n");
    if (sem_unlink(semaphore_name) == 0) {
        printf("-EPIC FAIL-\n\n");
    } else {
        printf("-SUCCESS-\n\n");
    }
}