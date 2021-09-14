#include <stddef.h>
#include <stdio.h>
#include "list.h"

void printList(List* pList){
    Node* current = pList->headerNext;
    printf("\nPrint current list: ");
    while (current != NULL) {
        int* value;
        value = (int*)(current->nodeVal);
        printf("%d, ", *value);
        current = current->nextNode;
    }
    printf("\n");
}

int main() {
    List* testList = List_create();

    int testInt1 = 10123;
    int* pInt1 = &testInt1;

    int testInt2 = 123;
    int* pInt2 = &testInt2;

    int testInt3 = 1000;
    int* pInt3 = &testInt3;

    List_append(testList, pInt1);
    List_append(testList, pInt2);
    List_append(testList, pInt3);

    printList(testList);

    Node* lastNode = List_last(testList);
    int* last = lastNode->nodeVal;
    printf("\nLast element is %d\n", *last);

    Node* firstNode = List_first(testList);
    int* first = firstNode->nodeVal;
    printf("First element is %d\n", *first);
    return 0;
}

