#include <stddef.h>
#include <stdio.h>
#include "list.h"

Node nodeList[LIST_MAX_NUM_NODES];
List headerList[LIST_MAX_NUM_HEADS];
Node* pNodeList = nodeList;
List* pHeaderList = headerList;

static Node* createNode(Node* nextNode, Node* prevNode, void* nodeVal){
    pNodeList->nextNode = nextNode;
    pNodeList->prevNode = prevNode;
    pNodeList->nodeVal = nodeVal;

    Node* newNode = pNodeList;
    pNodeList++;
    return newNode;
}

List* List_create(){
    // initialize header
    pHeaderList->headNext = NULL;
    pHeaderList->len = 0;
    pHeaderList->currentNode = NULL;

    List* newListPointer = pHeaderList;
    pHeaderList += 1;
    return newListPointer;
}

int List_count(List* pList){
    return pList->len;
}

void* List_first(List* pList){
    if (pList->len == 0) {
        return NULL;
    }
    pList->currentNode = pList->headNext;
    return pList->currentNode;
}

void* List_last(List* pList){
    if (pList->len == 0) {
        return NULL;
    }
    pList->currentNode = pList->pTail->prevNode;
    return pList->currentNode;
}

void* List_next(List* pList) {
    if (pList->currentNode->nextNode->nodeVal == NULL){
        return NULL;
    }
    pList->currentNode = pList->currentNode->nextNode;
    return pList->currentNode;
}

void* List_prev(List* pList){
    // if (pList->currentNode->prevNode->nodeVal == NULL){
    //     return NULL;
    // }
    pList->currentNode = pList->currentNode->prevNode;
    return pList->currentNode;
}

void* List_curr(List* pList){
    return pList->currentNode;
}

int List_append(List* pList, void* pItem){
    Node* newNode;
    if (pList->len == 0) {
        newNode = createNode(NULL, NULL, pItem);
        pList->headNext = newNode;

        // initialize tail
        Node* tail = createNode(NULL, newNode, NULL);
        newNode->nextNode = tail;
        pList->pTail = tail;
    } else {
        Node* lastNode = pList->pTail->prevNode;
        newNode = createNode(pList->pTail, lastNode, pItem);
        lastNode->nextNode = newNode;
        pList->pTail->prevNode = newNode;
    }
    pList->currentNode = newNode;
    pList->len++;
    printf("Added %d to the list\n", *(int*)pItem);
    return 0;
}
