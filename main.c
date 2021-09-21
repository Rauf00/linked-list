#include <stddef.h>
#include <stdio.h>
#include "list.h"

void printList(List* pList){
    Node* current = pList->head;
    printf("\n--------------------------------\n");
    printf("Current list: ");
    while (current != NULL) {
        int* value;
        value = (int*)(current->nodeVal);
        printf("%d, ", *value);
        current = current->nextNode;
    }
    printf("\n--------------------------------\n");
}

static void printCurrent(List *pList) {
    if (pList->currentNode) {
            printf("Value of current pointer: %d\n", *(int*)(pList->currentNode->nodeVal));
        } else {
            printf("Value of current pointer: %p\n", pList->currentNode);
    }
}

int main() {
    // List* testList = List_create();

    // // initilize test items;
    // int testInt1 = 10123;
    // int* pInt1 = &testInt1;
    // int testInt2 = 123;
    // int* pInt2 = &testInt2;
    // int testInt3 = 1000;
    // int* pInt3 = &testInt3;

    // // Test List_append
    // printf("List_append: %d\n", List_append(testList, pInt1));
    // printf("List_append: %d\n", List_append(testList, pInt2));
    // printf("List_append: %d\n", List_append(testList, pInt3));
    // printList(testList);
    // printCurrent(testList);

    // // Test List_last
    // Node* lastNode = List_last(testList);
    // printf("\nList_last test:  %d\n", *(int*)(lastNode->nodeVal));
    // printList(testList);
    // printCurrent(testList);

    // // Test List_first
    // Node* firstNode = List_first(testList);
    // printf("\nList_first test: %d\n", *(int*)(firstNode->nodeVal));
    // printList(testList);
    // printCurrent(testList);

    // // Test List_count
    // printf("\nList_count test %d\n", List_count(testList));
    
    // // Test List_next
    // Node* next = List_next(testList);
    // printf("\nList_next test: %d\n", *(int*)(next->nodeVal));
    // printList(testList);
    // printCurrent(testList);
    // next = List_next(testList);
    // printf("List_next test: %d\n", *(int*)(next->nodeVal));
    // next = List_next(testList);
    // printf("List_next test (out of bounds): %p\n", next);
    // printList(testList);
    // printCurrent(testList);

    // // Test List_prev
    // Node* prev = List_prev(testList);
    // printf("\nList_prev test: %d\n", *(int*)(prev->nodeVal));
    // printList(testList);
    // printCurrent(testList);
    // prev = List_prev(testList);
    // printf("List_prev test: %d\n", *(int*)(prev->nodeVal));
    // prev = List_prev(testList);
    // printf("List_prev test: %d\n", *(int*)(prev->nodeVal));
    // prev = List_prev(testList);
    // printf("List_prev test (out of bounds): %p\n", prev);
    
    // next = List_next(testList);
    // printf("List_next test: %d\n", *(int*)(next->nodeVal));
    // printCurrent(testList);
    // next = List_next(testList);
    // printf("List_next test: %d\n", *(int*)(next->nodeVal));
    // printCurrent(testList);

    // List_remove(testList);
    // List_trim(testList);
    // printList(testList);
    // printCurrent(testList);


    // // List* testList2 = List_create();

    // // // initilize test items;
    // // int test2Int1 = 1;
    // // int* p2Int1 = &test2Int1;
    // // int test2Int2 = 2;
    // // int* p2Int2 = &test2Int2;
    // // int test2Int3 = 3;
    // // int* p2Int3 = &test2Int3;

    // // // Test List_append
    // // printf("List_append: %d\n", List_append(testList2, p2Int1));
    // // printf("List_append: %d\n", List_append(testList2, p2Int2));
    // // printf("List_append: %d\n", List_append(testList2, p2Int3));
    // // printList(testList2);
    // // printCurrent(testList2);

    List* test = List_create();
    int array[80];
    int* pArray[80];
    for(int i = 0; i < 80; i++) {
       array[i] = i;
    }
    for(int i = 0; i < 80; i++) {
       pArray[i] = &array[i];
    }

    List* test2 = List_create();
    int array2[20];
    int* pArray2[20];
    for(int i = 0; i < 20; i++) {
       array2[i] = i;
    }
    for(int i = 0; i < 20; i++) {
       pArray2[i] = &array2[i];
    }

    for(int j = 0; j < 80; j++) {
        List_append(test, pArray[j]);
    }

    for(int j = 0; j < 20; j++) {
        List_append(test2, pArray2[j]);
    }
    printList(test);
    printList(test2);   
    List_first(test2);
    List_next(test2);


    printf("Removed %d\n", *(int*)(List_remove(test2)));
    printList(test2);  
    return 0;
}

