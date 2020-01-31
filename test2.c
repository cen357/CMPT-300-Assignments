#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 10
// Node element for linked list
typedef struct Node
{
    void *item;
    struct Node *next;
    struct Node *prev;
} NODE;

// List abstract data structure
typedef struct List
{
    int size;
    struct List *link;
    NODE *head;
    NODE *tail;
    NODE *current;
    _Bool isValid;
    _Bool isBeforeFirstItem;
    _Bool isBeyondLastItem;

} LIST;

// Global arrays that store nodes and heads
NODE nodes_array[MAX_LENGTH];
LIST lists_array[MAX_LENGTH];

// First free node or free head in the arrays
static NODE *freeNode;
static LIST *freeList;

// ---------------------------------------Memory Allocation--------------------------------//
// Init a free memory array for data storage
void init()
{
    // link list for freeNode and freeList traversal
    nodes_array[MAX_LENGTH - 1].next = NULL;
    lists_array[MAX_LENGTH - 1].link = NULL;
    nodes_array[0].prev = NULL;

    for (int i = 0; i < MAX_LENGTH - 1; i++)
    {
        nodes_array[i].next = &nodes_array[i + 1];
        lists_array[i].link = &lists_array[i + 1];
        nodes_array[i + 1].prev = NULL;
    }

    // Set free node and free list at the beginning of the array
    freeNode = &nodes_array[0];
    freeList = &lists_array[0];
}

void resetList(LIST *list)
{
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    list->isValid = 0;
    list->isBeforeFirstItem = 0;
    list->isBeyondLastItem = 0;
}

void resetNode(NODE *node)
{
    node->item = NULL;
}

// Find new list head
LIST *findNewList()
{
    LIST *newList = freeList;
    // Case: List array exhausted
    if (freeList == NULL)
    {
        return NULL;
    }
    else
    {
        resetList(newList);
        // Move to the next free list in the array
        freeList = freeList->link;
        newList->link = NULL;
    }

    return newList;
}

// Find new list Node
NODE *findNewNode()
{
    NODE *newNode = freeNode;
    // Case: Node array exhausted
    if (freeNode == NULL)
    {
        return NULL;
    }
    else
    {
        resetNode(newNode);
        // Move to the next free node in the array
        freeNode = freeNode->next;
    }

    return newNode;
}

void freeNodeFromArray(NODE *node)
{
    resetNode(node);
    if (freeNode == NULL)
    {
        freeNode = node;
        freeNode->next = NULL;
    }
    else
    {
        node->next = freeNode;
        freeNode = node;
    }
}

void freeListFromArray(LIST *list)
{
    resetList(list);
    if (freeList == NULL)
    {
        freeList = list;
        freeList->link = NULL;
    }
    else
    {
        list->link = freeList;
        freeList = list;
    }
}
//------------------------------End of Memory Allocation-------------------------//

// ------------------------------Current Pointer---------------------------------//
_Bool isNull(LIST *list)
{
    return (((list->isBeforeFirstItem == 0) && (list->isBeyondLastItem == 0) && (list->isValid == 0)) || (list->size == 0)) ? 1 : 0;
}

_Bool isValid(LIST *list)
{
    return ((list->isBeforeFirstItem == 0) && (list->isBeyondLastItem == 0) && (list->isValid == 1) && (list->size != 0)) ? 1 : 0;
}

_Bool isBeforeFirstItem(LIST *list)
{
    return ((list->isBeforeFirstItem == 1) && (list->isBeyondLastItem == 0) && (list->isValid == 0) && (list->size != 0)) ? 1 : 0;
}

_Bool isBeyondLastItem(LIST *list)
{
    return ((list->isBeforeFirstItem == 0) && (list->isBeyondLastItem == 1) && (list->isValid == 0) && (list->size != 0)) ? 1 : 0;
}

void setCurrentItemNull(LIST *list)
{
    list->isValid = 0;
    list->isBeforeFirstItem = 0;
    list->isBeyondLastItem = 0;
}

void setCurrentItemValid(LIST *list)
{
    list->isValid = 1;
    list->isBeforeFirstItem = 0;
    list->isBeyondLastItem = 0;
}

void setCurrentItemBeforeHead(LIST *list)
{
    list->isValid = 0;
    list->isBeforeFirstItem = 1;
    list->isBeyondLastItem = 0;
}

void setCurrentItemBeyondTail(LIST *list)
{
    list->isValid = 0;
    list->isBeforeFirstItem = 0;
    list->isBeyondLastItem = 1;
}

void updateCurrentItemStatus(LIST *list)
{
    if (list->current != NULL)
    {
        setCurrentItemValid(list);
    }
    else if (list->head->prev == list->current)
    {
        setCurrentItemBeforeHead(list);
    }
    else if (list->tail->next == list->current)
    {
        setCurrentItemBeyondTail(list);
    }
    else
    {
        setCurrentItemNull(list);
    }
}

// ----------------------------End of Current Pointer---------------------//

// -------------------------Functionality--------------------------------//
// List create
LIST *ListCreate()
{
    LIST *newList = findNewList();

    if (newList == NULL)
    {
        return NULL;
    }

    return newList;
}

// List count
int ListCount(LIST *list)
{
    return list->size;
}

// List first
void *ListFirst(LIST *list)
{
    if ((list == NULL) || (list->size == 0))
    {
        return NULL;
    }
    else
    {
        list->current = list->head;
        setCurrentItemValid(list);
    }

    return list->head->item;
}

void *ListLast(LIST *list)
{
    if ((list == NULL) || (list->size == 0))
    {
        return NULL;
    }
    else
    {
        list->current = list->tail;
        setCurrentItemValid(list);
    }

    return list->tail->item;
}

void *ListNext(LIST *list)
{
    if ((list == NULL) || (list->size == 0) || (list->current == NULL))
    {
        return NULL;
    }
    else if (list->current->next == NULL)
    {
        setCurrentItemBeyondTail(list);
    }
    else
    {
        list->current = list->current->next;
        updateCurrentItemStatus(list);
    }

    return list->current->item;
}

void *ListPrev(LIST *list)
{
    if ((list == NULL) || (list->size == 0) || (list->current == NULL))
    {
        return NULL;
    }
    else if ((list->current->prev == NULL))
    {
        setCurrentItemBeforeHead(list);
    }
    else
    {
        list->current = list->current->prev;
        updateCurrentItemStatus(list);
    }
    return list->current->item;
}

void *ListCurr(LIST *list)
{
    if ((list == NULL) || (list->size == 0) || (list->current == NULL) || (isValid(list) == 0))
        return NULL;

    return list->current->item;
}

// List add
int ListAdd(LIST *list, void *value)
{
    if ((list == NULL) || (freeNode == NULL))
    {
        return -1;
    }

    if (list->size == 0)
    {
        NODE *newListNode = findNewNode(list);
        newListNode->item = value;
        list->head = newListNode;
        list->tail = newListNode;
        list->current = newListNode;
        setCurrentItemValid(list);
        list->size++;
        return 0;
    }
    else if (list->head == list->tail)
    {
        NODE *newListNode = findNewNode(list);
        newListNode->item = value;
        list->head->next = newListNode;
        newListNode->prev = list->head;
        list->tail = newListNode;
        list->current = newListNode;
        setCurrentItemValid(list);
        list->size++;
        return 0;
    }
    else if ((isBeforeFirstItem(list) == 1) || (list->current == list->head))
    {
        NODE *newListNode = findNewNode(list);
        newListNode->item = value;
        newListNode->next = list->head->next;
        list->head->next->prev = newListNode;
        list->head->next = newListNode;
        newListNode->prev = list->head;
        list->current = newListNode;
        setCurrentItemValid(list);
        list->size++;
        return 0;
    }
    else if ((isBeyondLastItem(list) == 1) || (list->current == list->tail))
    {
        NODE *newListNode = findNewNode(list);
        newListNode->item = value;
        newListNode->next = NULL;
        newListNode->prev = list->tail;
        list->tail->next = newListNode;
        list->tail = newListNode;
        list->current = list->tail;
        setCurrentItemValid(list);
        list->size++;
        return 0;
    }
    else if (isValid(list) == 1)
    {
        NODE *newListNode = findNewNode(list);
        newListNode->item = value;
        newListNode->next = list->current->next;
        list->current->next->prev = newListNode;
        list->current->next = newListNode;
        newListNode->prev = list->current;
        list->current = newListNode;
        setCurrentItemValid(list);
        list->size++;
        return 0;
    }

    return 0;
}

//---------------------------------------------------------------------------//

int main()
{
    init();
    LIST *test = ListCreate();
    LIST *test2 = ListCreate();
    int a = 1;
    float b = 2;
    double c = 3.5;

    // Test driver
    printf("List size: %d\n", ListCount(test));
    printf("List size: %d\n", ListCount(test2));

    printf("List current test 1: %p\n", test);
    printf("List test[0]: %p\n", &lists_array[0]);
    printf("List current test 2: %p\n", test2);
    printf("List test[1]: %p\n", &lists_array[1]);

    printf("Node test[0]: %p\n", &nodes_array[0]);
    printf("Node test[1]: %p\n", &nodes_array[1]);

    ListAdd(test, &a);
    printf("size: %d\n", test->size);
    ListAdd(test, &b);
    printf("size: %d\n", test->size);
    ListAdd(test, &c);
    printf("size: %d\n", test->size);

    printf("a test: %p\n", &a);
    printf("b test: %p\n", &b);
    printf("c test: %p\n", &c);

    printf("item a test: %p\n", test->head->item);
    printf("item b test: %p\n", test->head->next->item);
    printf("item c test: %p\n", test->tail->item);

    printf("current test: %p\n", ListCurr(test));
    printf("move test: %p\n", ListFirst(test));
    printf("move test: %p\n", ListNext(test));
    printf("move test: %p\n", ListPrev(test));
    printf("move test: %p\n", ListPrev(test));

    return 0;
}