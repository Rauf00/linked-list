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

static void deleteNode(void* item) {
    printf("delete item\n");
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

    List* list1 = List_create();
    
    // Test List_append
    if(List_append(list1, pNumbers[99]) == 0) {
        if (*(int*)(List_curr(list1)) == 99){
            printList(list1);
            printCurrent(list1);
            printf("\nList_append test: --- PASSED ---\n");
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nERROR: Unable to append an item to the list\n");
    }
    
    // Add more items to the list for further testing
    printf("\nAdded more items for further testing");
    for(int i = 0; i < 99; i++) {
        List_append(list1, pNumbers[i]);
    }
    printList(list1);

    // Test List_count
    if (List_count(list1) == 100) {
        printf("\nList_count test: --- PASSED ---\n");
    } else {
        printf("\nList_count test: --- FAILED ---\n");
    }

    // Test List_first
    if (*(int*)(List_first(list1)) == 99) {
        if (*(int*)(List_curr(list1)) == 99) {
            printf("\nList_first test: --- PASSED ---\n");
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_first test: --- FAILED ---\n");
    }

    // Test List_last
    if (*(int*)(List_last(list1)) == 98) {
        if (*(int*)(List_curr(list1)) == 98) {
            printf("\nList_last test: --- PASSED ---\n");
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_last test: --- FAILED ---\n");
    }

    // Test List_prev
    if (*(int*)(List_prev(list1)) == 97) {
        if (*(int*)(List_curr(list1)) == 97) {
            printf("\nList_prev test: --- PASSED ---\n");
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_prev test: --- FAILED ---\n");
    }

     // Test List_next
    if (*(int*)(List_next(list1)) == 98) {
        if (*(int*)(List_curr(list1)) == 98) {
            printf("\nList_next test: --- PASSED ---\n");
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_next test: --- FAILED ---\n");
    }

    // Test List_next OOB
    if (List_next(list1) == NULL) {
        if (List_curr(list1) == NULL) {
            printf("\nList_next OOB test: --- PASSED ---\n");
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_next OOB test: --- FAILED ---\n");
    }
    
    // Test List_prev when OOB at the end
    if (*(int*)(List_prev(list1)) == 98) {
        if (*(int*)(List_curr(list1)) == 98) {
            printf("\nList_prev after OOB at the end: --- PASSED ---\n");
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_prev after OOB at the end: --- FAILED ---\n");
    }

    List_first(list1);

    // Test List_prev OOB
    if (List_prev(list1) == NULL) {
        if (List_curr(list1) == NULL) {
            printf("\nList_prev OOB test: --- PASSED ---\n");
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_prev OOB test: --- FAILED ---\n");
    }

    // Test List_next when OOB at the start
    if (*(int*)(List_next(list1)) == 99) {
        if (*(int*)(List_curr(list1)) == 99) {
            printf("\nList_next after OOB at the start: --- PASSED ---\n");
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_next after OOB at the start: --- FAILED ---\n");
    }

    // Test List_curr 
    if (*(int*)(List_curr(list1)) == 99) {
        printf("\nList_curr test: --- PASSED ---\n");
    } else {
        printf("\nList_curr test --- FAILED ---\n");
    }

    // Test List_prepend
    List_remove(list1);
    if (List_prepend(list1, pNumbers[98]) == 0) {
        if (*(int*)(List_curr(list1)) == 98) {
            printf("\nList_prepend test: --- PASSED ---\n");
            List_remove(list1);
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_prepend test --- FAILED ---\n");
    }

    // Test List_insert_after
    if (List_insert_after(list1, pNumbers[97]) == 0) {
        if (*(int*)(List_curr(list1)) == 97) {
            printf("\nList_insert_after test: --- PASSED ---\n");
            List_remove(list1);
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_insert_after test: --- FAILED ---\n");
    }

    // Test List_insert_after when OOB at the start
    List_first(list1);
    List_prev(list1);
    if (List_insert_after(list1, pNumbers[97]) == 0) {
        if (*(int*)(List_curr(list1)) == 97) {
            printf("\nList_insert_after when OOB at the start test: --- PASSED ---\n");
            List_remove(list1);
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_insert_after when OOB at the start test: --- FAILED ---\n");
    }

    // Test List_insert_after when OOB at the end
    List_last(list1);
    List_next(list1);
    if (List_insert_after(list1, pNumbers[97]) == 0) {
        if (*(int*)(List_curr(list1)) == 97) {
            printf("\nList_insert_after when OOB at the end test: --- PASSED ---\n");
            List_remove(list1);
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_insert_after when OOB at the end test: --- FAILED ---\n");
    }
    
    // Test List_insert_after
    if (List_insert_before(list1, pNumbers[97]) == 0) {
        if (*(int*)(List_curr(list1)) == 97) {
            printf("\nList_insert_before test: --- PASSED ---\n");
            List_remove(list1);
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_insert_before test: --- FAILED ---\n");
    }

    // Test List_insert_before when OOB at the end
    List_last(list1);
    List_next(list1);
    if (List_insert_before(list1, pNumbers[97]) == 0) {
        if (*(int*)(List_curr(list1)) == 97) {
            printf("\nList_insert_before when OOB at the end test: --- PASSED ---\n");
            List_remove(list1);
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_insert_before when OOB at the end test: --- FAILED ---\n");
    }

    // Test List_insert_before when OOB at the end
    List_last(list1);
    List_next(list1);
    if (List_insert_before(list1, pNumbers[97]) == 0) {
        if (*(int*)(List_curr(list1)) == 97) {
            printf("\nList_insert_before when OOB at the end test: --- PASSED ---\n");
            List_remove(list1);
        } else {
            printf("\nERROR: current pointer is wrong\n");
        }
    } else {
        printf("\nList_insert_before when OOB at the end test: --- FAILED ---\n");
    }
    
    return 0;
}

