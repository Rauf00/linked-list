#include <stddef.h>
#include <stdio.h>
#include "list.h"

static Node nodeList[LIST_MAX_NUM_NODES];
static List headList[LIST_MAX_NUM_HEADS];
static Node* pNodeList = nodeList;
static List* pHeadList = headList;
static int isInitialized = 0;

// link all nodes together and all heads together
static void initialize(){
    for (int i = 0; i < LIST_MAX_NUM_NODES - 1; i++) {
        nodeList[i].nextNode = &nodeList[i + 1];
    }
    for (int i = 0; i < LIST_MAX_NUM_HEADS - 1; i++) {
        headList[i].nextFreeHead = &headList[i + 1];
    }
}

// helper function to free a node for the future usage
static void freeNode(Node* node) {
    // make removed node free
    node->nextNode = pNodeList;
    node->prevNode = NULL;
    node->nodeVal = NULL;
    
    pNodeList = node;
}

static void freeHeadList(List* list) {
    list->currentPointerState = 2;
    list->len = 0;
    list->nextFreeHead = pHeadList;
    list->currentNode = NULL;
    list->head = NULL;
    list->tail = NULL;

    pHeadList = list;
}

// helper function to create a node
static Node* createNode(Node* nextNode, Node* prevNode, void* nodeVal){
    if (pNodeList == NULL) {
        printf("ERROR: All nodes are used!\n");
        return NULL;
    }
    Node* newNode = pNodeList;
    pNodeList = pNodeList->nextNode;
    
    // Populate Node data
    newNode->nextNode = nextNode;
    newNode->prevNode = prevNode;
    newNode->nodeVal = nodeVal;
    return newNode;
}

List* List_create(){
    if (isInitialized == 0) {
        initialize();
        isInitialized = 1;
    }
    if (pHeadList == NULL) {
        printf("ERROR: All heads are used!\n");
        return NULL;
    }
    List* newListPointer = pHeadList;
    pHeadList = pHeadList->nextFreeHead;

    // Populate List data
    newListPointer->currentPointerState = 2;
    newListPointer->len = 0;
    newListPointer->nextFreeHead = NULL;
    newListPointer->currentNode = NULL;
    newListPointer->head = NULL;
    newListPointer->tail = NULL;
    
    return newListPointer;
}

int List_count(List* pList){
    return pList->len;
}

void* List_first(List* pList){
    if (pList->len == 0) {
        return NULL;
    }
    pList->currentNode = pList->head;
    return pList->currentNode;
}

void* List_last(List* pList){
    if (pList->len == 0) {
        return NULL;
    }
    pList->currentNode = pList->tail;
    return pList->currentNode;
}

void* List_next(List* pList) {
    // if OOB at the end, return NULL
    if (pList->currentPointerState == 1) {
        return NULL;
    }
    // if currentPointer is OOB at the start, move pointer to head
    if (pList->currentPointerState == 0) {
        pList->currentNode = pList->head;
        pList->currentPointerState = 2;
        return pList->currentNode;
    }
    if (pList->currentNode->nextNode == NULL){
        pList->currentPointerState = LIST_OOB_END;
        printf("Out of bounds status: %d\n", pList->currentPointerState);
        pList->currentNode = pList->currentNode->nextNode;
        return NULL;
    }
    pList->currentNode = pList->currentNode->nextNode;
    return pList->currentNode;
}

void* List_prev(List* pList){
    // if OOB at the start, return NULL
    if (pList->currentPointerState == 0) {
        return NULL;
    }
    // if currentPointer is OOB at the end, move pointer to tail
    if (pList->currentPointerState == 1) {
        pList->currentNode = pList->tail;
        pList->currentPointerState = 2; // set status to something else (not OOB)
        return pList->currentNode;
    }
    if (pList->currentNode->prevNode == NULL){
        pList->currentPointerState = LIST_OOB_START;
        printf("Out of bounds status: %d\n", pList->currentPointerState);
        pList->currentNode = pList->currentNode->prevNode;
        return NULL;
    }
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
        pList->head = newNode;
        pList->tail = newNode;

    } else {
        newNode = createNode(NULL, pList->tail, pItem);
        pList->tail->nextNode = newNode;
        pList->tail = newNode;
    }
    pList->currentNode = newNode;
    pList->len++;
    return 0;
}

void* List_trim(List* pList) {
    void* oldTail = pList->tail->nodeVal;
    // adjust pointers
    Node* tailPrev = pList->tail->prevNode;
    tailPrev->nextNode = NULL;

    freeNode(pList->tail);

    pList->tail = tailPrev;
    pList->currentNode = pList->tail;
    return oldTail;
}

static void* List_trimFront(List* pList) {
    void* oldHead = pList->head->nodeVal;
    // adjust pointers
    Node* headNext = pList->head->nextNode;
    headNext->prevNode = NULL;

    freeNode(pList->head);

    pList->head = headNext;
    pList->currentNode = pList->head;

    return oldHead;
}

void* List_remove(List* pList) {
    if (pList->currentPointerState == 0 || pList->currentPointerState == 1) {
        return NULL;
    }
    void* oldCurrentValue = pList->currentNode->nodeVal;
    // if currentPointer is a header
    if (pList->currentNode == pList->tail) {
        void* pVal = List_trim(pList);
        return pVal;
    } 
    // if currentPointer is a tail
    else if (pList->currentNode == pList->head) {
        void* pVal = List_trimFront(pList);
        return pVal;
    } 
    // if currentPointer is between two nodes
    else {
        // adjust pointers
        Node* currPrev = pList->currentNode->prevNode;
        Node* currNext = pList->currentNode->nextNode;
        currPrev->nextNode = currNext;
        currNext->prevNode = currPrev;

        freeNode(pList->currentNode);

        // update current node
        pList->currentNode = currNext;
        return oldCurrentValue;
    }
}

void List_concat(List* pList1, List* pList2) {
    pList1->tail->nextNode = pList2->head;
    pList2->head->prevNode = pList1->tail;
    pList1->tail = pList2->tail;
    freeHeadList(pList2);
}

void List_free(List* pList, FREE_FN pItemFreeFn) {
    Node* current = pList->head;
    while(current) {
        Node* currentNext = current->nextNode;
        (*pItemFreeFn)(current->nodeVal);
        current->nextNode = pNodeList;
        current->prevNode = NULL;
        pNodeList = current;
        current = currentNext;
    }
    freeHeadList(pList);
}


