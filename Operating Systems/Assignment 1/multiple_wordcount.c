/*
 * File: multiple_wordcount.c
 * Hassan Sheikh
 *
 * ....
 */

#include <stdio.h>
#include <stdlib.h>
// include other standard header files or your own user defined libraries needed 
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
  // Checks if there are multiple input files in the command line arguments
  if (argc < 2) {
    fprintf(stderr, "Usage: %s File_1 File_2 ...\n", argv[0]);
    return 1;
  }


  for(int i = 1; i < argc; i++) {

    pid_t cpid = fork();
    // Checking if fork() was executed correctly
    if (cpid == -1) { 
      perror("fork");
      return 1; 
    }

    if (cpid == 0) {

     // this part is for child process
     // exec(...) the wordcount program with argv[i] as a paramenter
      char *wordCount_argv[] = {"./wordcount", argv[i], NULL};
      int result = execvp("./wordcount", wordCount_argv);
      // if statement to check whether or not exec() is sucessfull
      if (result == -1) {
        // Error message for execvp() if it fails
        perror("execvp");
        // returns/exits with a value of 2, meaning that execvp failed.
        return 2;
      }
    }
    printf("wordcount with process id of %s counted words in %s: number of words is %d", getpid(), argv[i], wordCount_argv[i]);
  }

  // Counting down the files that have worked and those that failed
  int working = 0, failing = 0;
  for( int i = 1; i < argc; i++) {
      // Waiting for all children and checking their exit codes
      int status, count;
      wait(&status);

      // Sorting and counting the files 
      if(WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        working++;
      }
      else {
        failing++;
      }
      count++;
  }

  printf("Parent process %s created %d child processes to count words in %d files", getpid(), count, count);
  printf("\t%d files have been counted successfully!", working);
  printf("\t%d files did not exist", failing);

  return 0;
}
   