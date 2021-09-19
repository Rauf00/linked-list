#include <stddef.h>
#include <stdio.h>
#include "list.h"

void printList(List* pList){
    Node* current = pList->head->nextNode;
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

    // Test List_append
    printf("List_append: %d\n", List_append(testList, pInt1));
    printf("List_append: %d\n", List_append(testList, pInt2));
    printf("List_append: %d\n", List_append(testList, pInt3));
    printList(testList);

    // Test List_last
    Node* lastNode = List_last(testList);
    printf("\nList_last test:  %d\n", *(int*)(lastNode->nodeVal));
    printList(testList);

    // Test List_first
    Node* firstNode = List_first(testList);
    printf("\nList_first test: %d\n", *(int*)(firstNode->nodeVal));
    printList(testList);

    // Test List_count
    printf("\nList_count test %d\n", List_count(testList));
    
    // Test List_next
    Node* next = List_next(testList);
    printf("\nList_next test: %d\n", *(int*)(next->nodeVal));
    printList(testList);
    next = List_next(testList);
    printf("List_next test: %d\n", *(int*)(next->nodeVal));
    next = List_next(testList);
    printf("List_next test (out of bounds): %p\n", next);

    // Test List_prev
    Node* prev = List_prev(testList);
    printf("\nList_prev test: %d\n", *(int*)(prev->nodeVal));
    printList(testList);
    prev = List_prev(testList);
    printf("List_prev test: %d\n", *(int*)(prev->nodeVal));
    prev = List_prev(testList);
    printf("List_prev test: %d\n", *(int*)(prev->nodeVal));
    prev = List_prev(testList);
    printf("List_prev test (out of bounds): %p\n", prev);

    next = List_next(testList);
    printf("List_next test: %d\n", *(int*)(next->nodeVal));

    return 0;
}

