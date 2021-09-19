#include <stddef.h>
#include <stdio.h>
#include "list.h"

void printList(List* pList){
    Node* current = pList->headNext;
    printf("--------------------------------\n");
    printf("Result:\nCurrent list: ");
    while (current->nodeVal != NULL) {
        int* value;
        value = (int*)(current->nodeVal);
        printf("%d, ", *value);
        current = current->nextNode;
    }
    printf("\nValue of current pointer: %d\n", *(int*)(pList->currentNode->nodeVal));
    printf("--------------------------------\n");
}

int main() {
    List* testList = List_create();

    // initilize test items;
    int testInt1 = 10123;
    int* pInt1 = &testInt1;
    int testInt2 = 123;
    int* pInt2 = &testInt2;
    int testInt3 = 1000;
    int* pInt3 = &testInt3;

    printf("Operation result %d\n", List_append(testList, pInt1));
    printf("Operation result %d\n", List_append(testList, pInt2));
    printf("Operation result %d\n", List_append(testList, pInt3));
    printList(testList);

    Node* lastNode = List_last(testList);
    printf("\nList_last test:  %d\n", *(int*)(lastNode->nodeVal));
    printList(testList);

    Node* firstNode = List_first(testList);
    printf("\nList_first test: %d\n", *(int*)(firstNode->nodeVal));
    printList(testList);

    printf("\nList_count test %d\n", List_count(testList));
    
    Node* next = List_next(testList);
    printf("\nList_next test: %d\n", *(int*)(next->nodeVal));
    printList(testList);

    List_next(testList);
    List_next(testList);
    Node* nextOutOfBounds = List_next(testList);
    printf("\nList_next test (out of bounds): %p\n", nextOutOfBounds);

    Node* prev = List_prev(testList);
    printf("\nList_prev test: %d\n", *(int*)(prev->nodeVal));
    printList(testList);

    List_prev(testList);
    // List_prev(testList);
    // List_prev(testList);
    Node* prevOutOfBounds = List_prev(testList);
    printf("\nList_prev test (out of bounds): %p\n", prevOutOfBounds);


    return 0;
}

