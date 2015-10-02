// eswan
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "hidestrings.h"

int count_lines (char *filename);

/*
  PROBLEM ONE -- REPLACE THE COMMENTED ALL CAPS SECTIONS OF MAIN() FUNCTION
  WITH YOUR CODE

  --also replace all caps section in hidestrings.h

  Complete the implementation of the main() function below that reads
  in a ASCII text file (a normal non-binary file) line by line and
  writes out each line in a binary file according the following
  encoding:

  The first 8 bytes of the encoded file follow this format:

  -------------------------------------------------
  | magic-number (all 0s) | number of lines coded |  8 bytes
  -------------------------------------------------

  The magic number is a 4-byte integer zero.  The number of lines
  coded is also a 4-byte integer.

  Then, for each line coded, a section is written of the output file
  according to the following

  -------------------------------------------------
  | number n of coded bytes |  coded bytes        |  4+n bytes,
  -------------------------------------------------

  An n-byte string is coded (WITHOUT the null terminator AND without
  the newline character) as the 4-byte int n, followed by n coded
  bytes.  Each byte is coded independently: the coded byte is the
  original byte with every bit flipped, which can be computed as
  follows:

  char uncoded = ...expression setting the char to be coded...;
  char coded = uncoded ^ 255;   // 255 is hexadecimal FF, i.e. all bits one.

  The coding can be reversed the same way:

  char decoded = coded ^ 255;

 */


int main (int argc, char **argv) {

  if (argc != 3 || 0==strcmp(argv[1],"--help")) {
    printf("Usage: %s <infile> <outfile>\n", argv[0]);
    printf("   <infile> is an input file of binary encoded strings \n");
    printf("   <outfile> will be written over with the decoded version of the contents of <infile>\n");
    return 0;
  }

  int numlines = count_lines (argv[1]);
  if (numlines<0) return 1;


  FILE *infile = fopen(argv[1],"r");

  if (!infile) {
    fprintf(stderr, "Error opening input file \"%s\"\n", argv[1]);
    return 1;
  }

  FILE *outfile = fopen(argv[2], "wb");

  if (!outfile) {
    fprintf(stderr, "Error opening output file \"%s\"\n", argv[2]);
    return 1;
  }

  // for fwrite below
  File_header header;
  header.magic = 0;
  header.line_count = numlines;

  if(fwrite(&header, sizeof(File_header), 1, outfile) != 1) {
      fprintf(stderr, "Error writing output file \"%s\"\n", argv[2]);
      return 1;
  }

  // for getline below
  char *lineptr=NULL;
  size_t n=0;

  // loop index for "encoding" using ^255
  uint32_t i;

  while (getline(&lineptr, &n, infile)>0) {
    uint32_t len = strlen(lineptr)-1; // don't count newline so won't encode or write it

    for (i=0; i<len; i++) {
        lineptr[i] = lineptr[i] ^ 255;
    }

    if (fwrite(&len, sizeof(uint32_t), 1, outfile) != 1) {
      fprintf(stderr, "Error writing output file \"%s\"\n", argv[2]);
       return 1;
    }

    // If we have an "empty" line (just a newline, fwrite will return 0 here
    if (len > 0 && fwrite(lineptr, len, 1, outfile) != 1) {
      fprintf(stderr, "Error writing output file \"%s\"\n", argv[2]);
      return 1;
    }
  }

  free(lineptr);

  if (fclose(infile)) {
    fprintf(stderr, "Error closing input file \"%s\"\n", argv[1]);
    return 1;
  }

  if (fclose(outfile)) {
    fprintf(stderr, "Error closing output file \"%s\"\n", argv[2]);
    return 1;
  }

  return 0;
}


// This function does not need to be altered during the exam.
// This function returns the number of lines found in the file, or -1 if any error.

int count_lines (char *filename) {
  FILE *infile = fopen(filename,"r");

  if (!infile) {
    fprintf(stderr, "Error opening input file \"%s\"\n", filename);
    return -1;
  }

  char *lineptr=NULL;
  size_t n=0;

  int result=0;
  while (getline(&lineptr, &n, infile)>0) result++;

  if (fclose(infile)) {
    free(lineptr);
    fprintf(stderr, "Error closing input file \"%s\"\n", filename);
    return -1;
  }

  free(lineptr);
  return result;
}
