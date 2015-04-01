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

#define TRUE 1
#define FALSE 0
#define EXIT_ERROR 2
#define BUF_SIZE 2001

int main(int argc, char * * argv) {
    char * pattern; // Variable to store inputted pattern
    int lineCount = 1; // Line counter
    int matchFound = FALSE; // Whether we've found a match

    // We want some variables to store which "switches" were set
    int invertMatch = FALSE;
    int lineNumber = FALSE;
    int quiet = FALSE;

    // Loop through the arguments, looking for our switches...
    int i = 1; // we always skip 0, which is the program path
    for( ; i < argc; ++i) {
        if(strcmp(argv[i], "--help") == 0) {
            printf("Usage: grep-lite [OPTION]... PATTER\n"
                    "Search for PATTERN in standard input. PATTERN is a\n"
                    "string. grep-lite will search standard input line by\n"
                    "line, and (by default) print out those lines which\n"
                    "contain pattern as a substring.\n\n"
                    "  -v, --invert-match     print non-matching lines\n"
                    "  -n, --line-number      print line numbers with output\n"
                    "  -q, --quiet            suppress all output\n\n"
                    "Exit status is 0 if any line is selected, 1 otherwise;\n"
                    "if any error occurs, then the exit status is 2.\n");
            return EXIT_SUCCESS;
        } else if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--invert-match") == 0) {
            invertMatch = TRUE;
        } else if(strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--line-number") == 0) {
            lineNumber = TRUE;
        } else if(strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "--quiet") == 0) {
            quiet = TRUE;
        } else if(i == argc - 1) {
            // Last argument, which must be the pattern
            pattern = argv[i];
        }
        else {
            // Die on first unknown switch
            fprintf(stderr, "Unknown switch: '%s'\nAborting...\n", argv[i]);
            return EXIT_ERROR;
        }
    }

    // Check the validity of the pattern string
    if(pattern[0] == '-') {
        fprintf(stderr, "Pattern cannot begin with '-'.\nAborting...\n");
        return EXIT_ERROR;
    }

    // Buffer for each line
    char * buffer = malloc(BUF_SIZE * sizeof(char));

    while(fgets(buffer, BUF_SIZE - 1, stdin)) {
        // Force a cast to 'bool' and compare with bitwise XOR
        if(!!strstr(buffer, pattern) ^ invertMatch) {
            // We have a match
            if(!quiet) {
                if(lineNumber) {
                    printf("%d: ", lineCount);
                }
                printf("%s", buffer);
            }
            matchFound = TRUE;
        }
        lineCount++;
    }

    free(buffer);
    return matchFound ? EXIT_SUCCESS : EXIT_FAILURE;
}

