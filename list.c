#include <stddef.h>
#include <stdio.h>
#include "list.h"

Node nodeList[LIST_MAX_NUM_NODES];
List headerList[LIST_MAX_NUM_HEADS];
int currNodeListIndex = 0;
int currHeaderListIndex = 0;

static Node* createNode(Node* nextNode, Node* prevNode, void* nodeVal){
    nodeList[currNodeListIndex].nextNode = nextNode;
    nodeList[currNodeListIndex].prevNode = prevNode;
    nodeList[currNodeListIndex].nodeVal = nodeVal;
    Node* newNode = &nodeList[currNodeListIndex];
    currNodeListIndex++;
    return newNode;
}

List* List_create(){
    headerList[currHeaderListIndex].headerNext = NULL;
    headerList[currHeaderListIndex].len = 0;
    headerList[currHeaderListIndex].isUsed = 1;
    headerList[currHeaderListIndex].currentNode = NULL;
    List* newListPointer = &headerList[currHeaderListIndex];
    currHeaderListIndex += 1;
    return newListPointer;
}

int List_count(List* pList){
    return pList->len;
}

void* List_first(List* pList){
    pList->currentNode = pList->headerNext;
    return pList->currentNode;
}

void* List_last(List* pList){
    if (pList->len == 0) {
        return NULL;
    }
    while (pList->currentNode->nextNode != NULL) {
        pList->currentNode = pList->currentNode->nextNode;
    }
    return pList->currentNode;
}

void* List_next(List* pList){

}

void* List_prev(List* pList){

}

void* List_curr(List* pList){

}

int List_insert_after(List* pList, void* pItem){
    
}
int List_insert_before(List* pList, void* pItem){

}
int List_append(List* pList, void* pItem){
    Node* newNode;
    if (pList->len == 0) {
        newNode = createNode(NULL, NULL, pItem); // dont point to head for now
        pList->headerNext = newNode;
        
    } else{
        Node* lastNode = List_last(pList);
        newNode = createNode(NULL, lastNode, pItem);
        lastNode->nextNode = newNode;
    }
    pList->len += 1;
    pList->currentNode = newNode;
    printf("Added %d to the list\n", *(int*)pItem);
    return 1;
}

int List_prepend(List* pList, void* pItem){

}
void* List_remove(List* pList){

}
void* List_trim(List* pList){

}
void List_concat(List* pList1, List* pList2){

}
void List_free(List* pList, FREE_FN pItemFreeFn){

}
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg){

}
