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
#include "exam3.h"

void test_general_make_words();
void test_reachable_size();

int general_make_words(char **input, int inputlen, int (*filter)(char * prefix, char extension));

int main (int argc, char **argv)
{
    FILE *fp;

    if(argc > 1) {
        if(argc > 2 && strcmp(argv[1], "-args") == 0) {
            make_words(argv + 2, argc - 2);
            return EXIT_SUCCESS;
        } else if(argc == 3 && strcmp(argv[1], "-file") == 0 && (fp = fopen(argv[2], "r"))) {
            char *lines[11] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}; // one for EOF, see below
            ssize_t numchar;
            size_t n = 0;
            int numlines = 0;

            while((numchar = getline(lines + numlines, &n, fp)) > 1 && numlines < 10) {
                // strip the newline off of the line (replace with null terminator)
                lines[numlines][numchar - 1] = '\0';

                n = 0;
                numlines++;
            }

            if(numlines == 0) {
                fprintf(stderr, "File is empty or getline failed! Cannot call make_words.\n");
            } else {
                // Call make_words
                make_words(lines, numlines);

                // Deallocate memory (lines) allocated by getline
                // Getline will allocate a line for the EOF after the last newline,
                // so we must deallocate that too. Why? I dunno. (Stupid.)
                for(; numlines >= 0; numlines--) {
                    free(lines[numlines]);
                }
            }

            // Close the file
            fclose(fp);

            return EXIT_SUCCESS;
        } else {
            fprintf(stderr, "Invalid arguments to main or cannot open file. Aborting.\n");
            return EXIT_FAILURE;
        }
    }

  printf("\n======================================================================\n\n");

  test_reachable_size();

  printf("\n======================================================================\n\n");

  test_general_make_words();

  printf("\n======================================================================\n\n");

  return 0;

}


void test_reachable_size ()
{
  printf("TESTING PROBLEM 5: reachable_size\n\n");

  int test1[4][5] = {{1, 1, 1, 1, 1},
                    {1, 0, 1, 0, 1},
                    {1, 0, 1, 1, 1},
                    {1, 1, 1, 0, 1}};

  int vals[4][5];


  //TEST 1 of reachable_size
  memcpy(vals,test1,sizeof(int)*4*5);
  int result1 = reachable_size((int *)vals,4,5,1,1);
  int answer1 = 3;
  printf("Test 1 of reachable_size returns %d, should be %d, %s\n", result1, answer1, (result1==answer1 ? "CORRECT" : "WRONG"));

  //TEST 2 of reachable_size
  memcpy(vals,test1,sizeof(int)*4*5);
  int result2 = reachable_size((int *)vals,4,5,3,3);
  int answer2 = 3;
  printf("Test 2 of reachable_size returns %d, should be %d, %s\n", result2, answer2, (result2==answer2 ? "CORRECT" : "WRONG"));

  //TEST 3 of reachable_size
  memcpy(vals,test1,sizeof(int)*4*5);
  int result3 = reachable_size((int *)vals,4,5,2,1);
  int answer3 = 1;
  printf("Test 3 of reachable_size returns %d, should be %d, %s\n", result3, answer3, (result3==answer3 ? "CORRECT" : "WRONG"));

  //TEST 4 of reachable_size
  memcpy(vals,test1,sizeof(int)*4*5);
  int result4 = reachable_size((int *)vals,4,5,0,0);
  int answer4 = 0;
  printf("Test 4 of reachable_size returns %d, should be %d, %s\n", result4, answer4, (result4==answer4 ? "CORRECT" : "WRONG"));

}


void test_general_make_words ()
  {
  printf("TESTING PROBLEM 4: general_make_words\n\n");


  // FIRST TEST FOR PROBLEM 4
  int no_b (char * prefix, char extension)
  {
    return ('b' != extension);
  }

  char * words1[3] = {"abc", "de", "f"};
  UNUSED(words1);

  // UNCOMMENT THESE TWO LINES IF YOU DO PROBLEM 4
  int result1 = general_make_words(words1, 3, no_b);
  printf("Test 2 of general_make_words returns %d, should be 4, %s\n", result1, (result1==4 ? "CORRECT" : "WRONG"));

  // SECOND TEST FOR PROBLEM 4
  int ordered (char * prefix, char extension)
  {
    int len=strlen(prefix);
    return (len==0 || prefix[len-1]<extension);
  }

  char * words2[3] = {"ace", "bd", "cf"};
  UNUSED(words2);

  // UNCOMMENT THESE TWO LINES IF YOU DO PROBLEM 4
  int result2 = general_make_words(words2, 3, ordered);
  printf("Test 2 of general_make_words returns %d, should be 4, %s\n", result2, (result2==4 ? "CORRECT" : "WRONG"));
  }
