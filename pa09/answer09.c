#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "answer09.h"

#define MAXLINE 2048  // the max line size tolerated in the database file
#define FORMAT_STRING "%3s\t%99s\t%255s" // the format string used for the tsv file

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

/*
 * Construct one BusinessNode. You need to allocate memory for this node first.
 *
 * The caller needs to make sure to use strdup(...) for the arguments, do not
 * use strdup(...) inside of this function.
 *
 * stars: the stars of this business
 * name: name of this business
 * address: address of this business
 */
BusinessNode * create_node(char * stars, char * name, char * address) {
    BusinessNode * bnode = malloc(sizeof(BusinessNode));

    if(bnode != NULL) {
        bnode->name = name;
        bnode->stars = stars;
        bnode->address = address;
        bnode->left = NULL;
        bnode->right = NULL;
    }

    return bnode;
}

/* Insert a node into a BST. Primarily used in load_tree_from_file(). Return a
 * pointer to the root of the BST.
 */
BusinessNode * tree_insert(BusinessNode * node, BusinessNode * root) {
    int cmp;

    if(node) {
        if(!root) {
            root = node;
        } else {
            if((cmp = strcmp(node->name, root->name) > 0)) {
                if(root->right) tree_insert(node, root->right);
                else root->right = node;
            } else {
                if(root->left) tree_insert(node, root->left);
                else root->left = node;
            }
        }
    }

    return root;
}

/* Parse a .tsv file line by line, create a BusinessNode for each entry, and
 * enter that node into a new BST. Return a pointer to the root of the BST.
 *
 * The explode(...) function from PA03 may be useful for breaking up a lines
 * into separate fields.
 */
BusinessNode * load_tree_from_file(char * filename) {
    FILE * fp;
    BusinessNode *bnode = NULL, *root = NULL;
    char string[501]; // max line length is 500 chars
    char ** str_array;
    int arr_len, i;

    if(filename) {
        fp = fopen(filename, "r");
        if(!fp) return root;

        while(fgets(string, 501, fp)) {
            str_array = explode(string, "\t", &arr_len);

            if(arr_len == 3) {
                bnode = create_node(str_array[0], str_array[1], str_array[2]);

                if(bnode) {
                    root = tree_insert(bnode, root);
                } else {
                    // Looks like we're out of memory. Tear things down and then
                    // exit.
                    destroy_tree(root);
                    return NULL;
                }
            } else {
                // free strings allocated by explode()
                for(i = 0; i < arr_len; i++) {
                    free(str_array[i]);
                }
            }

            free(str_array);
        }
    }

    return root;
}

/* Search a BusinessNode BST for the node with the name 'name'. Returns
 * pointer to the node with a match.
 *
 * If there is no match, return NULL.
 */
BusinessNode * tree_search_name(char * name, BusinessNode * root) {
    int cmp;

    if(name && root) {
        cmp = strcmp(name, root->name);
        if(cmp == 0) return root;
        else return tree_search_name(name, cmp < 0 ? root->left : root->right);
    } else return NULL;
}

/* Print out a single node: name, address, and stars
 * The format can be similar to this:
 *
 * Country Cafe
 * ============
 * Stars:
 *    3.5
 * Address:
 *    1030 Emerald Ter, Sun Prairie, WI 53590
 *
 * This function is not graded, but it could come in very handful while
 * debugging this assignment.
 */
void print_node(BusinessNode * node) {
    if(node && node->stars && node->name && node->address) {
        printf("%s\n"
               "============\n"
               "Stars:\n"
               "\t%s\n"
               "Address:\n"
               "\t%s\n",
               node->name, node->stars, node->address
        );
    }
}

/* Print the entire tree, starting from the root. Like the print_node(...)
 * function, this is not graded.
 */
void print_tree(BusinessNode * tree) {
    if(tree) {
        print_node(tree);
        print_tree(tree->left);
        print_tree(tree->right);
    }
}

/* Deallocate all of the memory used by a BusinessNode BST, without memory
 * leaks.
 */
void destroy_tree(BusinessNode * root) {
    if(root) {
        destroy_tree(root->left);
        destroy_tree(root->right);

        if(root->name) free(root->name);
        if(root->stars) free(root->stars);
        if(root->address) free(root->address);
        free(root);
    }
}

