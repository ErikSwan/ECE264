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

int main(int argc, char * * argv) {
    int i;

    for(i = 1; i < argc; i++) {
        printf(i == argc - 1 ? "%s" : "%s ", argv[i]);
    }

    printf("\n");
    return EXIT_SUCCESS;
}

