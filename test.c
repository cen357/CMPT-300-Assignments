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

// ---------------------------------------Memory Allocation--------------------------------//
// Init memory cache array
void init()
{
    // Array init
    nodes_array[MAX_LENGTH - 1].next = NULL;
    heads_array[MAX_LENGTH - 1].next = NULL;
    nodes_array[0].prev = NULL;
    heads_array[0].prev = NULL;

    for (int i = 0; i < MAX_LENGTH - 1; i++)
    {
        nodes_array[i].next = &nodes_array[i + 1];
        heads_array[i].next = &heads_array[i + 1];
        nodes_array[i + 1].prev = NULL;
        heads_array[i + 1].prev = NULL;
    }

    freeListNode = &nodes_array[0];
    freeListHead = &heads_array[0];
}

// Find new list head
NODE *findNewListHead()
{
    NODE *newListHead = freeListHead;
    if (freeListHead == NULL)
    {
        return NULL;
    }
    else
    {
        freeListHead = freeListHead->next;
    }
    return newListHead;
}

// Find new list Node
NODE *findNewListNode()
{
    NODE *newListNode = freeListNode;
    if (freeListNode == NULL)
    {
        return NULL;
    }
    else
    {
        freeListNode = freeListNode->next;
    }

    return newListNode;
}

void freeNodeFromList(NODE *nodeElement)
{
    nodeElement->item = NULL;
    nodeElement->prev = NULL;
    nodeElement->next = freeListNode;
    freeListNode = nodeElement;
}

void freeHeadFromList(NODE *headElement)
{
    headElement->item = NULL;
    headElement->prev = NULL;
    headElement->next = freeListHead;
    freeListHead = headElement;
}
//------------------------------End of Memory Allocation-------------------------//

// ------------------------------Current Pointer---------------------------------//

_Bool isValid(LIST *list)
{
    return ((list->current.isBeforeFirstItem == 1) || (list->current.isBeyondLastItem) == 1 || (list->size == 0)) ? 0 : 1;
}

_Bool isBeforeFirstItem(LIST *list)
{
    return ((list->current.isValid == 1) || (list->current.isBeyondLastItem == 1) || (list->size == 0)) ? 0 : 1;
}

_Bool isBeyondLastItem(LIST *list)
{
    return ((list->current.isBeforeFirstItem == 1) || (list->current.isValid == 1) || (list->size == 0)) ? 0 : 1;
}

void setCurrentItemNull(LIST *list)
{
    list->current.isValid = 0;
    list->current.isBeforeFirstItem = 0;
    list->current.isBeyondLastItem = 0;
}

void setCurrentItemValid(LIST *list)
{
    list->current.isValid = 1;
    list->current.isBeforeFirstItem = 0;
    list->current.isBeyondLastItem = 0;
}

void setCurrentItemBeforeHead(LIST *list)
{
    list->current.isValid = 0;
    list->current.isBeforeFirstItem = 1;
    list->current.isBeyondLastItem = 0;
}

void setCurrentItemBeyondTail(LIST *list)
{
    list->current.isValid = 0;
    list->current.isBeforeFirstItem = 0;
    list->current.isBeyondLastItem = 1;
}

void updateCurrentItemStatus(LIST *list)
{
    if (.current.pointer != NULL)
    {
        setCurrentItemValid();
    }
    else if (list.current.pointer->next == test.head)
    {
        setCurrentItemBeforeHead();
    }
    else if (list.current.pointer->prev == test.tail)
    {
        setCurrentItemBeyondTail();
    }
}

// ----------------------------End of Current Pointer---------------------//

// -------------------------Functionality--------------------------------//
// List create
LIST *ListCreate()
{
    LIST newList;
    NODE *newListHead = findNewListHead();

    if (newListHead == NULL)
    {
        return -1;
    }
    else
    {
        newList.size = 0;
        newList.head = newListHead;
        newList.tail = newList.head;
        newList.current.pointer = newList.head;
        newList.current.isValid = 0;
        newList.current.isBeforeFirstItem = 0;
        newList.current.isBeyondLastItem = 0;
    }

    LIST *listReference = &newList;

    return listReference;
}

// List count
int ListCount(LIST *list)
{
    return list->size;
}

// List first
void *ListFirst(LIST *list)
{
    if (list->size == 0)
        return NULL;

    list->current.pointer = list->head;
    setCurrentItemValid(list);

    return list->head->item;
}

void *ListLast(LIST *list)
{
    if (list->size == 0)
        return NULL;

    list->current.pointer = list->tail;
    setCurrentItemValid(list);

    return list->tail->item;
}

void *ListNext(LIST *list)
{
    if ((list->size == 0) || (list->current.pointer == NULL) || (list->current.pointer->next == NULL))
        return NULL;

    list->current.pointer = list->current.pointer->next;
    updateCurrentItemStatus(list);
    return list->current.pointer->item;
}

void *ListPrev(LIST *list)
{
    if ((list->size == 0) || (list->current.pointer == NULL) || (list->current.pointer->prev == NULL))
        return NULL;

    list->current.pointer = list->current.pointer->prev;
    updateCurrentItemStatus(list);
    return list->current.pointer->item;
}

void *ListCurr(LIST *list)
{
    if ((list->size == 0) || (list->current.pointer == NULL) || (isValid(list) == 0))
        return NULL;

    return list->current.pointer->item;
}

// List add
int ListAdd(LIST *list, void *value)
{
    if (newListNode == NULL)
    {
        return -1;
    }

    if (list->size == 0)
    {
        list->head->next = NULL;
        list->head->prev = NULL;
        list->head->item = value;
        list->tail = list->head;
        list->current.pointer = list->head;
        setCurrentItemValid(list);
        list->size++;
    }
    else if (list->size == 1)
    {
        NODE *newListNode = findNewListNode(list);
        list->head->next = newListNode;
        newListNode->prev = list->head;
        list->tail = newListNode;
        list->current.pointer = newListNode;
        setCurrentItemValid(list);
        list->size++;
    }
    else if ((isBeforeFirstItem(list) == 1) || (list->current.pointer == list->head))
    {
        NODE *newListNode = findNewListNode(list);
        newListNode->item = value;
        newListNode->next = list->head->next;
        list->head->next->prev = newListNode;
        list->head->next = newListNode;
        newListNode->prev = list->head;
        list->head->item = value;
        list->current.pointer = newListNode;
        setCurrentItemValid(list);
        list->size++;
    }
    else if ((isBeyondLastItem(list) == 1) || (list->current.pointer == list->tail))
    {
        NODE *newListNode = findNewListNode(list);
        newListNode->item = value;
        newListNode->next = NULL;
        newListNode->prev = list->tail;
        list->tail->next = newListNode;
        list->tail = newListNode;
        list->current.pointer = list->tail;
        setCurrentItemValid(list);
        list->size++;
    }
    else if (isValid(list) == 1)
    {
        NODE *newListNode = findNewListNode(list);
        newListNode->item = value;
        newListNode->next = list->current.pointer->next;
        list->current.pointer->next->prev = newListNode;
        list->current.pointer->next = newListNode;
        newListNode->prev = list->current.pointer;
        list->current.pointer = newListNode;
        setCurrentItemValid(list);
        list->size++;
    }

    return 0;
}

// List insert
int ListInsert(LIST *list, void *value)
{
    if (newListNode == NULL)
    {
        return -1;
    }

    if (list->size == 0)
    {
        list->head->next = NULL;
        list->head->prev = NULL;
        list->head->item = value;
        list->tail = list->head;
        list->current.pointer = list->head;
        setCurrentItemValid(list);
        list->size++;
    }
    else if (list->size == 1)
    {
        NODE *newListNode = findNewListNode(list);
        list->head->next = newListNode;
        newListNode->item = list->head->item;
        list->head->item = value;
        list->tail = newListNode;
        list->current.pointer = list->head;
        setCurrentItemValid(list);
        list->size++;
    }
    else if ((isBeforeFirstItem(list) == 1) || (list->current.pointer == list->head))
    {
        NODE *newListNode = findNewListNode(list);
        list->head->prev = NULL;
        newListNode->next = list->head->next;
        list->head->next->prev = newListNode;
        list->head->next = newListNode;
        newListNode->prev = list->head;
        newListNode->item = list->head->item;
        list->head->item = value;
        list->current.pointer = list->head;
        setCurrentItemValid(list);
        list->size++;
    }
    else if ((isBeyondLastItem(list) == 1) || (list->current.pointer == list->tail))
    {
        NODE *newListNode = findNewListNode(list);
        newListNode->item = value;
        list->tail->prev->next = newListNode;
        newListNode->prev = list->tail->prev;
        newListNode->next = list->tail;
        list->tail->prev = newListNode;
        list->current.pointer = newListNode;
        setCurrentItemValid(list);
        list->size++;
    }
    else if (isValid(list) == 1)
    {
        NODE *newListNode = findNewListNode(list);
        newListNode->item = value;
        list->current.pointer->prev->next = newListNode;
        newListNode->prev = list->current.pointer->prev;
        newListNode->next = list->current.pointer;
        list->current.pointer->prev = newListNode;
        list->current.pointer = newListNode;
        setCurrentItemValid(list);
        list->size++;
    }

    return 0;
}

//List Append
int ListAppend(LIST *list, void *value)
{
    if ((isValid(list) == 0) || (newListNode == NULL))
    {
        return -1;
    }

    if (list->size == 0)
    {
        list->head->next = NULL;
        list->head->prev = NULL;
        list->head->item = value;
        list->tail = list->head;
        list->current.pointer = list->head;
        setCurrentItemValid(list);
    }
    else
    {
        NODE *newListNode = findNewListNode(list);
        newListNode->next = NULL;
        list->tail->next = newListNode;
        newListNode->prev = list->tail;
        newListNode->item = value;
        list->tail = newListNode;
        list->current.pointer = newListNode;
        setCurrentItemValid(list);
        list->size++;
    }

    return 0;
}

// List Prepend
int ListPrepend(LIST *list, void *value)
{
    if ((isValid(list) == 0) || (newListNode == NULL))
    {
        return -1;
    }

    if (list->size == 0)
    {
        list->head->next = NULL;
        list->head->prev = NULL;
        list->head->item = value;
        list->tail = list->head;
        list->current.pointer = list->head;
        setCurrentItemValid(list);
    }
    else if (list->size == 1)
    {
        NODE *newListNode = findNewListNode(list);
        newListNode->next = list->head->next;
        list->head->next->prev = newListNode;
        list->head->next = newListNode;
        newListNode->prev = list->head;
        newListNode->item = list->head->item;
        list->head->item = value;
        list->tail = newListNode;
        list->current.pointer = list->head;
        setCurrentItemValid(list);
        list->size++;
    }
    else
    {
        NODE *newListNode = findNewListNode(list);
        newListNode->next = list->head->next;
        list->head->next->prev = newListNode;
        list->head->next = newListNode;
        newListNode->prev = list->head;
        newListNode->item = list->head->item;
        list->head->item = value;
        list->current.pointer = list->head;
        setCurrentItemValid(list);
        list->size++;
    }

    return 0;
}

// List trim
void *ListTrim(list)
{
    NODE *removedItem = NULL;
    if (list->size == 0)
    {
        return NULL;
    }

    if ((list->size == 1))
    {
        removedItem = list->head;
        list->head->next = NULL;
        list->head->prev = NULL;
        list->head->item = NULL;
        list->tail = list->head;
        list->current.pointer = list->head;
        setCurrentItemNull(list);
        list->size--;
    }
    else
    {
        list->current.pointer = list->tail;
        removedItem = list->current.pointer->item;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        freeNodeFromList(list->current.pointer);
        list->current.pointer = list->tail;
        setCurrentItemValid(list);
        list->size--;
    }

    return removedItem;
}

// List remove
void *ListRemove(list)
{
    NODE *removedItem = NULL;
    if ((isValid(list) == 0) || (list->size == 0))
    {
        return NULL;
    }

    if (list->size == 1)
    {
        removedItem = list->head->item;
        list->head->next = NULL;
        list->head->prev = NULL;
        list->head->item = NULL;
        list->tail = list->head;
        list->current.pointer = list->head;
        setCurrentItemNull(list);
        list->size--;
    }
    else if (list->size == 2)
    {
        if (list->current.pointer == list->head)
        {
            removedItem = list->head->item;
            list->current.pointer = list->tail;
            list->head->next = NULL;
            freeNodeFromList(list->current.pointer);
            list->head->item = removedItem;
            list->tail = list->head;
            list->current.pointer = list->head;
            setCurrentItemValid(list);
            list->size--;
        }
        else if (list->current.pointer == list->tail)
        {
            removedItem = list->tail->item;
            list->current.pointer = list->tail;
            list->head->next = NULL;
            freeNodeFromList(list->current.pointer);
            list->tail = list->head;
            list->current.pointer = list->head;
            setCurrentItemValid(list);
            list->size--;
        }
    }
    else if (list->size > 2)
    {
        if (list->current.pointer == list->head)
        {
            removedItem = list->head;
            list->current.pointer = list->head->next;
            list->head->item = list->current.pointer->item;
            list->head->next = list->current.pointer->next;
            list->current.pointer->next->prev = list->head;
            freeNodeFromList(list->current.pointer);
            list->current.pointer = list->head;
            setCurrentItemValid(list);
            list->size--;
        }
        else if (list->current.pointer == list->tail)
        {
            removedItem = list->tail->item;
            list->current.pointer = list->tail->prev;
            list->tail->prev = list->current.pointer->prev;
            list->current.pointer->prev->next = list->tail;
            freeNodeFromList(list->current.pointer);
            list->current.pointer = list->tail;
            setCurrentItemValid(list);
            list->size--;
        }
        else
        {
            removedItem = list->current.pointer->item;
            NODE *beforeCurrentItem = list->current.pointer->prev;
            NODE *afterCurrentItem = list->current.pointer->next;
            beforeCurrentItem->next = afterCurrentItem;
            afterCurrentItem->prev = beforeCurrentItem;
            freeNodeFromList(list->current.pointer);
            list->current.pointer = afterCurrentItem;
            setCurrentItemValid(list);
            list->size--;
        }
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

    while (list->head != list->tail)
    {
        list->current.pointer = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        (*itemFree)(list->current.pointer->item);
        freeNodeFromList(list->current.pointer);
        list->current.pointer = list->tail;
        setCurrentItemValid(list);
        list->size--;
    }

    freeHeadFromList(list->head);
    list = NULL;

    return;
}

void ListConcat(LIST *list1, LIST *list2)
{
    if (((list1->size != 0) || (list1->size != 1)) && ((list2->size != 0) || (list2->size != 1)))
    {
        list1->tail->next = list2->head;
        list2->head->prev = list1->tail;
        list1->tail = list2->tail;
        list1->size += list2->size;
        ListFree(list2);
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

void *ListSearch(LIST *list, int (*comparator)(void *item1, void *item2),
                 void *comparisonArg)
{
    if ((list->size == 0) || (comparator == NULL) || (comparisonArg == NULL) || (isValid(list) == 0) {
        return NULL;
    }

    while ((*comparator)(comparisonArg, list->current.pointer->item) != 1)
    {
        if (list->current.pointer == list->tail)
            break;
        list->current.pointer = list->current.pointer->next;
    }

    return list->current.pointer->item;
}

//-----------------------------------Functionality----------------------------//

void print(int x)
{
    printf("%d\n", x);
}

void ad(int a, void (*itemFree)(int item))
{
    (*itemFree)(a);
}

int main()
{
    init();
    LIST *test = ListCreate();
    int b = 5;
    // Test driver
    ad(b, print);
    printf("List count: %d\n", ListCount(test));

    return 0;
}