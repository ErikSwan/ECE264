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

#include "answer05.h"

int main(int argc, char **argv)
{
  printf("partitionAll(2) is\n");
  partitionAll(2);

  printf("partitionAll(3) is\n");
  partitionAll(3);

  printf("partitionAll(5) is\n");
  partitionAll(5);

  printf("partitionAll(10) is\n");
  partitionAll(10);

  printf("======================================================================\n");

  printf("partitionIncreasing(5) is\n");
  partitionIncreasing(5);

  printf("partitionIncreasing(10) is\n");
  partitionIncreasing(10);

  printf("======================================================================\n");

  printf("partitionDecreasing(5) is\n");
  partitionDecreasing(5);

  printf("partitionDecreasing(10) is\n");
  partitionDecreasing(10);

  printf("======================================================================\n");

  printf("partitionOdd(5) is\n");
  partitionOdd(5);

  printf("partitionOdd(10) is\n");
  partitionOdd(10);

  printf("======================================================================\n");

  printf("partitionEven(5) is\n");
  partitionEven(5);

  printf("partitionEven(10) is\n");
  partitionEven(10);

  printf("======================================================================\n");

  printf("partitionOddAndEven(5) is\n");
  partitionOddAndEven(5);

  printf("partitionOddAndEven(10) is\n");
  partitionOddAndEven(10);

  printf("======================================================================\n");

  printf("partitionPrime(5) is\n");
  partitionPrime(5);

  printf("partitionPrime(7) is\n");
  partitionPrime(7);

  printf("partitionPrime(10) is\n");
  partitionPrime(10);

  return 0;
}
