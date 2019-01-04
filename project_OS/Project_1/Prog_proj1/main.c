/*************************************************************************
 * Programming project 1
 * Isaac Delgado
 * COSC_3346
 * 6/24/2016
 * Purpose: This program i will take a text file (via command line) and 
 *          identify the different words (case-insensitive) as well as 
 *          their frequency in the
 *          tect file.
 *
 * Input:   The input of the program will be the from any text file 
 *          specified by the user.
 *          which contains the elemnts to insert in to AVL tree
 *
 * Output:  The output of this program will be directed to file 
 *          "program_output.out" the file will contain all the words with 
 *          their cont of frequency.
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lib.h"


int Total_Words = 0;  //global variables
int Total_UniqueWords = 0;


int main(int argc, char *argv[])
{
    LIST_HEAD(listHead);
    char wordArray[50];  //to hold each individual word
    char **charArray;  //array of character array's to hold all words
    int *countArray;   //array to hold count of words parrallel to **charArray
    int choice, asc_dsc;

    char * token;
    const char s[4] = "-)."; // characters to ignore via strtoke

    FILE *infile;
    infile = fopen(argv[1], "r");
    if (!infile) {
        perror("file does not exist\n");
        exit(1);
    }
    
    while (fscanf(infile, "%s", wordArray) != EOF) {  //while we can read words from file do the following
        token = strtok(wordArray, s);  //take each word and ignor characters in array s
        lowerCase(wordArray);
        strip_nonAlpa(wordArray);
        if (!search_listForWord(wordArray, &listHead)) { //if word does not exist in linked list already
            add_node(wordArray, &listHead);   //add word into linked list
        }
    }
    
    countArray = (int*)malloc(sizeof(int)*Total_UniqueWords);  //memorey allocate character array
    charArray = (char**)malloc(sizeof(char*)*Total_UniqueWords); //memorey allocate integer array
    int i; //for for-loop
    for (i = 0; i < Total_UniqueWords; i++) {//loop to allocate memorey character array in charArry for each word
        charArray[i] = (char*)malloc(sizeof(char)*20); 
    }
    
    putInToArrays(charArray, countArray, &listHead); //transfer linked list info to appropriate array
    
    printf("Would you like your file sorted by word or by count of occurences?\n\n");
    printf("1.) Sort by WORD\n2.) sort by COUNT\n");
    printf("Please enter number: ");
    scanf("%d", &choice);
    
    printf("\n\nWould you like your file sorted in ascending or descending order?\n\n");
    printf("1.) ASCENDING\n2.) DESCENDING\n");
    printf("Please enter number: ");
    scanf("%d", &asc_dsc);
    
    switch (choice) {
        case 1:
            selectionSort_word(charArray, countArray, asc_dsc);
            break;
            
        case 2:
            selectionSort_count(charArray, countArray, asc_dsc);
            break;
            
        default:
            perror("*** invalid input ***\n");
            exit(1);
            break;
    }
    
    printf("*** writing to output file ***\n\n");
    outputToFile(charArray, countArray);
    printf("*** program succeded ***\n");

    
    delete_all(&listHead);
    fclose(infile);
    
    return 0;
}
