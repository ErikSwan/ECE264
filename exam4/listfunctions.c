// eswan
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "lists.h"

// In writing code below, please feel free to call functions you have written
// in later functions.

// PROBLEM THREE, part A:  complete the struct in lists.h
// PROBLEM THREE, parts B thru H.  Implement each function described below.
//   Implement in order as much as possible.


// PROBLEM THREE B
// makeListOfOne accepts a string argument and creates a one-element
// list where the one element stores a copy of that string.

List * makeListOfOne (char * contents) {
    List * list = malloc(1*sizeof(List));
    list->data = strdup(contents);
    list->next = NULL;
    return list;
}


// PROBLEM THREE C
//   destroyList reclaims all memory used by the list cells and their contents.
void destroyList (List * list) {
    if(list) {
        free(list->data);
        destroyList(list->next);
        free(list);
    }
}


// PROBLEM THREE D
//    odds(list) returns a new list containing some of the data elements
//    (strings) from "list".
//      -the returned list contains every other element from list: those in odd
//       positions.
//      -i.e. the first, third, fifth, etc., element from the input list
//
//      -DO NOT modify the input list elements, make a new list, with new
//       list cells and new string copies.
List * odds (List * list) {
    List * new_list = NULL;
    if(list) {
        // Malloc a new list element
        new_list = malloc(1*sizeof(List));

        // Make a copy of the string
        new_list->data = strdup(list->data);

        if(list->next && list->next->next) {
            new_list->next = odds(list->next->next);
        } else {
            new_list->next = NULL;
        }
    }
    return new_list;
}


// PROBLEM THREE E
//    evens(list) returns a list of the even position elements from list.
//    All the instructions for odds() apply here, just using the other
//    elements.
List * evens (List * list) {
    // Intentional assignment in if()
    // Just shift the list by one element, then call odds
    if((list = list->next)) {
        return odds(list);
    } else {
        return NULL;
    }
}


// PROBLEM THREE F
//    append() modifies list1 so the end cell points to list2 and returns list1.
//    --but if list1 is null, just return list2.
List * appendList (List * list1, List * list2) {
    if(!list1) {
        return list2;
    } 

    if(!(list1->next)) {
        list1->next = list2;
    } else {
        appendList(list1->next, list2);
    }

    return list1;
}


// PROBLEM THREE G copyList(list) returns a new list copy of list.  New list
//    cells and new data strings.
List * copyList(List * list) {
    List * new_list = NULL;

    if(list) {
        new_list = malloc(1*sizeof(List));
        new_list->data = strdup(list->data);
        new_list->next = copyList(list->next);
    }

    return new_list;
}


// The function merge() is provided for your use in
// implementing mergesort() below.  DO NOT MODIFY THIS FUNCTION.
List * merge(List * list1, List * list2) {
  if (!list1) return list2;
  else if (!list2) return list1;
  else {
    List * useList;
    List * otherList;

    if (strcmp(list1->data,list2->data) < 0) {
      useList=list1;
      otherList= list2;
    } else {
      useList= list2;
      otherList=list1;
    }
    useList->next = merge(useList->next,otherList);
    return useList;
  }
}


// PROBLEM THREE H
//  mergeSort() recursively sorts "list" using merge()
//  -- this function changes the pointers in list, so the
//     old list is no longer.  If the old list is desired,
//     it should be copied with copyList before calling mergeSort()
List * mergeSort (List *list) {
    // Helper to measure length
    int _listLength(List * _list) {
        int length = 0;

        if(_list) {
            length = 1 + _listLength(_list->next);
        }

        return length;
    }

    // Helper to split the list
    void _splitList(List ** _lhs, List ** _rhs) {
        int length = _listLength(*_lhs),
            i;
        List * tmp = *_lhs;

        // Find the midway point
        for(i = 0; i < (length / 2) - 1; i++) {
           tmp = tmp->next;
        }

        // Do the splitting
        *_rhs = tmp->next;
        tmp->next = NULL;
    }

    List *lhs = list, *rhs;

    // Already sorted
    if(_listLength(list) < 2) {
        return list;
    }

    // Split the list
    _splitList(&lhs, &rhs);

    // Sort both halves
    mergeSort(lhs);
    mergeSort(rhs);

    return merge(lhs, rhs);
}
