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

#include "exam3.h"

/*  SOLVE THE PROBLEMS IN ORDER IF POSSIBLE.  We don't guarantee fully
    counting solutions to later problems if earlier problems are unsolved.

    Minimum score guarantees: (actual score may be curved above this minimum)
    Problem One working:              60
    Problems One and Two working:     70
    Problems One, Two, Three working: 80
    Problems One thru Four working:   90
    Problems One thru Five working:  100

    5% deduction from this if you do not provide a working Makefile

    working = correct output on any tests we make up, and no valgrind errors.

    Also, no compile errors/warnings using all warning flags we used
    in our assignments, and no valgrind errors.

    Code efficiently but DO NOT RACE.  Your efficiency and effectiveness is
    a key outcome of this class.

    Your assignment:  WRITE the file exam3.c based this file exam2.h.
                      MODIFY the file main.c as described below.

*/


/*======================================================================*/
/*         Problem Zero -- write a Makefile
 *
 *  Write a Makefile for this assignment that compiles exam3.c and main.c
 *   into an executable file called main
 */


/*======================================================================
 *         Problem One -- write make_words() in exam3.c
 *
 * The function make_words accepts an array of strings (and an int
 * giving the array length) and generates words by choosing one
 * character from each string, in order, to construct a word.
 *
 * For each way of doing this, the function prints the resulting word
 * on a line by itself followed by a newline character.
 *
 * You may define and call other functions in order to implement make_words.
 *
 * Example:
 *
 * char *s1 = "abc";
 * char *s2 = "de";
 * char *s3 = "f";
 * (char *) (input[3]) = {s1, s2, s3};
 *
 * make_words(strings,3) will print:
 * adf
 * bdf
 * cdf
 * aef
 * bef
 * cef
 * WE PROVIDE A SCRIPT tester for you to test a few cases of your make_words
 * --write your own tests in main.c for further testing.
 */
void make_words(char **input, int inputlen) {
    char buffer[inputlen+1];

    void _make_recursive(char **_input, int _inputlen, char *_buffer, int offset) {
        int i,
            str_len = strlen(*_input);

        for(i = 0; i < str_len; i++) {
            _buffer[offset] = (*_input)[i];

            if(_inputlen == 1) {
                // Add the null terminator
                buffer[offset + 1] = '\0';
                // Print the completed word
                printf("%s\n", _buffer);
            } else {
                _make_recursive(_input + 1, _inputlen - 1, _buffer, offset + 1);
            }
        }
    }

    _make_recursive(input, inputlen, buffer, 0);
}


/*======================================================================
 *         Problem Two -- modify main.c
 *
 * Modify your main.c so that it accepts command-line arguments as
 * follows:
 *
 * If the first argument provided is the string -args, the remaining
 * arguments after that are used to call make_words with an array of
 * strings containing all the arguments after -args
 *
 * When the first argument is -args, your main() returns 0 after
 * running make_words, without proceeding to run any other tests.
 *
 * If the first argument is not -args, main() just proceeds, ignoring
 * the arguments, unless you also solve problem 3 below (see problem 3)
 *
 * > ./main -args abc de f
 * adf
 * bdf
 * cdf
 * aef
 * bef
 * cef
 * >
 *
 * THE SCRIPT tester tests a few cases of this problem.
 * --conduct your own tests from the command line for further testing.
 */


/*======================================================================
 *         Problem Three -- modify main.c
 *
 * Modify your main.c so that it accepts command-line arguments as
 * follows:
 *
 * If the first argument provided is the string -file, the next (and
 * last) argument is interpreted as a filename where the strings for
 * testing make_words() are to be found.
 *
 * That file is opened, and the lines in the file are all read into a
 * single array of strings, one for each line, which is then used as
 * an argument for make_words.  We recommend using getline() for this.
 * Your code must close the file.  You may assume the file has at most
 * 10 lines.
 *
 * hints on getline:
 *   1. be sure to remove the newline delimiter at the
 *      end of each line by overwriting it with '\0' when it is present.
 *   2. be sure to free the line buffer that getline created before finishing.
 *   3. Manage the space allocation carefully to not leak or overwrite memory.
 *
 * In this case, main() returns 0 without proceeding to run any other tests.
 *
 * If there is any error opening, closing, or reading from the file,
 * or if there are too few or too many arguments, main() must print an
 * error message of your choice to standard error and return the value 1.
 *
 * If the first argument is neither -args nor -file, then all
 * arguments are ignored and main() proceeds as before.
 *
 * So, if the file "testinput.txt" (provided as one test for you) has
 * abc
 * de
 * f
 * then the command will behave as follows:
 *
 * > ./main -file "testinput.txt"
 * adf
 * bdf
 * cdf
 * aef
 * bef
 * cef
 * >
 *
 * THE SCRIPT tester tests a few cases of this problem.
 * --conduct your own tests from the command line for further testing.
 */


/*======================================================================
 *    Problem Four -- write the function general_make_words() in exam3.c
 *
 * The main.c file contains program lines that call a function named
 * general_make_words(). These lines are in comments.  Remove the comment
 * marks to add these lines to the program.  Then, write the function
 * general_make_words() as follows.
 *
 * We are not providing a function prototype for general_make_words(),
 * you need to figure out the argument types from the calls in main().
 * The function returns an int.
 *
 * The difference between general_make_words and make_words is that
 * general_make_words accepts a third argument, which is a function
 * that can prune the generation of words.  The arguments to the
 * passed function are a string (the word so far) and a character
 * proposed to be added to that string.  No word should be generated
 * and printed by general_make_words unless the passed function
 * approves (by returning 1 instead of 0) each character to be added
 * to the prefix before that character.
 *
 * So, "abc" is generated only if the passed function returns 1 on
 * each of the following argument pairs:
 *
 *    "", 'a'
 *    "a", 'b'
 *    "ab", 'c'
 *
 * Your function must not generate all words and then perform these
 * tests, but is required to prune the generation where possible.
 *
 * ANOTHER difference from make_words is that general_make_words()
 * returns an int that must be the number of words printed.
 *
 * WE PROVIDE A SCRIPT tester for you to test a few cases of your
 * general_make_words
 *  --write your own tests in main.c for further testing.
 */
int general_make_words(char **input, int inputlen, int (*filter)(char * prefix, char extension)) {
    char buffer[inputlen+1];
    int wordcount = 0, j;

    // Zero out buffer
    for(j = 0; j < inputlen + 1; j++) {
        buffer[j] = '\0';
    }

    void _general_make_recursive(char **_input, int _inputlen, char *_buffer, int offset,
                                 int (*_filter)(char * prefix, char extension)) {
        int i,
            str_len = strlen(*_input);

        for(i = 0; i < str_len; i++) {
            // Need this because _filter doesn't take an offset, needs a null terminator in prefix
            _buffer[offset] = '\0';

            if(_filter(buffer, (*_input)[i])) {
                _buffer[offset] = (*_input)[i];

                if(_inputlen == 1) {
                    // Add the null terminator
                    buffer[offset + 1] = '\0';
                    // Print the completed word
                    printf("%s\n", _buffer);
                    wordcount++;
                } else {
                    _general_make_recursive(_input + 1, _inputlen - 1, _buffer, offset + 1, _filter);
                }
            }
        }
    }

    _general_make_recursive(input, inputlen, buffer, 0, filter);
    return wordcount;
}

/*======================================================================
 *     Problem Five -- code the function reachable_size in exam3.c
 *
 * reachable_size() accepts as input a two-dimensional array vals[] of
 * ints, along with the sizes maxrow, maxcol of each dimension, and a
 * particular row,col position in that array.
 *
 * The function must count how many different positions in the array
 * can be reached from the row,col position specified by repeatedly
 * adding or subtracting 2 from either the row or the col, but without
 * visiting a position where vals[] contains a non-zero element.
 *
 * If the specified row,col position has vals[]!=0 then the
 * returned value should be 0.
 *
 * For convenience, you may assume the vals[] array has been copied
 * before calling reachable_size(), so you may modify the array as you
 * proceed.
 *
 * For convenience, we provide below two functions that can be
 * used to lookup or set values in two dimensional integer arrays.
 *
 * int lookup(int * vals, int maxrows, int maxcols, int row, int col)
 * returns the value in vals at row,col
 *
 * int setval(int * vals, int maxrows, int maxcols, int row, int col, int newval)
 * sets the value in vals at row,col to the integer newval, returning newval.
 *
 * Example, shown with row,col == 0,0 at the upper left:
 * vals = 1 1 1 1 1
 *        1 0 1 0 1
 *        1 0 1 1 1
 *        1 1 1 0 1
 * the calls below give the values shown:
 *   reachable_size(vals,3,5,1,1) returns 3
 *   reachable_size(vals,3,5,1,3) returns 3
 *   reachable_size(vals,3,5,3,3) returns 3
 *   reachable_size(vals,3,5,3,1) returns 1
 *   reachable_size(vals,3,5,0,0) returns 0
 *   all other row,col arguments in range return 0.
 */
int reachable_size(int *vals, int maxrow, int maxcol, int row, int col) {
    return 0;
}

// YOU CAN USE THIS STUB IF YOU DON'T SOLVE THIS PROBLEM, TO AVOID COMPILE ERRORS
//int reachable_size(int *vals, int maxrow, int maxcol, int row, int col)
//{
//  int ignore = vals[0]+maxrow+maxcol+row+col;
//  return 0*ignore;
//}

// You can use the following two functions in your exam.c for convenience
// int lookup(int * vals, int maxrows, int maxcols, int row, int col)
// {
//   UNUSED(maxrows);
//   return vals[row*maxcols+col];
// }

// int setval(int * vals, int maxrows, int maxcols, int row, int col, int newval)
// {
//   UNUSED(maxrows);
//   return (vals[row*maxcols+col]=newval);
// }
