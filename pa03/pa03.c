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
#include <string.h>
#include "answer03.h"

int main(int argc, char **argv)
{
  char * src;
  char * dest;
  char * result;
  int n;

  src="World!";
  dest=NULL;
  result=strcat_ex(&dest, &n, src);
  printf("src=\"World!\";\ndest=NULL;\nstrcat_ex(&dest, &n, src);\n --> gives %s with n=%d\n",result,n);
  result=strcat_ex(&dest, &n, "");
  printf("Then strcat_ex(&dest, &n, \"\") yields --> gives %s with n=%d\n",result,n);
  strcpy(dest,"abc");
  result=strcat_ex(&dest, &n, "def");
  printf("Then strcpy(dest,\"abc\"); strcat_ex(&dest, &n, \"def\") yields --> gives %s with n=%d\n",result,n);
  free(dest);

  int outlen;
  int my_index;
  char * glue;
  char * save;
  char **outstrings=explode("abc\tdef\fghi","\t\f",&outlen);
  printf("explode(\"abc\\tdef\\fghi\",\"\\t\\f\",&outlen); yields:\n");
  for (my_index=0; my_index<outlen; my_index++) {
    printf("\t%d:\"%s\"\n",my_index,outstrings[my_index]);
  }
  glue="";
  printf("implode with glue \"%s\" gives \"%s\"\n",glue,save=implode(outstrings,outlen,glue));
  free(save);
  printf("After sorting:\n");
  sortStringArray(outstrings,outlen);
  for (my_index=0; my_index<outlen; my_index++) {
    printf("\t%d:\"%s\"\n",my_index,outstrings[my_index]);
    free(outstrings[my_index]);
  }
  free(outstrings);

  outstrings=explode("abc\t\fghi","\t\f",&outlen);
  printf("explode(\"abc\\t\\fghi\",\"\\t\\f\",&outlen); yields:\n");
  for (my_index=0; my_index<outlen; my_index++) {
    printf("\t%d:\"%s\"\n",my_index,outstrings[my_index]);
  }
  glue="++";
  printf("implode with glue \"%s\" gives \"%s\"\n",glue,save=implode(outstrings,outlen,glue));
  free(save);
  printf("After sorting:\n");
  sortStringArray(outstrings,outlen);
  for (my_index=0; my_index<outlen; my_index++) {
    printf("\t%d:\"%s\"\n",my_index,outstrings[my_index]);
    free(outstrings[my_index]);
  }
  free(outstrings);

  outstrings=explode("abc\t\fghi","\f",&outlen);
  printf("explode(\"abc\\t\\fghi\",\"\\f\",&outlen); yields:\n");
  for (my_index=0; my_index<outlen; my_index++) {
    printf("\t%d:\"%s\"\n",my_index,outstrings[my_index]);
  }
  glue="|";
  printf("implode with glue \"%s\" gives \"%s\"\n",glue,save=implode(outstrings,outlen,glue));
  free(save);
  printf("After sorting:\n");
  sortStringArray(outstrings,outlen);
  for (my_index=0; my_index<outlen; my_index++) {
    printf("\t%d:\"%s\"\n",my_index,outstrings[my_index]);
    free(outstrings[my_index]);
  }
  free(outstrings);

  outstrings=explode("","\f",&outlen);
  printf("explode(\"\",\"\\f\",&outlen); yields:\n");
  for (my_index=0; my_index<outlen; my_index++) {
    printf("\t%d:\"%s\"\n",my_index,outstrings[my_index]);
  }
  glue="\t";
  printf("implode with glue \"%s\" gives \"%s\"\n",glue,save=implode(outstrings,outlen,glue));
  free(save);
  printf("After sorting:\n");
  sortStringArray(outstrings,outlen);
  for (my_index=0; my_index<outlen; my_index++) {
    printf("\t%d:\"%s\"\n",my_index,outstrings[my_index]);
    free(outstrings[my_index]);
  }
  free(outstrings);

  outstrings=explode("\f\f\f\f","\f",&outlen);
  printf("explode(\"\\f\\f\\f\\f\",\"\\f\",&outlen); yields:\n");
  for (my_index=0; my_index<outlen; my_index++) {
    printf("\t%d:\"%s\"\n",my_index,outstrings[my_index]);
  }
  glue="";
  printf("implode with glue \"%s\" gives \"%s\"\n",glue,save=implode(outstrings,outlen,glue));
  free(save);
  printf("After sorting:\n");
  sortStringArray(outstrings,outlen);
  for (my_index=0; my_index<outlen; my_index++) {
    printf("\t%d:\"%s\"\n",my_index,outstrings[my_index]);
    free(outstrings[my_index]);
  }
  free(outstrings);

  outstrings=explode("\f\f\f\f","",&outlen);
  printf("explode(\"\\f\\f\\f\\f\",\"\",&outlen); yields:\n");
  for (my_index=0; my_index<outlen; my_index++) {
    printf("\t%d:\"%s\"\n",my_index,outstrings[my_index]);
  }
  glue="|||";
  printf("implode with glue \"%s\" gives \"%s\"\n",glue,save=implode(outstrings,outlen,glue));
  free(save);
  printf("After sorting:\n");
  sortStringArray(outstrings,outlen);
  for (my_index=0; my_index<outlen; my_index++) {
    printf("\t%d:\"%s\"\n",my_index,outstrings[my_index]);
    free(outstrings[my_index]);
  }
  free(outstrings);

  return 0;
}
