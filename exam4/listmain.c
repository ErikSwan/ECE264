// eswan
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "lists.h"

void printList (List * list) {
  if (list) {
    printf("%s\n", list->data);
    printList(list->next);
  }
}

// You should not need to modify this program but you can add more test code if
// you want. This file will not be turned in.

//    READ THIS: This program uses the above functions to make a list of
//    all argument strings given on the command line and then run various
//    functions defined above on that list, finally cleaning up the
//    memory used.
int main (int argc, char **argv) {
  int i;
  List *list=NULL;

  List **next=&list;
  for (i=1; i<argc; i++) {
    *next = makeListOfOne(argv[i]);
    next = &((*next)->next);
  }

  List * evenresult=NULL;
  List * oddresult=NULL;
  List * sortresult=NULL;

  printf("\nList:\n");
  printList(list);
  printf("\nOdds:\n");
  printList(oddresult=odds(list));
  printf("\nEvens:\n");
  printList(evenresult=evens(list));
  printf("\nList again (should not have changed):\n");
  printList(list);

  appendList(oddresult,copyList(evenresult));  // modifies oddresult to include evenresult
  printf("\nEvens appended onto odds gives:\n");
  printList(oddresult);

  printf("\nSorted list:\n");
  printList(sortresult=mergeSort(copyList(list)));

  printf("\nList again (should not have changed):\n");
  printList(list);

  destroyList(list);
  destroyList(oddresult);
  destroyList(evenresult);
  destroyList(sortresult);
  return 0;
}
