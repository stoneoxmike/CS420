#ifndef _verify_h
#define _verify_h

void verify_file_contents(int num_procs, int num_threads, char* filename);
void verify_semaphore_cleanup(const char* semaphore_name);

#endif

