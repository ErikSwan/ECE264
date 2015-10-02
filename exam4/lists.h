// eswan
typedef struct List_struct_t {
    char * data;
    struct List_struct_t * next;
} List;


// these are described in listfunctions.c

List * makeListOfOne (char * contents);

void destroyList (List * list);

List * appendList (List * list1, List * list2);

List * odds (List * list);

List * evens (List * list);

List * copyList(List * list);

List * mergeSort (List *list);
