/* suggest you uncomment the following lines for your exam.c file:
   
#include <stdlib.h>
#include <string.h>

*/

/*  SOLVE THE PROBLEMS IN ORDER IF POSSIBLE.  We don't guarantee fully
    counting solutions to later problems if earlier problems are unsolved.
    
    Minimum score guarantees: (actual score may be curved above this minimum)
        Problem One working:               60% 
	Problems One and Two working:      70%
	Problems One, Two, Three working:  90%

        Problems four and five exist.

    5% deduction from this if you do not provide a working Makefile
    
    working = correct output on any tests we make up, and no valgrind errors.

    For reference:
    > valgrind --tool=memcheck --leak-check=full --log-file=memcheck.log ./main

    Code efficiently but DO NOT RACE.  Your efficiency and effectiveness is
    a key outcome of this class.

*/
	
/*======================================================================*/
/*         Problem Zero                                                 */

/*  Write a Makefile for this assignment that compiles answer.c and main.c
    into an executable file called main
*/



/*======================================================================*/
/*         Problem One                                                  */
/* 
   array_sum_nth is a function that returns the sum of SELECTED elements
   of the array of 'len' elements passed in.
   
   An array element is included in the sum if the index of that
   element is a multiple of the positive integer n.
   
   Index 0 is considered a multiple of every n.
   
   So, if array holds the elements 1,2,3,4,5 in that order, and n is
   2, the return value will be 1+3+5 = 9.

   Other examples can be found in main.c in the testing code. 

   If n=1, this function just returns the sum of all the array elements.

 */
int array_sum_nth(int * array, int len, int n);


/*======================================================================*/
/*         Problem Two                                                  */

/*
  interleave1 is a function that stores its result in memory pointed
  to by its third argument, named 'output'.
  
  You may ASSUME that output is not NULL and points at enough memory
  to store the requested result.

  The result computed is the two strings s1 and s2 interleaved: the
  characters of the output alternate from the two inputs.


  Specifically, the first character of the output is the first
  character of s1, then the second character of the output is the
  first character of s2, and so forth alternating.  If an input string
  is used up, the remaining output comes from the other string.

  example:
  

  interleave1("abc", "12345", output);
  
  will result in output pointing at the string "a1b2c345".

 */
void interleave1 (const char * s1, const char * s2, char * output);


/*======================================================================*/
/*         Problem Three                                                */
/*
  interleave2 functions the same as interleave1 except that the
  resulting string is returned differently:

  SUMMARY: the output is returned in the space of size 'avail' pointed
  to by the pointer 'output', if 'output' is not NULL and 'avail' is
  big enough.  If not, that space is freed, and a large enough space
  is created for the output---then 'output' and 'avail' are set to
  describe that new space, the desired output must then be written it
  before returning.

  interleave2 MAY CALL interleave1 and this is useful.

  HINTS (if you need more; you don't need to read these):

  (1) the result is returned as the value of the 'output' parameter,
      together with a number of bytes that is returned in 'avail'.

  (2) the 'output' parameter is passed as char ** so you can change
      the caller's pointer in order to return a value in new memory
      that you allocate if need be.  The 'avail' parameter is passed
      as int * so that you can return the size of the space allocated.

  (3) the 'output' parameter, if not NULL, is promised to point to
      available space that may or may not be sufficient for your
      answer.  The size of this space, in bytes, is given by the
      'avail' parameter.  If you don't need more space than this, do
      not change 'output' or 'avail'.

  (4) If 'output' is NULL (in which case 'avail' should not be used
      for anything), or if you need more than 'avail' bytes, including
      the null byte for your answer, you must reclaim the space
      pointed to by 'output' and then allocate the space needed, and
      point 'output' to the newly allocated space.  Do not do this if
      there was already sufficient space.

  (5) the interleaved string is returned in the space so provided.

  You may use strlen from <string.h> to help determine how much memory
  is needed, but don't forget the null byte.  Use the shell command
  "man strlen" to see a description of how to call strlen. (or in Emacs
  "M-x manual", and then enter "strlen" to the prompt)
 */
void interleave2 (const char * s1, const char * s2, char ** output, int * avail);


/*======================================================================
 *    FUNCTIONS BELOW HERE ARE "GRAVY", you do not need them to get a
 *    90% but they may help your grade anyways if you have time.  Solve
 *    the above problems first, if at all possible.
 */


/*======================================================================*/
/*         Problem Four                                                 */
/*
  hidden_subsequence determines if the string s2 is the same as s1
  with extra characters added at any point.
  
  i.e. can string s2 become string s1 by deleting characters?
  
  return 1 if so, and 0 if not.

  to answer this, you look through s2 for the first character of s1,
  and then after that keep looking from that point for the second
  character of s1, and so forth until all of s1 has been found.
  
  examples:
  
  hidden_subsequence ("abc", "125a76a687b9c12") returns 1
  hidden_subsequence ("abc", "125a76a6879c12") returns  0
  
*/
int hidden_subsequence (const char * s1, const char * s2);

/*======================================================================*/
/*         Problem Five                                                 */
/*
  merge_strings receives two strings s1 and s2. 
  
  ASSUME that s1 and s2 are made up of strictly increasing characters.
  
  i.e.  s1[i] < s1[i+1] for i small enough to stay within string s1, etc.
  
    so s1 can point to "abbcd" but not "bdcba"

  ** note that characters in strings can be compared with < and that is
  the ordering among characters we are talking about here

  The output string will be placed in space that must be created by
  merge_strings, pointed to by 'output', and must then contain all the
  characters from s1 and s2, in sorted order.
  
  example
  
  char * answer;
  merge_strings("aabcccnnop", "bbdx", &answer);
  printf("The answer is \"%s\"\n", answer);
  
  will print
  
  The answer is "aabbbcccdnnopx"

 */
void merge_strings (const char * s1, const char * s2, char ** output); 
