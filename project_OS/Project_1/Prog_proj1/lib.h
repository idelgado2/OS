#ifndef lib_h
#define lib_h

#include <stdbool.h>
#include "list.h"

void display( struct list_head *head);
void delete_all(struct list_head *head);
bool search_listForWord(char * arg, struct list_head *head);
void add_node(char * arg, struct list_head *head);
void lowerCase(char *fileWord);
void strip_nonAlpa(char *fileword);
void swap_word(int first, int second, char **Array);
void swap(int first, int second, char **wordArray, int *countArray);
int minLocation_word(int first, int last, char **charArray, int asc_dsc);
void selectionSort_word(char **wordArray, int *countArray, int asc_dsc);
void putInToArrays(char **wordArray, int *countArray, struct list_head *head);
int minLocation_count(int first, int last, int *countArray, int asc_dsc);
void selectionSort_count(char **wordArray, int *countArray, int asc_dsc);
void outputToFile(char **words, int *count);


#endif /* lib_h */
