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
#include "exam2.h"

void test_split_by_n()
{
  printf("Testing split_string_by_n\n\n");

  int correct, i;

  ///(const char * s1, int n, int * numFields)

  int len;

  int answer1_len=2;
  char *answer1[2] = {"ace", "bdf"};
  char **result=split_by_n("abcdef",2,&len);
  if (result==NULL) return;

  printf("split_by_n on \"abcdef\" with n=2 returns numFields=%d:\n", len);
  for (i=0;i<len;i++) printf("   \"%s\"%s",result[i], (i==len-1 ? "" : ", "));
  correct=(len==answer1_len);
  for (i=0;i<len;i++) correct = correct && (strcmp(answer1[i],result[i])==0);
  printf("     (%s)\n\n",correct ? "Correct" : "Failed");
  free_array(result,len);

  int answer2_len=3;
  char *answer2[3] = {"ad", "be", "cf"};
  result=split_by_n("abcdef",3,&len);

  printf("split_by_n on \"abcdef\" with n=3 returns numFields=%d:\n", len);
  for (i=0;i<len;i++) printf("   \"%s\"%s",result[i], (i==len-1 ? "" : ", "));
  correct=(len==answer2_len);
  for (i=0;i<len;i++) correct = correct && (strcmp(answer2[i],result[i])==0);
  printf("     (%s)\n\n",correct ? "Correct" : "Failed");
  free_array(result,len);

  int answer3_len=4;
  char *answer3[4] = {"ae", "bf", "c", "d"};
  result=split_by_n("abcdef",4,&len);

  printf("split_by_n on \"abcdef\" with n=4 returns numFields=%d:\n", len);
  for (i=0;i<len;i++) printf("   \"%s\"%s",result[i], (i==len-1 ? "" : ", "));
  correct=(len==answer3_len);
  for (i=0;i<len;i++) correct = correct && (strcmp(answer3[i],result[i])==0);
  printf("     (%s)\n\n",correct ? "Correct" : "Failed");
  free_array(result,len);

  int answer4_len=6;
  char *answer4[6] = {"a", "b", "c", "d", "e", "f"};
  result=split_by_n("abcdef",8,&len);

  printf("split_by_n on \"abcdef\" with n=8 returns numFields=%d:\n", len);
  for (i=0;i<len;i++) printf("   \"%s\"%s",result[i], (i==len-1 ? "" : ", "));
  correct=(len==answer4_len);
  for (i=0;i<len;i++) correct = correct && (strcmp(answer4[i],result[i])==0);
  printf("     (%s)\n\n",correct ? "Correct" : "Failed");
  free_array(result,len);

  int answer5_len=0;
  result=split_by_n("",7,&len);

  printf("split_by_n on \"\" with n=7 returns numFields=%d:\n", len);
  for (i=0;i<len;i++) printf("   \"%s\"%s",result[i], (i==len-1 ? "" : ", "));
  correct=(len==answer5_len) && result==NULL;
  printf("     (%s)\n\n",correct ? "Correct" : "Failed");
  free_array(result,len);

  int answer6_len=2;
  char *answer6[2] = {"a", "b"};
  result=split_by_n("ab",7,&len);

  printf("split_by_n on \"ab\" with n=7 returns numFields=%d:\n", len);
  for (i=0;i<len;i++) printf("   \"%s\"%s",result[i], (i==len-1 ? "" : ", "));
  correct=(len==answer6_len);
  for (i=0;i<len;i++) correct = correct && (strcmp(answer6[i],result[i])==0);
  printf("     (%s)\n\n",correct ? "Correct" : "Failed");
  free_array(result,len);

  int answer7_len=1;
  char *answer7[1] = {"a"};
  result=split_by_n("a",3,&len);

  printf("split_by_n on \"a\" with n=3 returns numFields=%d:\n", len);
  for (i=0;i<len;i++) printf("   \"%s\"%s",result[i], (i==len-1 ? "" : ", "));
  correct=(len==answer7_len);
  for (i=0;i<len;i++) correct = correct && (strcmp(answer7[i],result[i])==0);
  printf("     (%s)\n\n",correct ? "Correct" : "Failed");
  free_array(result,len);

  int answer8_len=1;
  char *answer8[1] = {"a"};
  result=split_by_n("a",1,&len);

  printf("split_by_n on \"a\" with n=1 returns numFields=%d:\n", len);
  for (i=0;i<len;i++) printf("   \"%s\"%s",result[i], (i==len-1 ? "" : ", "));
  correct=(len==answer8_len);
  for (i=0;i<len;i++) correct = correct && (strcmp(answer8[i],result[i])==0);
  printf("     (%s)\n\n",correct ? "Correct" : "Failed");
  free_array(result,len);
}

void test_split_string_by_array()
{
  printf("Testing split_string_by_array\n\n");

  int correct, i;

  int len=5;
  int x[5] = {1,1,3,0,1};
  char *answer1[5] = {"a", "b", "cde", "", "f"};
  char **result=split_string_by_array("abcdef",x,len);
  if (result==NULL) return;

  printf("split_string_by_array on \"abcdef\" with 1,1,3,0,1 returns:\n");
  for (i=0;i<len;i++) printf("   \"%s\"%s",result[i], (i==len-1 ? "" : ", "));
  correct=1;
  for (i=0;i<len;i++) correct = correct && (strcmp(answer1[i],result[i])==0);
  printf("     (%s)\n\n",correct ? "Correct" : "Failed");
  free_array(result,len);

  len=3;
  int y[3] = {1,2,1};
  char *answer2[3] = {"a", "bc", "d"};
  result=split_string_by_array("abcdef",y,len);

  printf("split_string_by_array on \"abcdef\" with 1,2,1 returns:\n");
  for (i=0;i<len;i++) printf("   \"%s\"%s",result[i], (i==len-1 ? "" : ", "));
  correct=1;
  for (i=0;i<len;i++) correct = correct && (strcmp(answer2[i],result[i])==0);
  printf("     (%s)\n\n",correct ? "Correct" : "Failed");
  free_array(result,len);

  len=3;
  int z[3] = {1,2,1};
  char *answer3[3] = {"a", "b", ""};
  result=split_string_by_array("ab",z,len);

  printf("split_string_by_array on \"ab\" with 1,2,1 returns:\n");
  for (i=0;i<len;i++) printf("   \"%s\"%s",result[i], (i==len-1 ? "" : ", "));
  correct=1;
  for (i=0;i<len;i++) correct = correct && (strcmp(answer3[i],result[i])==0);
  printf("     (%s)\n\n",correct ? "Correct" : "Failed");
  free_array(result,len);
}

void test_make_palindrome()
{
  char *output = NULL;
  int output_len;

  printf("Testing make_palindrome\n\n");

  make_palindrome("hello", &output, &output_len);
  printf("make_palindrome \"hello\" with NULL buffer"
	 " returns \"%s\" with len %d (%s)\n", output, output_len,
	 strcmp(output,"hellolleh")==0 && output_len==10 ? "Correct" : "Failed");

  make_palindrome("abc", &output, &output_len);
  printf("make_palindrome \"abc\" with previous buffer"
	 " returns \"%s\" with len %d (%s)\n", output, output_len,
	 strcmp(output,"abcba")==0 && output_len==10 ? "Correct" : "Failed");

  make_palindrome("hello", &output, &output_len);
  printf("make_palindrome \"hello\" with previous buffer"
	 " returns \"%s\" with len %d (%s)\n", output, output_len,
	 strcmp(output,"hellolleh")==0 && output_len==10 ? "Correct" : "Failed");

  make_palindrome("helloX", &output, &output_len);
  printf("make_palindrome \"helloX\" with previous buffer"
	 " returns \"%s\" with len %d (%s)\n", output, output_len,
	 strcmp(output,"helloXolleh")==0 && output_len==12 ? "Correct" : "Failed");

  free(output);
  output=NULL;

  make_palindrome("", &output, &output_len);
  printf("make_palindrome \"\" with NULL buffer"
	 " returns \"%s\" with len %d (%s)\n", output, output_len,
	 strcmp(output,"")==0 && output_len==1 ? "Correct" : "Failed");

  free(output);
  output=NULL;

  make_palindrome("a", &output, &output_len);
  printf("make_palindrome \"\" with NULL buffer"
	 " returns \"%s\" with len %d (%s)\n", output, output_len,
	 strcmp(output,"a")==0 && output_len==2 ? "Correct" : "Failed");

  free(output);
  output=NULL;
}

int main (int argc, char **argv)
{
    if(argc == 2) {
        char *output = NULL;
        int output_len;
        make_palindrome(argv[1], &output, &output_len);
        printf("%s\n", output);
        free(output);
        return EXIT_SUCCESS;
    }

  //if (argc>1) {
  //  char *output = NULL;
  //  int output_len;
  //  make_palindrome(argv[1], &output, &output_len);
  //  printf("%s\n",output);
  //  free(output);
  //}

  //if (argc>2) {
  //  if (argc<5) {fprintf(stderr,"Not enough args\n"); return 1;}
  //  char *string_to_split = argv[2];
  //  char *endptr=NULL;
  //  int numlens = strtol(argv[3],&endptr,10);
  //  if ((*endptr)!='\0') {fprintf(stderr,"Number of lens ill-formed\n"); return 1;}
  //
  //  if (argc<3+numlens) {fprintf(stderr,"Not enough args\n"); return 1;}
  //  int *array = malloc(sizeof(int)*numlens);
  //  int index;
  //  for(index=0; index<numlens; index++) {
  //    array[index] = strtol(argv[4+index],&endptr,10);
  //    if ((*endptr)!='\0') {fprintf(stderr,"Ill-formed len\n"); return 1;}
  //  }
  //
  //char **result=split_string_by_array(string_to_split,array,numlens);
  //int i;
  //for (i=0;i<numlens;i++) printf("\"%s\"%s",result[i], (i==numlens-1 ? "" : " "));
  //free_array(result,numlens);
  //free(array);
  //}

  printf("\n======================================================================\n\n");

  test_make_palindrome();

  printf("\n======================================================================\n\n");

  test_split_string_by_array();

  printf("\n======================================================================\n\n");

  test_split_by_n();

  printf("\n======================================================================\n\n");

  return 0;

}


