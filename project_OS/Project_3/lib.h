#ifndef lib_h
#define lib_h

#include <stdbool.h>

bool ampersand(char **args, int *size);
int historyFunction(char *history[], int current, int numOfVal);
void childExecvp(char **args);
int numValues(char *history[]);

#endif