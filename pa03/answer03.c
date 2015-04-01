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

#include "answer03.h"

/**
 * Append the C-string 'src' to the end of the C-string '*dest'.
 *
 * strcat_ex(...) will append the C-string 'src' to the end of the string
 * at '*dest'. The parameter 'n' is the address of a int that specifies how
 * many characters can safely be stored in '*dest'.
 *
 * If '*dest' is NULL, or if '*dest' is not large enough to contain the result
 * (that is, the sum of the lengths of *dest, src, and the null byte), then
 * strcat_ex will:
 * (1) malloc a new buffer of size 1 + 2 * (strlen(*dest) + strlen(src))
 * (2) set '*n' to the size of the new buffer
 * (3) copy '*dest' into the beginning of the new buffer
 * (4) free the memory '*dest', and then set '*dest' to point to the new buffer
 * (5) concatenate 'src' onto the end of '*dest'.
 *
 * Always returns *dest.
 *
 * Why do we need to pass dest as char * *, and n as int *?
 * Please see the FAQ for an answer.
 *
 * Hint: These <string.h> functions will help: strcat, strcpy, strlen.
 * Hint: Leak no memory.
 */
char * strcat_ex(char * * dest, int * n, const char * src) {
    char * buffer;
    if((!*dest) || (strlen(src) + strlen(*dest) + 1 > *n)) {
        *n = 1 + 2 * ((!*dest ? 0 : strlen(*dest)) + strlen(src));
        buffer = malloc(*n * sizeof(char));
        *buffer = '\0';
        if(*dest) {
            strcpy(buffer, *dest);
        }
        // Since we are going to be changing *dest and are unsure of the memory
        // that it points to's location (could be stack or heap), deallocate it
        // to prevent a memory leak.
        free(*dest);
        // Update *dest to point to the new buffer.
        *dest = buffer;
    }

    // We can use strcat without worrying about overflow because we KNOW (from
    // above) that *dest has enough room.
    strcat(*dest, src);
    return *dest;
}

/**
 * Takes a string and splits it into an array of strings according to delimiter.
 * The memory location '*arrLen' is initialized to the length of the returned
 * array.
 *
 * str: A string to split
 * delims: a string that contains a set of delimiter characters. explode(...)
 *         will split the string at any character that appears in 'delims'.
 * arrLen: pointer to an int that is used to store the resultant length of the
 *         returned array.
 *
 * For example, if delimiter is white space " \t\v\n\r\f", then,
 * int len;
 * char * * strArr = explode("The\nTuring test", " \t\v\n\r\f", &len);
 * // len = 3, strArr[0] is "The", strArr[1] is "Turing", strArr[2] is "test"
 *
 * Hint: you can use <string.h> functions "memcpy" and "strchr"
 *       "memcpy" copies blocks of memory.
 *       "strchr" can be used to tell if a specific character is in delims.
 * Hint: this question is hard; it will help to draw out your algorithm.
 * Hint: read the FAQ...
 */
char * * explode(const char * str, const char * delims, int * arrLen) {
    int i, segLen = 0, delimCount = 0;

    // Count delimiters to determine length of necessary array
    for(i = 0; *(str + i) != '\0'; i++) {
        if(strchr(delims, *(str + i)) != NULL) {
            delimCount++;
        }
    }

    // Malloc the array of strings
    char ** strArr = malloc((delimCount + 1) * sizeof(char *));
    delimCount = 0;

    // Go back and split the string
    for(i = 0; *(str + i) != '\0'; i++) {
        if(strchr(delims, *(str + i)) != NULL) {
            // Make some memory for this segment
            *(strArr + delimCount) = malloc((segLen + 1) * sizeof(char)); // + 1 is for null byte

            // Copy the segment to the allocated memory
            if(segLen) {
                memcpy(*(strArr + delimCount), str + i - segLen, segLen * sizeof(char));
            }

            // Set null byte
            strArr[delimCount][segLen] = '\0';

            // Reset segLen and increment delimCount
            segLen = 0;
            delimCount++;
        } else {
            segLen++;
        }
    }

    // Copy the last segment
    *(strArr + delimCount) = malloc((segLen + 1) * sizeof(char));
    memcpy(*(strArr + delimCount), str + i - segLen, segLen * sizeof(char));

    // Set null byte
    strArr[delimCount][segLen] = '\0';

    *arrLen = delimCount + 1;
    return strArr;
}

/**
 * Takes an array of strings, and concatenates the elements into a single
 * string, placing 'glue' between each successive element.
 *
 * strArr: an array of strings
 * len: the length of the array 'strArr'
 * glue: string to concatenate between each element of 'strArr'
 *
 * For example:
 * int len;
 * char * * strArr = explode("100 224 147 80", " ", &len);
 * char * str = implode(strArr, len, ", ");
 * printf("(%s)\n", str); // (100, 224, 147, 80)
 *
 * Hint: use strcat_ex in a for loop.
 */
char * implode(char * * strArr, int len, const char * glue) {
    int totalLength, i;
    totalLength = (len - 1) * strlen(glue) + 1;

    for(i = 0; i < len; i++) {
        totalLength += strlen(*(strArr + i));
    }

    char * concatString = malloc(totalLength * sizeof(char));
    *concatString = '\0';

    for(i = 0; i < len - 1; i++) {
        strcat_ex(&concatString, &totalLength, *(strArr + i));
        strcat_ex(&concatString, &totalLength, glue);
    }

    // Append last piece
    strcat_ex(&concatString, &totalLength, *(strArr + i));

    return concatString;
}

/**
 * Takes an array of C-strings, and sorts them alphabetically, ascending.
 *
 * arrString: an array of strings
 * len: length of the array 'arrString'
 *
 * For example,
 * int len;
 * char * * strArr = explode("lady beatle brew", " ", &len);
 * sortStringArray(strArr, len);
 * char * str = implode(strArr, len, " ");
 * printf("%s\n", str); // beatle brew lady
 *
 * Hint: use the <stdlib.h> function "qsort"
 * Hint: you must _clearly_ understand the typecasts.
 */
void sortStringArray(char * * arrString, int len) {
    // Define the comparison function
    // Note: nested functions are a gcc language extension.
    int compareStrings(const void * a, const void * b) {
        const char ** A = (const char **) a;
        const char ** B = (const char **) b;
        int i;
        for(i = 0; *(*A + i) == *(*B + i); i++) {
            if(*(*A + i) == '\0') {
                return 0;
            }
        }
        return 2 * (*(*A + i) > *(*B + i)) - 1;
    }

    // Sort everything!
    qsort(arrString, len, sizeof(char *), compareStrings);
}

/**
 * Sorts the characters in a string.
 *
 * str: string whose characters are to be sorted
 *
 * For example,
 * char * s1 = strdup("How did it get so late so soon?");
 * sortStringCharacters(s1)
 * // s1 is now "       ?Haddeegiilnooooossstttw"
 *
 * Hint: use the <stdlib.h> function "qsort"
 * Hint: you must _clearly_  understand the typecasts.
 */
void sortStringCharacters(char * str) {
    int len;

    int compareCharacters(const void * a, const void * b) {
        const char * A = (const char *) a;
        const char * B = (const char *) b;
        if(*A < *B) {
            return -1;
        } else if(*A == *B) {
            return 0;
        } else {
            return 1;
        }
    }

    len = strlen(str);

    // Sort everything!
    qsort(str, len, sizeof(char), compareCharacters);
}

/**
 * Safely frees all memory associated with strArr, and then strArr itself.
 * Passing NULL as the first parameter has no effect.
 *
 * strArr: an array of strings
 * len: the length of 'strArr'
 *
 * int len;
 * const char * abe = "Give me six hours to chop down a tree and I will spend\n"
 *                    "the first four sharpening the axe.";
 * char * * strArr = explode(abe, "\n ");
 * destroyStringArray(strArr, len); // cleans memory -- no memory leaks
 * destroyStringArray(NULL, 0); // does nothing, does not crash.
 */
void destroyStringArray(char * * strArr, int len) {
    int i;

    for(i = 0; i < len; i++) {
        free(*(strArr + i));
    }
    free(strArr);
}
