#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "lib.h"
#include "list.h"
#include "struct_listNode.h"


void display(struct list_head *head)
{
    struct list_head *iter;
    struct listNode *objPtr;
    
    list_for_each(iter, head) {
        objPtr = list_entry(iter, struct listNode, list_member);
        printf("word: %s count: %d\n", objPtr->word, objPtr->count);    }
    printf("\n");
}

void delete_all(struct list_head *head)
{
    struct list_head *iter;
    struct listNode *objPtr;
    
redo:
    list_for_each(iter, head) {
        objPtr = list_entry(iter, struct listNode, list_member);
        list_del(&objPtr->list_member);
        free(objPtr);
        goto redo;
    }
}

bool search_listForWord(char * arg, struct list_head *head)
{
    struct list_head *iter;
    struct listNode *objPtr;
    
    list_for_each(iter, head) {
        objPtr = list_entry(iter, struct listNode, list_member);
        if(strcmp(arg, objPtr -> word) == 0) {
            objPtr -> count++;
            Total_Words++;
            return true;
        }
    }
    return false; //not in list
}

void add_node(char * arg, struct list_head *head)
{
    struct listNode *node = (struct listNode *)malloc(sizeof(struct listNode));
    assert(node != NULL);
    
    node -> word = (char *)malloc(strlen(arg)+1);
    strcpy(node -> word, arg);
    node -> count = 1;
    Total_Words++;
    Total_UniqueWords++;
    
    INIT_LIST_HEAD(&node->list_member);
    list_add(&node->list_member, head);
}


void lowerCase(char *fileWord){
    int i = 0;
    while (fileWord[i]) {
        fileWord[i] = tolower(fileWord[i]);
        i++;
    }
}

void strip_nonAlpa(char *fileword){
    int i;
    int j;
    for (i = 0; fileword[i]; i++) {
        if (isalpha(fileword[i]) == 0) {
            for (j = i; j < sizeof(fileword) - 1; j++ )
                fileword[j] = fileword[j+1];
        }
    }
}


void swap_word(int first, int second, char **Array){
    char *temp;
    temp = Array[second];
    Array[second] = Array[first];
    Array[first] = temp;
}

void swap(int first, int second, char **wordArray, int *countArray){
    char *chartemp;
    chartemp = wordArray[second];
    wordArray[second] = wordArray[first];
    wordArray[first] = chartemp;
    
    int inttemp;
    inttemp = countArray[second];
    countArray[second] = countArray[first];
    countArray[first] = inttemp;
}

int minLocation_word(int first, int last, char **charArray, int asc_dsc){
    int minIndex;
    minIndex = first;
    int current;
    
    switch (asc_dsc) {
        case 1: //ascending
            for (current = first+1; current < last; current++) {
                if (strcmp(charArray[current], charArray[minIndex]) < 0) {
                    minIndex = current;
                }
            }
            return minIndex;
            break;
            
        case 2: //dscending
            for (current = first+1; current < last; current++) {
                if (strcmp(charArray[current], charArray[minIndex]) > 0) {
                    minIndex = current;
                }
            }
            return minIndex;
            break;
            
        default:
            perror("*** invalid input ***\n");
            exit(1);
            break;
    }
    
}

void selectionSort_word(char **wordArray, int *countArray, int asc_dsc){
    int minIndex;
    int first;
    for (first = 0; first < Total_UniqueWords; first++) {
        minIndex = minLocation_word(first, Total_UniqueWords, wordArray, asc_dsc);
        swap(first, minIndex, wordArray, countArray);
        //printf("word is: %s\n", Array[first].word);
    }
}

void putInToArrays(char **wordArray, int *countArray, struct list_head *head)
{
    struct list_head *iter;
    struct listNode *objPtr;
    int i = 0;
    list_for_each(iter, head) {
        objPtr = list_entry(iter, struct listNode, list_member);
        strcpy(wordArray[i], objPtr->word);
        countArray[i] = objPtr->count;
        i++;
    }
    
}


int minLocation_count(int first, int last, int *countArray, int asc_dsc){
    int minIndex;
    minIndex = first;
    int current;
    switch (asc_dsc) {
        case 1: //ascending
            for (current = first+1; current < last; current++) {
                if (countArray[current] < countArray[minIndex]) {
                    minIndex = current;
                }
            }
            return minIndex;
            break;
        case 2: //dscending
            for (current = first+1; current < last; current++) {
                if (countArray[current] > countArray[minIndex]) {
                    minIndex = current;
                }
            }
            return minIndex;
            break;
            
        default:
            perror("*** invalid input ***\n");
            exit(1);
            break;
    }
    
}

void selectionSort_count(char **wordArray, int *countArray, int asc_dsc){
    int minIndex;
    int first;
    for (first = 0; first < Total_UniqueWords; first++) {
        minIndex = minLocation_count(first, Total_UniqueWords, countArray, asc_dsc);
        swap(first, minIndex, wordArray, countArray);
    }
}

void outputToFile(char **words, int *count){
    FILE *outfile;
    outfile = fopen("program-output.out", "w");
    
    if (!outfile) {
        perror("could not write to ecternal file\n");
        exit(1);
    }
    
    fprintf(outfile, "Word\tCount\n" );
    fprintf(outfile,"****************\n\n");
    
    int j;
    for (j = 0; j < Total_UniqueWords; j++) {
        fprintf(outfile, "%s   %d\n ", words[j], count[j]);
    }
    
    fprintf(outfile, "\n**********************\n");
    fprintf(outfile, "Total Words: %d\nTotal Unique Words: %d\n", Total_Words, Total_UniqueWords);
    fprintf(outfile, "**********************\n");
    
    fclose(outfile);
}

