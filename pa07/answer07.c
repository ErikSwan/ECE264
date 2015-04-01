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

#include "answer07.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Loads an ECE264 image file, returning an Image structure.
 * Will return NULL if there is any error.
 *
 * Hint: Please see the README for extensive hints
 */
Image * Image_load(const char * filename) {
    FILE * fp;
    ImageHeader header;
    Image image;

    // Open file for reading
    fp = fopen(filename, "r");
    if(!fp) {
        fprintf(stderr, "Cannot open file '%s' for reading.", filename);
        return NULL;
    }

    // Read the header
    if(fread(&header, sizeof(ImageHeader), 1, fp) != 1) {
        fprintf(stderr, "Unable to read header.");
        return NULL;
    }

    // Check the header's validity
    if(header.magic_number != ECE264_IMAGE_MAGIC_NUMBER) {
        fprintf(stderr, "Magic number in header does not match.");
        return NULL;
    }

    // Check width and height
    if(header.width <= 0 || header.height <= 0) {
        fprintf(stderr, "Image file is not of valid width or height.");
        return NULL;
    }

    // Validate comment
    if(header.comment_len < 1) {
        fprintf(stderr, "Comment length in header is invalid.");
        return NULL;
    }

    // Read the comment
    image.comment = malloc(header.comment_len * sizeof(char));
    if(fread(image.comment, header.comment_len, 1, fp) != 1) {
        fprintf(stderr, "Cannot read comment.");
        free(image.comment);
        return NULL;
    }

    // Read the image data
    image.data = malloc(header.width * header.height * sizeof(uint8_t));
    if(fread(image.data, header.width * header.height, 1, fp) != 1) {
        fprintf(stderr, "Cannot read pixel data.");
        free(image.data);
    // NOT DONE

    return NULL;
}

/**
 * Save an image to the passed filename, in ECE264 format.
 * Return TRUE if this succeeds, or FALSE if there is any error.
 *
 * Hint: Please see the README for extensive hints
 */
int Image_save(const char * filename, Image * image) {
    return 0;
}

/**
 * Free memory for an image structure
 *
 * Image_load(...) (above) allocates memory for an image structure.
 * This function must clean up any allocated resources. If image is
 * NULL, then it does nothing. (There should be no error message.) If
 * you do not write this function correctly, then valgrind will
 * report an error.
 */
void Image_free(Image * image) {
    return;
}

/**
 * Performs linear normalization, see README
 */
void linearNormalization(int width, int height, uint8_t * intensity) {
    return;
}

