#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 5
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
// Init two free memory stacks for data storage
// Initially both stacks contain full free nodes and list
// free list or free node traversal reduce the stack until empty (either of them equals to NULL)
void init()
{
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
        // Move to the next free node in the array
        freeNode = freeNode->next;
        resetNode(newNode);
    }

    return newNode;
}

void freeNodeFromArray(NODE *node)
{
    if (node == freeNode)
    {
        freeNode = freeNode->next;
        resetNode(node);
        node->next = freeNode;
        freeNode = node;
    }
    // Case node array is exhausted
    if (freeNode == NULL)
    {
        resetNode(node);
        // new first free node
        freeNode = node;
        freeNode->next = NULL;
    }
    else
    {
        resetNode(node);
        // add new free node to the free node stack
        node->next = freeNode;
        freeNode = node;
    }
}

void freeListFromArray(LIST *list)
{

    if (list->head == list->tail)
    {
        freeList = freeList->link;
        resetList(list);
        list->link = freeList;
        freeList = list;
    }

    if (freeList == NULL)
    {
        resetList(list);
        freeList = list;
        freeList->link = NULL;
    }
    else
    {
        resetList(list);
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

// List insert
int ListInsert(LIST *list, void *value)
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
        newListNode->item = list->head->item;
        list->head->next = newListNode;
        newListNode->prev = list->head;
        list->head->item = value;
        list->tail = newListNode;
        list->current = list->head;
        setCurrentItemValid(list);
        list->size++;
        return 0;
    }
    else if ((isBeforeFirstItem(list) == 1) || (list->current == list->head))
    {
        NODE *newListNode = findNewNode(list);
        newListNode->item = value;
        newListNode->next = list->head;
        list->head->prev = newListNode;
        list->head = newListNode;
        list->current = newListNode;
        setCurrentItemValid(list);
        list->size++;
        return 0;
    }
    else if ((isBeyondLastItem(list) == 1) || (list->current == list->tail))
    {
        NODE *newListNode = findNewNode(list);
        newListNode->item = value;
        list->tail->prev->next = newListNode;
        newListNode->prev = list->tail->prev;
        newListNode->next = list->tail;
        list->tail->prev = newListNode;
        list->current = newListNode;
        setCurrentItemValid(list);
        list->size++;
        return 0;
    }
    else if (isValid(list) == 1)
    {
        NODE *newListNode = findNewNode(list);
        newListNode->item = value;
        list->current->prev->next = newListNode;
        newListNode->prev = list->current->prev;
        newListNode->next = list->current;
        list->current->prev = newListNode;
        list->current = newListNode;
        setCurrentItemValid(list);
        list->size++;
        return 0;
    }

    return 0;
}

//List Append
int ListAppend(LIST *list, void *value)
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
    else
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

    return 0;
}

// List Prepend
int ListPrepend(LIST *list, void *value)
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
        newListNode->item = list->head->item;
        list->head->next = newListNode;
        newListNode->prev = list->head;
        list->head->item = value;
        list->tail = newListNode;
        list->current = list->head;
        setCurrentItemValid(list);
        list->size++;
        return 0;
    }
    else
    {
        NODE *newListNode = findNewNode(list);
        newListNode->item = value;
        newListNode->next = list->head;
        list->head->prev = newListNode;
        list->head = newListNode;
        list->current = newListNode;
        setCurrentItemValid(list);
        list->size++;
        return 0;
    }

    return 0;
}

// List trim
void *ListTrim(LIST *list)
{
    NODE *removedItem;
    if ((list == NULL) || (list->size == 0))
    {
        return NULL;
    }

    if ((list->head == list->tail))
    {
        removedItem = list->head->item;
        freeNodeFromArray(list->head);
        freeListFromArray(list);
    }
    else
    {
        list->current = list->tail;
        removedItem = list->current->item;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        freeNodeFromArray(list->current);
        list->current = list->tail;
        setCurrentItemValid(list);
        list->size--;
    }

    return removedItem;
}

void freeItemFromList(void *value)
{
    value = NULL;
}

// List free
void ListFree(LIST *list, void (*itemFree)(void *itemToBeFreed))
{
    if ((list == NULL) || (list->size == 0))
    {
        return;
    }

    if ((list->head == list->tail))
    {
        freeNodeFromArray(list->head);
        freeListFromArray(list);
    }
    else
    {
        while (list->head != list->tail)
        {
            NODE *temp = list->tail;
            list->tail = list->tail->prev;
            list->tail->next = NULL;
            (*itemFree)(temp->item);
            freeNodeFromArray(list->current);
            list->current = list->tail;
            setCurrentItemValid(list);
            list->size--;
        }

        freeListFromArray(list);
    }
}

void ListConcat(LIST *list1, LIST *list2)
{
    if ((list1 != NULL) && (list2 != NULL))
    {
        list1->tail->next = list2->head;
        list2->head->prev = list1->tail;
        list1->tail = list2->tail;
        list1->size += list2->size;
        ListFree(list2, freeItemFromList);
    }
    else
    {
        return;
    }
}

int compare(void *value1, void *value2)
{
    return (value1 == value2) ? 1 : 0;
}

void *ListSearch(LIST *list, int (*comparator)(void *item1, void *item2), void *comparisonArg)
{
    if ((list == NULL) || (list->size == 0) || (comparator == NULL) || (comparisonArg == NULL) || (isValid(list) == 0))
    {
        return NULL;
    }

    while (list->current != list->tail)
    {
        if ((*comparator)(comparisonArg, list->current->item) == 1)
        {
            return list->current->item;
        }
        list->current = list->current->next;
    }

    list->current = list->current->next;
    setCurrentItemBeyondTail(list);

    return NULL;
}

//---------------------------------------------------------------------------//

int main()
{
    init();
    LIST *test = ListCreate();
    LIST *test2 = ListCreate();
    int a = 1;
    float b = 2.0;
    double c = 3.5;
    long d = 3;
    int e = 32;

    // Test driver
    printf("List current test 1: %p\n", test);
    printf("list array[0]: %p\n", &lists_array[0]);
    printf("List array[1]: %p\n", &lists_array[1]);
    printf("List array[2]: %p\n", &lists_array[2]);
    printf("List array[3]: %p\n", &lists_array[3]);
    printf("List array[4]: %p\n\n", &lists_array[4]);

    printf("Node array[0]: %p\n", &nodes_array[0]);
    printf("Node array[1]: %p\n", &nodes_array[1]);
    printf("Node array[2]: %p\n", &nodes_array[2]);
    printf("Node array[3]: %p\n", &nodes_array[3]);
    printf("Node array[4]: %p\n\n", &nodes_array[4]);

    ListAdd(test, &a);
    ListAdd(test, &b);
    ListAdd(test, &c);

    printf("a test: %p\n", &a);
    printf("b test: %p\n", &b);
    printf("c test: %p\n", &c);
    printf("d test: %p\n", &d);
    printf("e test: %p\n", &e);

    printf("current test: %p\n", ListCurr(test));
    printf("prepend test: %d\n", ListPrepend(test, &d));
    printf("current test: %p\n", ListCurr(test));
    printf("next test: %p\n", ListNext(test));
    printf("current test: %p\n\n", ListCurr(test));
    ListFree(test, freeItemFromList);

    ListAppend(test2, &a);
    ListAppend(test2, &b);
    ListAppend(test2, &c);
    printf("count test: %d\n\n", ListCount(test2));

    LIST *test3 = ListCreate();
    ListAppend(test3, &d);
    ListAppend(test3, &e);
    printf("count test: %d\n\n", ListCount(test3));

    return 0;
}