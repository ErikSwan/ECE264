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
#include <stdio.h>
#include <string.h>
#include <libgen.h>

#include "answer07.h"

void print_usage(char * argv0)
{
    printf("\n"
	   "   Usage: %s <in-filename> <out-filename> <present if normalization desired>\n"
	   "\n"
	   "      Reads image file <in-filename> and then:\n"
	   "      (1) Converts it to grayscale\n"
	   "      (2) Normalizes if <present...> is present\n"
	   "      (3) Writes (normalized) image to <out-filename>\n"
	   "      File format is determined by extension, required in {ee264,bmp}"
	   "\n",
	   basename(argv0));
}

char * file_extension(const char * filename)
{
  char *dot_tail = strrchr(filename, '.');

  if ((!dot_tail) || (dot_tail==filename)) return NULL;

  return dot_tail+1;
}

/**
 * Welcome to PA07.
 *
 */
int main(int argc, char * * argv)
{
    int ret = EXIT_SUCCESS; // unless otherwise noted

    // Parse input arguments
    if((argc != 3) && (argc != 4)) {
	print_usage(argv[0]);
	if(argc == 2 && strcmp(argv[1], "--help") == 0)
	    return EXIT_SUCCESS;
	return EXIT_FAILURE;
    }

    int normalizeRequested = (argc==4);
    const char * in_filename = argv[1];
    const char * out_filename = argv[2];

    char *extension=file_extension(in_filename);
    int isInBmp = (strcmp(extension,"bmp")==0);
    int isInEE264 = (strcmp(extension,"ee264")==0);
    if (!(isInBmp || isInEE264)) {
      printf("Input file \"%s\" must have either bmp or ee264 extension\n",in_filename);
      return EXIT_FAILURE;
    }

    extension=file_extension(out_filename);
    int isOutBmp = (strcmp(extension,"bmp")==0);
    int isOutEE264 = (strcmp(extension,"ee264")==0);
    if (!(isOutBmp || isOutEE264)) {
      printf("Output file \"%s\" must have either bmp or ee264 extension\n",out_filename);
      return EXIT_FAILURE;
    }

    // Read the file
    Image * im = (isInBmp ? Image_loadbmp(in_filename) : Image_load(in_filename));
    if(im == NULL) {
	fprintf(stderr, "Error: failed to read '%s'\n", in_filename);
	return EXIT_FAILURE;
    }

    // normalize
    if (normalizeRequested) linearNormalization(im->width, im->height, im->data);

    // Write out a new file
    if (!(isOutBmp ? Image_savebmp(out_filename, im) : Image_save(out_filename, im))) {
	fprintf(stderr, "Error attempting to write '%s'\n", out_filename);
	ret = EXIT_FAILURE;
    }

    Image_free(im);

    return ret;
}
