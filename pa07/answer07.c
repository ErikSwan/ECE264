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
#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * Loads an ECE264 image file, returning an Image structure.
 * Will return NULL if there is any error.
 *
 * Hint: Please see the README for extensive hints
 */
Image * Image_load(const char * filename) {
    FILE * fp = NULL;
    ImageHeader header;
    Image * image = NULL;

    void _teardown() {
        if(image) {
            Image_free(image);
            image = NULL;
        }
        fclose(fp);
    }

    // Open file for reading
    fp = fopen(filename, "rb");
    if(!fp) {
        fprintf(stderr, "Cannot open file '%s' for reading.\n", filename);
        return image;
    }

    // Read the header
    if(fread(&header, sizeof(ImageHeader), 1, fp) != 1) {
        fprintf(stderr, "Unable to read header.\n");
        _teardown();
        return image;
    }

    // Check the header's validity
    if(header.magic_number != ECE264_IMAGE_MAGIC_NUMBER) {
        fprintf(stderr, "Magic number in header does not match.\n");
        _teardown();
        return image;
    }

    // Check width and height
    if(header.width <= 0 || header.height <= 0) {
        fprintf(stderr, "Image file is not of valid width or height.\n");
        _teardown();
        return image;
    }

    // Validate comment
    if(header.comment_len < 1 || header.comment_len > 1024) {
        fprintf(stderr, "Comment length in header is invalid.\n");
        _teardown();
        return image;
    }

    // Allocate space for image
    if(!((image = malloc(sizeof(Image)))
        && (image->comment = malloc(header.comment_len * sizeof(char)))
        && (image->data = malloc(header.width * header.height * sizeof(uint8_t)))
    )) {
        fprintf(stderr, "Cannot allocate space for image.\n");
        _teardown();
        return image;
    }

    // Set width and height
    image->width = header.width;
    image->height = header.height;

    // Read the comment
    if((fread(image->comment, header.comment_len, 1, fp) != 1) || image->comment[header.comment_len - 1] != '\0') {
        fprintf(stderr, "Cannot read comment.\n");
        _teardown();
        return image;
    }

    // Read the image data
    if(fread(image->data, header.width * header.height, 1, fp) != 1) {
        fprintf(stderr, "Cannot read pixel data.\n");
        _teardown();
        return image;
    }

    // Check if there are trailing bytes
    uint8_t byte;
    if((fread(&byte, sizeof(uint8_t), 1, fp) != 0) || !feof(fp)) {
        fprintf(stderr, "File has trailing bytes. Not continuing.\n");
        _teardown();
        return image;
    }

    fclose(fp);
    return image;
}

/**
 * Save an image to the passed filename, in ECE264 format.
 * Return TRUE if this succeeds, or FALSE if there is any error.
 *
 * Hint: Please see the README for extensive hints
 */
int Image_save(const char * filename, Image * image) {
    FILE * fp = NULL;
    ImageHeader header;

    fp = fopen(filename, "wb");
    if(!fp) {
        fprintf(stderr, "Cannot open file '%s' for writing.\n", filename);
        return FALSE;
    }

    // Build header
    header.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
    header.width = image->width;
    header.height = image->height;
    header.comment_len = strlen(image->comment) + 1;

    // Write to file
    if(fwrite(&header, sizeof(ImageHeader), 1, fp) != 1) {
        fprintf(stderr, "Unable to write header.\n");
        fclose(fp);
        return FALSE;
    }

    // Write comment
    if(fwrite(image->comment, header.comment_len * sizeof(char), 1, fp) != 1) {
        fprintf(stderr, "Unable to write comment.\n");
        fclose(fp);
        return FALSE;
    }

    // Image data
    if(fwrite(image->data, header.height * header.width * sizeof(uint8_t), 1, fp) != 1) {
        fprintf(stderr, "Unable to write image data.\n");
        fclose(fp);
        return FALSE;
    }

    fclose(fp);
    return TRUE;
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
    if(image) {
        if(image->data) {
            free(image->data);
        }
        if(image->comment) {
            free(image->comment);
        }
        free(image);
    }
}

/**
 * Performs linear normalization, see README
 */
void linearNormalization(int width, int height, uint8_t * intensity) {
    int i;
    uint8_t min = 255, max = 0;

    // Find max and min
    for(i = 0; i < width * height; i++) {
        if(intensity[i] > max) {
            max = intensity[i];
        } else if(intensity[i] < min) {
            min = intensity[i];
        }
    }

    // Normalize image
    for(i = 0; i < width * height; i++) {
        intensity[i] = (intensity[i] - min) * 255.0 / (max - min);
    }
}
