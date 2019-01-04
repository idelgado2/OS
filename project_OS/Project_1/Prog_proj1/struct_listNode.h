#ifndef struct_listNode_h
#define struct_listNode_h

#include "list.h"

struct listNode {
    char *word;
    int count;
    struct list_head list_member;
};

extern int Total_Words;
extern int Total_UniqueWords;

#endif /* struct_listNode_h */
