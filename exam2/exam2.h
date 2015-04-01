/* suggest you uncomment the following lines for your exam.c file:
   
#include <stdlib.h>
#include <string.h>

*/

/*  SOLVE THE PROBLEMS IN ORDER IF POSSIBLE.  We don't guarantee fully
    counting solutions to later problems if earlier problems are unsolved.
    
    Minimum score guarantees: (actual score may be curved above this minimum)
        Problem One working:               70% 
	Problems One and Two working:      80%
	Problems One, Two, Three working:  90%

        Problems four and five exist.  We may not grade these without
	submission of working problems one to three.

    5% deduction from this if you do not provide a working Makefile
    
    working = correct output on any tests we make up, and no valgrind errors.

    no compile errors/warnings using all warning flags we used in our assignments

    For reference:
    > valgrind --tool=memcheck --leak-check=full --log-file=memcheck.log ./main

    Code efficiently but DO NOT RACE.  Your efficiency and effectiveness is
    a key outcome of this class.

    Your assignment:  WRITE the file exam2.c based this file exam2.h.
                      MODIFY the file main.c as described for problem 3 below.

 *** IF YOU DON'T SOLVE THE FUNCTIONS for PROBLEMS TWO and/or FOUR,    ***
 *** SUBMIT STUBS RETURNING NULL (or just returning in the case of the ***
 *** void function free_array).

*/
	
/*======================================================================*/
/*         Problem Zero                                                 */

/*  Write a Makefile for this assignment that compiles exam2.c and main.c
    into an executable file called main
*/



/*======================================================================*/
/*         Problem One  --  make_palindrome                             */
/* 
   arguments:
   
   const char * str  // a string to be made into a palindrome

   char ** palindrome // address of a char * pointer 
                      // that pointer is NULL or points to memory for result

   int * palindrome_len // length of entire memory available at
                        // **palindrome to if *palindrome isn't NULL

   If memory provided is insufficient then it must be freed.
   
   If no memory is provided, or what is provided is insufficient,
   make_palindrome must allocate exactly enough memory for its result,
   and set the values pointed to by palindrome and palindrome_len
   accordingly.

   WHAT IS THE DESIRED RESULT? 
   
   The desired result should be a copy of the first argument, char *
   str, followed by that same string in reverse except the final
   letter of the string is not repeated (in the center of the result).
   So the resulting string always has an odd length, or is empty if
   the original string was empty.
   
   example:
   
   if str points to "abc", the result (*palindrome) will point to "abcba".

 */
void make_palindrome(const char * str,  char ** palindrome, int * palindrome_len);

/*======================================================================*/
/*         Problem Two: split_string_by_array()  AND  free_array()


   free_array(char **array, int len)
      // must free all space used by array
      // and its contents, where array is a (char **) with 'len' elements.
      // this function is called by main.c to free result of split_string_by_array

   split_string_array Arguments:
   
   const char * s1   // a string.
   int * lens        // an integer array, all values are non-negative
   int numlens       // the (positive) number of integers in the array 'lens'


   Output:
   
   a (char **) pointing to an array of strings with 'numlens' elements.
   
   This function must allocate the space needed for the output array
   as well as each string in the output array.
   
   The 'numlens' strings of the output array are pieces of the input
   string 's1' as follows (read the examples below first).
   
   When the length of 's1' equals the sum of the elements of lens:

   (1) The i'th output string has length lens[i].  

   (2) The concatenation (i.e. implode()) of the output strings gives
       the input string 's1'.

   If the length of 's1' is greater than the sum of the elements of
   lens, then the unused part of 's1' is ignored.  In this case, the
   implode() of the output generates a prefix of 's1'. Condition (1)
   still holds.  See second example below.
  
   If the length of 's1' is less than the sum of lens[], then
   condition (1) is relaxed: the i'th output string is allowed to be less
   than lens[i], and if it is less then every later output string
   is the empty string.  Condition (2) stil holds. See third example.

   EXAMPLES:
   
   int x[5] = {1,1,3,0,1};
   split_string_by_array ("abcdef",x,5) returns an array with:
       "a", "b", "cde", "", "f"
       
   int y[3] = {1,2,1};
   split_string_by_array ("abcdefg",y,3) returns an array with:
       "a", "bc", "d"
  
   int z[3] = {1,2,1};
   split_string_by_array ("ab",z,3) returns an array with:
       "a", "b", ""
  
 */
void free_array(char **array, int len);
char ** split_string_by_array(const char * s1, int * lens, int numlens);

/*======================================================================*/
/*         Problem Three: 

       Modify main.c to add command line testing of make_palindrome

   Modify the main() function in main.c so that it accepts command
   line arguments.
   
   If there are no arguments other than the command itself:
    - do nothing other than proceed to the rest of main.

   If there is exactly one argument other than the command:

    - use that argument as an argument to make_palindrome and print
      the resulting string to standard output followed by a newline
      character.
 
      In this case, after running make_palindrome, RETURN 0 AND EXIT
      from the main() program without running the rest of main().
 
   If there are multiple arguments after the command (more than one),
   behave as though there were no arguments (ignore the arguments)
   unless you are solving problem 5 below.

   No modifications to exam2.c are needed for problem 3.

   Example usage:
   
   > ./main "amanaplanac"
   amanaplanacanalpanama
   > 
   
   Be sure there are no memory errors in the resulting main.c

 */



/*======================================================================*/
/*         Problem Four:  split_by_n                                                  

   Arguments:
   
   const char * s1   // a string.
   int n             // an integer guaranteed to be > 0.
   
   int * numFields   // a pointer to an integer in which you are to return the 
                     // size of the output array of char * pointers
		     
   Output:
   
   a (char **) pointing to an array of size (*numFields) of strings.
   
   This function must allocate the space needed for the output array
   as well as each string in the output array.
   
   Each string in the output array contains every n'th character from
   the input string, starting at a different start position, that is
   starting at positions between 0 and n-1.  If the input string is
   long enough, there will be 'n' of these strings, but there will be
   fewer when the length of 's1' is less than 'n'.

  Examples:
   
   int x;
   split_by_n("abcdefghij", 3, &x) 
       returns an array of 3 strings "adgj", "beh", and "cfi"
       and sets x to 3
       
   split_by_n("abcdefghij", 15, &x) 
       returns an array of 10 strings "a", "b", ..., "j" and
       sets x to 10.
       
   split_by_n("", 3, &x) sets x to 0 and returns NULL.
  
  If you don't write this function, place a stub here that returns
  NULL so that main will compile.

 */
char ** split_by_n (const char * s1, int n, int * numFields);


/*======================================================================*/
/*         Problem Five                                                

    Modify main.c to provide command-line testing of split_string_by_array  


  Maintain the behavior described in problem 3, except:
  
  If there is more than one command-line argument after the command,
  then run the test for split_string_by_array as described below.

  The first argument after the command is a string to split.

  The second argument after the command is a positive integer giving
  the number of array elements to follow.

  It is an error if the remaining arguments are not exactly that many
  array elements: all non-negative integers and exactly as many as
  specified.
  
  Each of the numeric arguments must be converted from string to int,
  detecting any error if they are not in fact non-negative integers.
  We recommend using strtol() for this conversion.  You can detect
  arguments that are not numeric using the test described on the man
  page for strtol(): "In particular, if *nptr is not '\0' but **endptr
  is '\0' on return, the entire string is valid."
  
  This processing code must print an error message to stderr if there
  is any error and return 1 from main();
  
  If all is in order, an array is created using the specified array
  elements and the string is split using split_string_by_array()

  The resulting strings are to be printed out in the order they
  appear in the array, with each string on a new line.

  > ./main "abcdef" 3 2 2 2
  ab
  cd
  ef
  > 

  Be sure to use free_array to avoid any memory errors.

 */

