// eswan
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "hidestrings.h"

/*
  PROBLEM TWO

  Complete the main() function below so that restorestrings reverses
  the process implemented by hidestrings.  In other words,
  restorestrings reads a binary file, encoded as described in
  hidestrings.c, and writes a text file the same as the one that was
  encoded.

  Note, the individual byte coding can be reversed the same way it was
  done, flipping all bits:

  char decoded = coded ^ 255;

 */


int main (int argc, char **argv) {

  if (argc != 3 || 0==strcmp(argv[1],"--help")) {
    printf("Usage: %s <infile> <outfile>\n", argv[0]);
    printf("   <infile> is a binary input file encoding a file of strings\n");
    printf("   <outfile> will be written over with a file of the strings encoded in <infile>\n");
    return 0;
  }

  FILE *infile = fopen(argv[1],"rb");

  if (!infile) {
    fprintf(stderr, "Error opening input file \"%s\"\n", argv[1]);
    return 1;
  }


  File_header header;
  if (fread(&header, sizeof(File_header), 1, infile) != 1) {
    fprintf(stderr, "Error reading input file \"%s\"\n", argv[1]);
    return 1;
  }

  if (header.magic != 0) {
      fprintf(stderr, "Input file \"%s\" not an encoded file\n", argv[1]);
      return 1;
  }

  int numlines = header.line_count;

  FILE *outfile = fopen(argv[2],"w");

  if (!outfile) {
    fprintf(stderr, "Error opening output file \"%s\"\n", argv[2]);
    return 1;
  }

  // loop index for "decoding" using ^255
  int linecount=0;
  unsigned int i;

  for (linecount=0; linecount<numlines; linecount++) {

    uint32_t linelen;
    if (fread(&linelen, sizeof(uint32_t), 1, infile) != 1) {
      fprintf(stderr, "Error reading input file \"%s\"\n", argv[1]);
      return 1;
    }

    char buffer[linelen+2];
    buffer[linelen]='\n';
    buffer[linelen+1]='\0';

    if (linelen > 0 && fread(buffer, linelen * sizeof(char), 1, infile) != 1) {
      fprintf(stderr, "Error reading input file \"%s\"\n", argv[1]);
      return 1;
    }

    for (i=0; i<linelen; i++) {
        buffer[i] = buffer[i] ^ 255;
    }


    fprintf(outfile, "%s", buffer);
  }

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
