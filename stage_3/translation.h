#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct labelNode {
    char* label;
    int address;
    struct labelNode* next;
} labelNode;
labelNode*create_labelNode(char*label,int address);
void append_labelNode(labelNode**head,char*label,int address);
int getAddr(labelNode* head, char* label);
void free_labelList(labelNode* head);