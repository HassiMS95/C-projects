/*
 * File: wordcount.c
 * Hassan Sheikh
 *
 * ....
 */

#include <stdio.h>
#include <stdlib.h>
// include other standard header files or your own user defined libraries needed
#include <string.h>


#define MAX_LINE_LENGTH 1024


int ReadLine(FILE *fp, int max_len){
  /*Variables set up for counting each word in each line to be read*/
  int wordCount = 0;
  char buffer[MAX_LINE_LENGTH];
  
  /*While loop for going through every line in a selected file*/
  while (fgets(buffer, MAX_LINE_LENGTH, fp)) {
    int k = 0;
    for (int j = 0; buffer[j]; j++) {
      if (buffer[j] == '\n' || buffer[j] == ' ' || buffer[j] == '\t' || buffer[j] == '\v' || buffer[j] == '\f' || buffer[j] == '\r') {
        if (k == 0) {
          wordCount++;
        }
        k = 1;
      }
      else {
        k = 0;
      }
    }
  }
  return wordCount + 1;
}


int main(int argc, char *argv[]) {
  // Checks if there are two arguments
  if (argc != 2) {
    fprintf(stderr, "Usage: %s An_Input_File\n", argv[0]);
    return 1;
  }

  // Checks if the file is valid
  char *file = argv[1];
  FILE *fp = fopen(file, "r");
  if (!fp) {
    perror(file);
    return 1;
  }

  // Runs Readline() method to count the words
  int wordCount = ReadLine(fp, MAX_LINE_LENGTH);
  
  // Print statement
  printf("wordcount with process id of %d counted words in %s: number of words is %d\n", getpid(), file, wordCount);
  
  // Closes file
  fclose(fp);

  return 0;
}
   