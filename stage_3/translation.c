#include "translation.h"
labelNode*create_labelNode(char* label, int address) {
    labelNode* newNode = (labelNode*)malloc(sizeof(labelNode));
    newNode->label = (char*)malloc(strlen(label) + 1);
    strcpy(newNode->label, label);
    newNode->address = address;
    newNode->next = NULL;
    return newNode;
}
void append_labelNode(labelNode** head, char* label, int address) {
    labelNode* newNode = create_labelNode(label, address);
    if (*head == NULL) {
        *head = newNode;
    } else {
        labelNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
int getAddr(labelNode* head, char* label) {
    labelNode* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->label, label) == 0) {
            return temp->address;
        }
        temp = temp->next;
    }
    return -1;
}
void free_labelList(labelNode* head) {
    labelNode* temp;
    while (head != NULL) {          
        temp = head;
        head = head->next;
        free(temp->label);
        free(temp);
    }
}
