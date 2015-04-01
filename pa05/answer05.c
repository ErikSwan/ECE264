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

#include "answer05.h"
#include <stdio.h>
#include <string.h>

#define TRUE    1
#define FALSE   0

/**
 * Function designed to do the actual partition computation. Should be
 * passed a int* to act as the partition buffer, an offset denoting the piece of
 * the buffer that has yet to be partitioned, and an arbitrary comparison
 * function for filtering partition generation.
 *
 * int (*comparator)(...) accepts the current partition, an offset pointing to
 * the place for the next value to be added to the partition, and the proposed
 * value to be added to the partition. If the proposed value violates any rules
 * imposed on partition generation, then (*comparator) should return FALSE,
 * otherwise it should return TRUE.
 */
void partitionGeneric(int value, int * partition, int offset,
                      int (*comparator)(int nextValue, int * partition, int offset)) {
    int i;

    if(value == 0) {
        // Print completed partition
        printf("= ");
        for(i = 0; i < offset - 1; i++) {
            printf("%d + ", partition[i]);
        }
        printf("%d\n", partition[offset-1]);
    } else {
        for(i = 1; i <= value; i++) {
            // Check partition
            if(comparator(i, partition, offset)) {
                // Update partition
                partition[offset] = i;

                // Generate sub-partition
                partitionGeneric(value - i, partition, offset + 1, comparator);
            }
        }
    }
}

/**
 * Prints all the partitions of a positive integer value.
 *
 * Example:
 * partitionAll(3); // prints the following: (line order not important)
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 *
 * Note: Order does not matter, and neither does white-space.
 * Hint: look at file: expected/partitionAll.output
 */
void partitionAll(int value) {
    int _acceptAll(int nextValue, int * partition, int offset) { return 1; }

    int partition[value];
    partitionGeneric(value, partition, 0, _acceptAll);
}

/**
 * Prints all partitions that have strictly increasing values.
 *
 * Example:
 * partitionIncreasing(5); // prints the following: (line order not important)
 * = 1 + 4
 * = 2 + 3
 * = 5
 *
 * These partitions are excluded because they are not _strictly_ increasing
 * 1 + 1 + 3
 * 2 + 1 + 2
 * 3 + 2
 *
 * Note:
 * The program should generate only valid partitions.  Do not
 * generates all partitions and then filter for validity. If you
 * do this, you will almost certainly have trouble understanding the exam.
 *
 * Hint: look at file: expected/partitionIncreasing.output
 */
void partitionIncreasing(int value) {
    int _acceptIncreasing(int nextValue, int * partition, int offset) {
        return offset == 0 || nextValue > partition[offset - 1];
    }

    int partition[value];
    partitionGeneric(value, partition, 0, _acceptIncreasing);
}

/**
 * Prints all partitions that have strictly decreasing values.
 *
 * Example:
 * partitionDecreasing(5); // prints the following: (line order not important)
 * = 3 + 2
 * = 4 + 1
 * = 5
 *
 * These partitions are excluded because they are not _strictly_ decreasing
 * 1 + 1 + 3
 * 2 + 1 + 2
 *
 * See: note on partitionIncreasing(...)
 * Hint: look at file: expected/partitionDecreasing.output
 */
void partitionDecreasing(int value) {
    int _acceptDecreasing(int nextValue, int * partition, int offset) {
        return offset == 0 || nextValue < partition[offset - 1];
    }

    int partition[value];
    partitionGeneric(value, partition, 0, _acceptDecreasing);
}

/**
 * Prints all partitions comprised solely of odd numbers.
 *
 * Example:
 * partitionOdd(5); // prints the following (line order not important)
 * = 1 + 1 + 1 + 1 + 1
 * = 1 + 1 + 3
 * = 1 + 3 + 1
 * = 3 + 1 + 1
 * = 5
 *
 * See: note on partitionIncreasing(...)
 * Hint: for odd numbers, (value % 2 != 0)
 * Hint: look at file: expected/partitionOdd.output
 */
void partitionOdd(int value) {
    int _acceptOdd(int nextValue, int * partition, int offset) {
        return (nextValue % 2) == 1;
    }

    int partition[value];
    partitionGeneric(value, partition, 0, _acceptOdd);
}

/**
 * Prints all partitions comprised solely of even numbers.
 *
 * Example:
 * partitionEven(6); // prints the following (line order not important)
 * = 2 + 2 + 2
 * = 2 + 4
 * = 4 + 2
 * = 6
 *
 * See: note on partitionIncreasing(...)
 * Hint: for even numbers, (value % 2 == 0)
 * Hint: you can never partition an odd number with even numbers alone.
 * Hint: look at file: expected/partitionEven.output
 */
void partitionEven(int value) {
    int _acceptEven(int nextValue, int * partition, int offset) {
        return nextValue % 2 == 0;
    }

    int partition[value];
    partitionGeneric(value, partition, 0, _acceptEven);
}

/**
 * Prints all partitions that do not have consecutive odd or even numbers.
 * In other words, it only prints partitions that have alternating odd and
 * even numbers.
 *
 * Example:
 * partitionOddAndEven(5); // prints the following (line order not important)
 * = 1 + 4
 * = 2 + 1 + 2
 * = 2 + 3
 * = 3 + 2
 * = 4 + 1
 * = 5
 *
 * See: note on partitionIncreasing(...)
 * Hint: look at file: expected/partitionOddAndEven.output
 */
void partitionOddAndEven(int value) {
    int _acceptOddAndEven(int nextValue, int * partition, int offset) {
        if(offset > 0) {
            return (nextValue % 2) ^ (partition[offset-1] % 2);
        } else {
            return TRUE;
        }
    }

    int partition[value];
    partitionGeneric(value, partition, 0, _acceptOddAndEven);
}

/**
 * Prints all partitions that comprise solely of prime numbers.
 *
 * Example:
 * partitionPrime(5); // prints the following (line order not important)
 * = 2 + 3
 * = 3 + 2
 * = 5
 *
 * See: note on partitionIncreasing(...)
 * Hint: you will need to write a function that checks if a number is prime.
 * Hint: 1 is not a prime number.
 * Hint: look at file: expected/partitionPrime.output
 */
void partitionPrime(int value) {
    int _acceptPrime(int nextValue, int * partition, int offset) {
        int i;

        // Simple primality test
        if(nextValue <= 3) {
            return nextValue >= 2;
        }
        if(nextValue % 2 == 0 || nextValue % 3 == 0) return FALSE;
        else {
            for(i = 5; i*i < nextValue; i += 6) {
                if(nextValue % i == 0 || (nextValue + 2) % i == 0) {
                    return FALSE;
                }
            }
            return TRUE;
        }
    }

    int partition[value];
    partitionGeneric(value, partition, 0, _acceptPrime);
}
