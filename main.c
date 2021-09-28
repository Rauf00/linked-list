#include <stddef.h>
#include <stdio.h>
#include "list.h"

// static void printList(List* pList){
//     Node* current = pList->head;
//     printf("\n--------------------------------\n");
//     printf("Current list: ");
//     while (current != NULL) {
//         int* value = (int*)(current->nodeVal);
//         printf("%d, ", *value);
//         current = current->nextNode;
//     }
//     printf("\n--------------------------------\n");
// }

// static void printCurrent(List *pList) {
//     if (pList->currentNode) {
//             printf("Value of current pointer: %d\n", *(int*)(pList->currentNode->nodeVal));
//         } else {
//             printf("Value of current pointer: %p\n", pList->currentNode);
//     }
// }

static bool comparator(void* pItem, void* pComparisonArg) {
    if (pItem == pComparisonArg) {
        return 1;
    } else {
        return 0;
    }
}

static void deleteNode(void* item) {
    item = NULL;
}

int main() {
    // create test items
    int numbers[150];
    int* pNumbers[100];
    for(int i = 0; i < 150; i++) {
       numbers[i] = i;
    }
    for(int i = 0; i < 100; i++) {
       pNumbers[i] = &numbers[i];
    }

    // Test List_create
    List* list1 = List_create();
    if (list1 != NULL) {
        printf("List_create test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test List_count when empty
    if (List_count(list1) == 0 && List_curr(list1) == NULL) {
        printf("List_count when empty test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test List_first when empty
    if (List_first(list1) == NULL && List_curr(list1) == NULL) {
        printf("List_first when empty test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test List_last when empty
    if (List_last(list1) == NULL && List_curr(list1) == NULL) {
        printf("List_last when empty test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test List_append
    if(List_append(list1, pNumbers[99]) == 0 && *(int*)(List_curr(list1)) == 99 && List_count(list1) == 1) {
        // printList(list1);
        // printCurrent(list1);
        printf("List_append test: --- PASSED ---\n");
    } else {
        return 0;
    }
    
    // Use all nodes for further testing
    for(int i = 0; i < 99; i++) {
        if (List_append(list1, pNumbers[i]) == -1){
            return 0;
        }
    }

    // Test List_count
    if (List_count(list1) == 100) {
        printf("List_count test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test List_first
    if (*(int*)(List_first(list1)) == 99 && *(int*)(List_curr(list1)) == 99 && list1->currentNode->prevNode == NULL) {
        printf("List_first test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test List_last
    if (*(int*)(List_last(list1)) == 98 && *(int*)(List_curr(list1)) == 98 && list1->currentNode->nextNode == NULL) {
        printf("List_last test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test List_prev
    if (*(int*)(List_prev(list1)) == 97 && *(int*)(List_curr(list1)) == 97) {
        printf("List_prev test: --- PASSED ---\n");
    } else {
        return 0;
    }

     // Test List_next
    if (*(int*)(List_next(list1)) == 98 && *(int*)(List_curr(list1)) == 98) {
        printf("List_next test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test List_next OOB
    if (List_next(list1) == NULL && List_curr(list1) == NULL && list1->currentPointerState == 1) {
        printf("List_next OOB_END test: --- PASSED ---\n");
    } else {
        return 0;
    }
    
    // Test List_prev when OOB at the end
    if (*(int*)(List_prev(list1)) == 98 && *(int*)(List_curr(list1)) == 98 && list1->currentPointerState == 2) {
        printf("List_prev after OOB_END: --- PASSED ---\n");
    } else {
        return 0;
    }

    List_first(list1);

    // Test List_prev OOB
    if (List_prev(list1) == NULL && List_curr(list1) == NULL && list1->currentPointerState == 0) {
        printf("List_prev OOB test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test List_next when OOB at the start
    if (*(int*)(List_next(list1)) == 99 && *(int*)(List_curr(list1)) == 99 && list1->currentPointerState == 2) {
            printf("List_next after OOB_START: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test List_curr 
    if (*(int*)(List_curr(list1)) == 99) {
        printf("List_curr test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // From now, I'll keep the state of list1 to have the values 1-98
    // Test List_prepend
    List_remove(list1);
    if (List_prepend(list1, pNumbers[98]) == 0 && *(int*)(List_curr(list1)) == 98) {
        printf("List_prepend test: --- PASSED ---\n");
        List_remove(list1);
    } else {
        return 0;
    }

    // Test List_insert_after
    if (List_insert_after(list1, pNumbers[97]) == 0 && *(int*)(List_curr(list1)) == 97) {
        printf("List_insert_after test: --- PASSED ---\n");
        List_remove(list1);
    } else {
        return 0;
    }

    // Test List_insert_after when OOB at the start
    List_first(list1);
    List_prev(list1);
    if (List_insert_after(list1, pNumbers[97]) == 0 && *(int*)(List_curr(list1)) == 97 && *(int*)(List_first(list1)) == 97) {
        printf("List_insert_after when OOB_START: --- PASSED ---\n");
        List_remove(list1);
    } else {
        return 0;
    }

    // Test List_insert_after when OOB at the end
    List_last(list1);
    List_next(list1);
    if (List_insert_after(list1, pNumbers[97]) == 0 && *(int*)(List_curr(list1)) == 97 && *(int*)(List_last(list1)) == 97) {
        printf("List_insert_after when OOB_END: --- PASSED ---\n");
        List_remove(list1);
    } else {
        return 0;
    }
    
    // Test List_insert_before
    List_last(list1);
    if (List_insert_before(list1, pNumbers[97]) == 0 && *(int*)(List_curr(list1)) == 97) {
            printf("List_insert_before test: --- PASSED ---\n");
            List_remove(list1);
    } else {
        return 0;
    }

    // Test List_insert_before when OOB at the start
    List_first(list1);
    List_prev(list1);
    if (List_insert_before(list1, pNumbers[97]) == 0 && *(int*)(List_curr(list1)) == 97 && *(int*)(List_first(list1)) == 97) {
            printf("List_insert_before when OOB_START: --- PASSED ---\n");
            List_remove(list1);
    } else {
        return 0;
    }

    // Test List_insert_before when OOB at the end
    List_last(list1);
    List_next(list1);
    if (List_insert_before(list1, pNumbers[97]) == 0 && *(int*)(List_last(list1)) == 97) {
            printf("List_insert_before when OOB_END: --- PASSED ---\n");
            List_remove(list1);
    } else {
        return 0;
    }
    
    List_prev(list1);
    // Test List_remove last
    if (*(int*)List_remove(list1) == 98 && List_curr(list1) == NULL) {
            printf("List_remove test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test List_remove OOB_END
    if (List_remove(list1) == NULL && List_curr(list1) == NULL && list1->currentPointerState == 1) {
        printf("List_remove OOB_END test: --- PASSED ---\n");
        List_append(list1, pNumbers[98]);
    } else {
        return 0;
    }

    List_first(list1);
    // Test List_remove first
    if (*(int*)List_remove(list1) == 0 && *(int*)List_curr(list1) == 1) {
        printf("List_remove first test: --- PASSED ---\n");
        List_prepend(list1, pNumbers[0]);
    } else {
        return 0;
    }

    List_next(list1);
    // Test List_remove middle
    if (*(int*)List_remove(list1) == 1 && *(int*)List_curr(list1) == 2) {
        printf("List_remove middle test: --- PASSED ---\n");
        List_insert_before(list1, pNumbers[1]);
    } else {
        return 0;
    }

    // Test List_remove OOB_START
    List_first(list1);
    List_prev(list1);
    if (List_remove(list1) == NULL && List_curr(list1) == NULL && list1->currentPointerState == 0) {
        printf("List_remove OOB_START test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test List_trim
    if (*(int*)List_trim(list1) == 98 && *(int*)List_curr(list1) == 97) {
        printf("List_trim test: --- PASSED ---\n");
        List_append(list1, pNumbers[98]);
    } else {
        return 0;
    }

    // Test trim with empty list
    List* list2 = List_create();
    if (List_trim(list2) == NULL && List_curr(list2) == NULL) {
        printf("List_trim empty test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test List_concat
    List_append(list2, pNumbers[99]);
    List_concat(list1, list2);
    if (List_count(list1) == 100 && *(int*)List_curr(list1) == 98) {
        printf("List_concat test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test memory management

    // Test insertion when all nodes are used
    if (List_append(list1, pNumbers[0]) == -1) {
        printf("List_append test when all nodes are used: --- PASSED ---\n");
    } else {
        return 0;
    }
    if (List_prepend(list1, pNumbers[0]) == -1) {
        printf("List_prepend test when all nodes are used: --- PASSED ---\n");
    } else {
        return 0;
    }
    if (List_insert_after(list1, pNumbers[0]) == -1) {
        printf("List_insert_after test when all nodes are used: --- PASSED ---\n");
    } else {
        return 0;
    }
    if (List_insert_before(list1, pNumbers[0]) == -1) {
        printf("List_insert_before test when all nodes are used: --- PASSED ---\n");
    } else {
        return 0;
    }
    
    // Test that a node is made available after removal
    List_remove(list1);
    if (List_append(list1, pNumbers[0]) == 0) {
        printf("List_append after List_remove (nodes were previously used): --- PASSED ---\n");
    } else {
        return 0;
    }

    // Use all head nodes
    list2 = List_create();
    List* list3 = List_create();
    List* list4 = List_create();
    List* list5 = List_create();
    List* list6 = List_create();
    List* list7 = List_create();
    List* list8 = List_create();
    List* list9 = List_create();
    List* list10 = List_create();
    List* list11 = List_create();
    if (list11 == NULL) {
        printf("List_create when all heads were used: --- PASSED ---\n");
    } else {
        return 0;
    }
    List_first(list1);

    // Test List_free
    List_free(list1, deleteNode);
    list11 = List_create();
    if (list11 != NULL) {
        printf("List_free test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Populate list11 to show that all nodes were reallocated
    for(int i = 0; i < 100; i++) {
        List_append(list11, pNumbers[i]);
    }

    if (list11->len == 100) {
        printf("Reallocate all nodes test: --- PASSED ---\n");
    } else {
        return 0;
    }

    List_first(list11);
    List_prev(list11);
    // Test List_search found
    if (*(int*)(List_search(list11, comparator, pNumbers[67])) == 67 && *(int*)(List_curr(list11)) == 67) {
        printf("List_search test when found: --- PASSED ---\n");
    } else {
        return 0;
    }

    List_remove(list11);
    // Test List_search not found    
    if (List_search(list11, comparator, pNumbers[67]) == NULL && List_curr(list11) == NULL && list11->currentPointerState == 1) {
        printf("List_search test when not found: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Test List_search on empty list
    if (List_search(list4, comparator, pNumbers[67]) == NULL && List_curr(list4) == NULL && list4->currentPointerState == 1) {
        printf("List_search empty list test: --- PASSED ---\n");
    } else {
        return 0;
    }

    // Clean everything up
    List_free(list2, deleteNode);
    List_free(list3, deleteNode);
    List_free(list4, deleteNode);
    List_free(list5, deleteNode);
    List_free(list6, deleteNode);
    List_free(list7, deleteNode);
    List_free(list8, deleteNode);
    List_free(list9, deleteNode);
    List_free(list10, deleteNode);
    List_free(list11, deleteNode);

    printf("-----------------------------------------------------------------\n");
    printf("All 41 test cases are passed! \nRauf KRASAVCHIK, MASHINA, MONSTR!!!\n");
    return 0;
}

