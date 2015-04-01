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

#include <stdlib.h>
#include "answer01.h"

int arraySum(int * array, int len) {
    int sum = 0;
    int i;
	for(i = 0; i < len; i++) {
        sum += array[i];
    }
    return sum;
}

int arrayCountNegative(int * array, int len) {
    int count = 0;
    int i;
	for(i = 0; i < len; i++) {
        count += (array[i] < 0);
    }
    return count;
}

int arrayIsIncreasing(int * array, int len) {
    int i;
	for(i = 0; i < len; i++) {
        if(i != 0 && array[i] < array[i-1]) {
            return 0;
        }
    }
    return 1;
}

int arrayIndexRFind(int needle, const int * haystack, int len) {
    int greatestIndex = -1;
    int i;
	for(i = 0; i < len; i++) {
        if(haystack[i] == needle && i > greatestIndex) {
            greatestIndex = i;
        }
    }
    return greatestIndex;
}

int arrayFindSmallest(int * array, int len) {
    int smallestIndex = (len <= 0) ? 0 : len-1;
    int smallestValue = (len <= 0) ? 0 : array[len-1];
    int i;
    for(i = len - 2; i >= 0; i--) {
        if(array[i] <= smallestValue) {
            smallestValue = array[i];
            smallestIndex = i;
        }
    }
    return smallestIndex;
}
