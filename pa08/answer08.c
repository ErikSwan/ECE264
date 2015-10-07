#include "answer08.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * Create a new list-node with the passed string.
 * str should be copied (with strdup).
 */
List * List_createNode(const char * str) {
    List * list = malloc(1 * sizeof(List));
    list->str = strdup(str);
    list->next = NULL;

    return list;
}

/**
 * Free all memory associated with the linked list, including memory for
 * contained strings. Must safely handle NULL lists.
 */
void List_destroy(List * list) {
    if(list) {
        if(list->str) {
            free(list->str);
        }
        if(list->next) {
            List_destroy(list->next);
        }
        free(list);
    }
}

/**
 * Length of a linked list.
 * The length of "NULL" is 0.
 */
int List_length(List * list) {
    int length = 0;
    if(list) {
        length++;
        if(list->next) {
            length += List_length(list->next);
        }
    }
    return length;
}

/**
 * Merge two sorted lists to produce a final sorted list.
 *
 * 'lhs' and 'rhs' are two sorted linked-list. Read 'left-hand-side' and 'right-
 * hand-side'. Note that either (or both) could be NULL, signifying the empty
 * list.
 * 'compar' is a function that is used to compare two nodes. This parameter is
 * similar to the parameter in qsort(...), except that it only compares two
 * strings. You can pass 'strcmp' to this function if you want to sort lists in
 * ascending order.
 *
 * When implementing this function, do not call List_createNode(...) or
 * malloc(...) Instead, think about how to build a new list by:
 * (1) Create a new (empty -- i.e., NULL) list where we build the result. You
 *     will need to track the first and last node of this list.
 * (2) In a while-loop:
 * (2.a) Use compar to identify whether the front node of lhs or rhs is smaller.
 *       Remember that lhs or rhs could be NULL.
 * (2.b) Move the front node of 'lhs/rhs' to the end of the result list.
 *
 * You will need to consider what happens when 'lhs' or 'rhs' becomes NULL.
 *
 * Well-written code should be 20-30 lines long, including comments and spacing.
 * If your code is longer than this, then you may save time by rethinking your
 * approach.
 */
List * List_merge(List * lhs, List * rhs,
    int (*compar)(const char *, const char*)) {

    void _merge_recursive(List * _lhs, List * _rhs, List ** result,
        int (*_compar)(const char *, const char *)) {

        List * next = NULL;

        if(!_lhs && !_rhs) {
            // Nothing left to sort! (base case)
            return;
        } else if(!_lhs) {
            // If the LHS is empty, but there are elements left in the RHS
            // Next element in the merged list is the RHS node
            next = _rhs;
            // Advance the RHS list
            _rhs = _rhs->next;
        } else if(!_rhs) {
            // If the RHS is empty, but there are elements left in the LHS
            // Next element in the merged list is the LHS node
            next = _lhs;
            // Advance the LHS list
            _lhs = _lhs->next;
        } else {
            if(_compar(_lhs->str, _rhs->str) < 0) {
                next = _lhs;
                _lhs = _lhs->next;
            } else {
                next = _rhs;
                _rhs = _rhs->next;
            }
        }

        if(*result) {
            // There is already a result list.
            (*result)->next = next;
            return _merge_recursive(_lhs, _rhs, &((*result)->next), _compar);
        } else {
            // If this is the first node in the result list, set the first node
            // instead of appending.
            (*result) = next;
            _merge_recursive(_lhs, _rhs, result, _compar);
        }
    }

    List * result = NULL;

    _merge_recursive(lhs, rhs, &result, compar);
    return result;
}

/**
 * Sorts the list's elements using the merge-sort algorithm.
 * Merge-sort is a recursive algorithm. See the README for hints.
 *
 * The brief instructions are as follows:
 *
 * (1) Base case:
 * Lists of length 0 or 1 are already (defacto) sorted. In this case, return
 * 'list'.
 *
 * (2) Recursive case:
 * (2.a) Split the linked-list into two approx. equal sized lists.
 * (2.b) Call List_sort(...) on each of these smaller lists.
 * (2.c) Call List_merge(...) to merge the now sorted smaller lists into a
 *       single larger sorted list, which you return.
 *
 * Well-written code should be 20-30 lines long, including comments and spacing.
 * If your code is longer than this, then you may save time by rethinking your
 * approach.
 */
List * List_sort(List * list, int (*compar)(const char *, const char*)) {
    int length = List_length(list),
        i;

    List *rhs, *lhs = list;

    // Lists of length 0 and 1 are already sorted
    if(length < 2) {
        return list;
    }

    // Find the center of the list
    for(i = 0; i < length / 2 - 1; i++) {
        list = list->next;
    }

    // Copy right segment to rhs
    rhs = list->next;

    // Break the connection at the halfway point
    list->next = NULL;

    // Sort the left hand side and the right hand side
    lhs = List_sort(lhs, compar);
    rhs = List_sort(rhs, compar);

    // Merge the lists
    return List_merge(lhs, rhs, compar);
}
