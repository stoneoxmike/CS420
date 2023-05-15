#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <sys/stat.h>

#define STDIN  0
#define STDOUT 1
#define STDERR 2

#define BUFFER_SIZE 256

// could have defined all error messages up here and wrote a function to write them

int main(int argc, char** argv)
{
  char *src_file, *dst_file;
  char data_buf[BUFFER_SIZE];

  // TODO
  // Declare any other variables
  // you may need here
  //
  struct stat fileStat;

  // verify the user has supplied the correct number of arguments
  // and assign source and destination file names
  if (argc != 3) {
    write(STDERR, "Error: Incorrect number of arguments\n", 37);
    exit(EXIT_FAILURE);
  } else {

    // TODO
    // Make appropriate assignments if correct
    // number of arguments were supplied
    //
    src_file = argv[1];
    dst_file = argv[2];
  }



  // TODO
  // Open the source file, be sure to apply appropriate permissions
  // BE SURE TO CHECK FOR ERRORS WHEN OPENING FILES
  // If an error occurs, report the error and terminate the program
  int src = open(src_file, O_RDONLY);
  if (src < 0) {
      write(STDERR, "Error opening source file\n", 26);
      // should have used EXIT_FAILURE instead to let OS decide best magic number
      exit(1);
  }

  // TODO
  // Determine the file system permissions (i.e. mode) of the source file
  // Again, be sure to check for errors!
  if (stat(src_file, &fileStat) < 0) {
      write(STDERR, "Error checking permissions\n", 27);
      exit(1);
  }

  // TODO
  // Open the destination file, be sure to apply appropriate permissions
  // BE SURE TO CHECK FOR ERRORS WHEN OPENING FILES
  // If an error occurs, report the error and terminate the program
  int dest = open(dst_file, O_WRONLY | O_CREAT | O_TRUNC, fileStat.st_mode);
  if (dest < 0) {
      write(STDERR, "Error opening destination file\n", 31);
      exit(1);
  }

  // TODO
  // Output a status message here, something like
  // "Copying AAA to BBB"
  write(STDOUT, "Copying ", 8);
  write(STDOUT, src_file, strlen(src_file));
  write(STDOUT, " to ", 4);
  write(STDOUT, dst_file, strlen(dst_file));
  write(STDOUT, "\n", 1);
 

  // TODO
  // Do the work to actually copy the file here
  // Be efficient and copy CHUNKS of data
  // DO NOT COPY ONE BYTE AT AT TIME
  // DO NOT READ THE ENTIRE FILE INTO MEMORY
  // Again, be sure to check for errors!
  // could be much simpler, while bytesRead != 0;
  // then make sure bytesRead is wrote
  for (int i = 0; i < (fileStat.st_size / BUFFER_SIZE); i++) {
      if (read(src, data_buf, BUFFER_SIZE) < 0) {
          write(STDERR, "There was an error reading\n", 27);
          exit(1);
      }
      if (write(dest, data_buf, BUFFER_SIZE) != BUFFER_SIZE) {
          write(STDERR, "There was an error writing\n", 27);
          exit(1);
      }
  }
    if (read(src, data_buf, fileStat.st_size % BUFFER_SIZE) < 0) {
        write(STDERR, "There was an error reading\n", 27);
        exit(1);
    }
    if (write(dest, data_buf, fileStat.st_size % BUFFER_SIZE) != fileStat.st_size % BUFFER_SIZE) {
        write(STDERR, "There was an error writing\n", 27);
        exit(1);
    }


  // TODO
  // Close the source and destination files here
  // As always, check for any errors that may be generated
  if (close(src) < 0) {
      exit(1);
  }
  if (close(dest) < 0) {
      exit(1);
  }

  return 0;
}
