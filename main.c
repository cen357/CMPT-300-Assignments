#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 10
// Node element for linked list
typedef struct Node
{
    int item;
    struct Node *next;
    struct Node *prev;
} NODE;

// List abstract data structure
typedef struct List
{
    int count;
    NODE *head;
    NODE *tail;
    struct Current
    {
        NODE *pointer;
        _Bool isValid;
        _Bool isBeforeFirstItem;
        _Bool isBeyondLastItem;
    } current;

} LIST;

// Global arrays that store nodes and heads
NODE nodes_array[MAX_LENGTH];
NODE heads_array[MAX_LENGTH];

// First free node or free head in the arrays
static NODE *freeListNode;
static NODE *freeListHead;

int main()
{
    // ------------------------Main Init------------------------------------
    int a = 1;
    int b = 1;
    LIST test;

    // Array init
    nodes_array[MAX_LENGTH - 1].next = NULL;
    heads_array[MAX_LENGTH - 1].next = NULL;
    nodes_array[0].prev = NULL;
    heads_array[0].prev = NULL;

    for (int i = 0; i < MAX_LENGTH - 2; i++)
    {
        nodes_array[i].next = &nodes_array[i + 1];
        heads_array[i].next = &heads_array[i + 1];
        nodes_array[i + 1].prev = &nodes_array[i];
        heads_array[i + 1].prev = &heads_array[i];
    }

    freeListNode = &nodes_array[0];
    freeListHead = &heads_array[0];
    // --------------------End of Main init -----------------------------------

    // --------------------------------Helper Functions ----------------------------
    // Find new head
    NODE *newListHead = freeListHead;
    freeListHead = freeListHead->next;
    freeListHead->item = 2;

    // Find new Node
    NODE *newListNode = freeListNode;
    freeListNode = freeListNode->next;
    freeListHead->item = 2;

    // ---------------------------End of Helper functions --------------------------

    // --------------------------------Main functions------------------------------
    // New list init
    test.count = 0;
    test.head = newListHead;
    test.head->item = 0;
    test.head->next = newListNode;
    test.head->prev = NULL;
    test.tail = test.head;
    test.current.pointer = test.head;

    if (test.current.pointer != NULL)
    {
        test.current.isValid = 1;
        test.current.isBeforeFirstItem = 0;
        test.current.isBeyondLastItem = 0;
    }
    else if (test.current.pointer->next == test.head)
    {
        test.current.isValid = 0;
        test.current.isBeforeFirstItem = 1;
        test.current.isBeyondLastItem = 0;
    }
    else if (test.current.pointer->prev == test.tail)
    {
        test.current.isValid = 0;
        test.current.isBeforeFirstItem = 0;
        test.current.isBeyondLastItem = 1;
    }
    //---------------------------------End of functions-----------------------------

    // Test driver
    printf("List count: %d\n", test.count);
    printf("Head address: %p\n", test.head);
    printf("Head item: %d\n", test.head->item);
    printf("Head next: %p\n", test.head->next);
    printf("Head prev: %p\n", test.head->prev);
    printf("Tail address: %p\n", test.tail);
    printf("Tail item: %d\n", test.tail->item);
    printf("Tail next: %p\n", test.tail->next);
    printf("Tail prev: %p\n", test.tail->prev);
    printf("Current pointer address: %p\n", test.current.pointer);
    printf("Current is valid: %d\n", test.current.isValid);
    printf("Current is is before: %d\n", test.current.isBeforeFirstItem);
    printf("Current is beyond: %d\n", test.current.isBeyondLastItem);
    printf("Current item: %d\n", test.current.pointer->item);
    printf("Current next: %p\n", test.current.pointer->next);
    printf("Current prev: %p\n", test.current.pointer->prev);
    return 0;
}