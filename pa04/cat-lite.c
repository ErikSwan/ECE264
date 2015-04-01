/*

 **************************
 * To intrepid Googlers: *
 **************************

 This file was written by Erik Swan for the Spring 2015 section of ECE 264.

 Although I have made it available publicly under the MIT license, you should be
 well aware that submitting *any* portion of this code as your own work is
 academically dishonest.

 Considering that this file and the corresponding GitHub project have been
 indexed by Google and are likely to show up among the top results for "ECE 264",
 you should assume that using any of this code will quite easily be flagged by
 the anti-cheating tools the teaching team likely has in place.

 Don't be dumb. Do your work.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * * argv)
{
   int i;
   char c;
   FILE * fptr;

   // The '--help' pass
   for(i = 1; i < argc; ++i) {
      if(strcmp(argv[i], "--help") == 0) {
          // Print help
          printf("Usage: cat-lite [--help] [FILE]...\n"
                  "With no FILE, or when FILE is -, read standard input.\n\n"

                  "Examples:\n"
                  "cat-lite README   Print the file README to standard output.\n"
                  "cat-lite f - g    Print f's contents, then standard input, \n"
                  "                  then g's contents.\n"
                  "cat-lite          Copy standard input to standard output.\n");
          return EXIT_SUCCESS;
      }
   }

   // Output pass
   for(i = 1; i < argc; ++i) {
      if(strcmp(argv[i], "-") == 0) {
          // stdin
          while((c = fgetc(stdin)) != EOF) {
              fputc(c, stdout);
          }
      } else {
          fptr = fopen(argv[i], "r");
          if(!fptr) {
              fprintf(stderr, "cat cannot open %s\n", argv[i]);
              return EXIT_FAILURE;
          }
          while((c = fgetc(fptr)) != EOF) {
              fputc(c, stdout);
          }
          fclose(fptr);
      }
   }

   if(argc == 1) {
       // copy stdin to stdout
       while((c = fgetc(stdin)) != EOF) {
           fputc(c, stdout);
       }
   }

   return EXIT_SUCCESS;
}

