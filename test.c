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
NODE *FindNewListHead()
{
    NODE *newListHead = freeListHead;
    newListHead = NULL;
    freeListHead = freeListHead->next;
    return newListHead;
}

// Find new list Node
NODE *FindNewListNode()
{
    NODE *newListNode = freeListNode;
    freeListNode = freeListNode->next;
    return newListNode;
}

void FreeNodeFromList(NODE *nodeElement)
{
    nodeElement->item = NULL;
    nodeElement->prev = NULL;
    nodeElement->next = freeListNode;
    freeListNode = nodeElement;
}

void FreeHeadFromList(NODE *headElement)
{
    headElement->item = NULL;
    headElement > prev = NULL;
    headElement->next = freeListNode;
    freeListNode = headElement;
}

_Bool isValid(LIST *list)
{
    return ((list->current.isBeforeFirstItem) || (list->current.isBeyondLastItem) || (list->size == 0)) ? 0 : 1;
}

void checkCurrentItemStatus(LIST *list)
{
    if (.current.pointer != NULL)
    {
        list->current.isValid = 1;
        list->current.isBeforeFirstItem = 0;
        list->current.isBeyondLastItem = 0;
    }
    else if (test.current.pointer->next == test.head)
    {
        list->current.isValid = 0;
        list->current.isBeforeFirstItem = 1;
        list->current.isBeyondLastItem = 0;
    }
    else if (test.current.pointer->prev == test.tail)
    {
        list->current.isValid = 0;
        list->current.isBeforeFirstItem = 0;
        list->current.isBeyondLastItem = 1;
    }
}

// List create
LIST *ListCreate()
{
    LIST newList;
    NODE *newListHead = FindNewListHead();

    if (newListHead == NULL)
    {
        return -1;
    }
    else
    {
        newList.count = 0;
        newList.head = newListHead;
        newList.head = NULL;
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
    if (list == NULL)
        return NULL;
    return list->size;
}

// List first
void *ListFirst(LIST *list)
{
    // set pointer = head
    // return head pointer
    if ((list == NULL) || (list->size == 0))
        return NULL;

    list->current.pointer list->head;

    return list->head->item;
}

void *ListLast(LIST *list)
{
    // set pointer = tail
    // return tail pointer
    if ((list == NULL) || (list->size == 0))
        return NULL;

    list->current.pointer list->tail;

    return list->tail->item;
}

void *ListNext(LIST *list)
{
    // if (isValid)
    // {set current = current->next}
    // return current pointer
    if ((list == NULL) || (list->current.pointer == NULL) || (list->current.pointer->next == NULL))
        return NULL;

    list->current.pointer = list->current.pointer->next;
    checkCurrentItemStatus();
    return list->current.pointer;
}

void *listPrev(LIST *list)
{
    // if (isValid)
    // {set current = current->prev}
    // return current pointer
    if ((list == NULL) || (list->current.pointer == NULL) || (list->current.pointer->prev == NULL))
        return NULL;

    list->current.pointer = list->current.pointer->next;
    checkCurrentItemStatus();
    return list->current.pointer->item;
}

void *ListCurr(LIST *list)
{
    if ((list == NULL) || (list->current.pointer == NULL) || (!isValid(list)))
        list->current.pointer->item;

    return list->current.pointer->item
}

// List add
int ListAdd(LIST *list, void *item)
{
    // if (isValid)
    // {add item after the current item in the list}
    // return 0 for success and -1 for failure (out of memory)
    NODE *newListNode = FindNewListNode(list);
    NODE *temp;
    if ((!isValid(list) || (list == NULL) || (newListNode == NULL)) 
        return -1; 
    
    if (list->size == 0)
    {
        list->head = newListNode;
        list->tail = list->head;
    } else {
        temp = newListNode;
        temp->next = list->head;
        list->head->prev = temp;
        list->head = temp;
    } 

    list->count++;

    return 0;
}

// List insert
int ListInsert(LIST *list, item)
{
    // if (current item is before first item)
    // {add item before head and make head = new item}
    // else if (current item is beyond last item)
    // {add after tail and make tail = new item}
    // else
    // {add item before the current item in the list}
    // return 0 for success and -1 for failure (out of memory)

    return 0;
}

//List Append
int ListAppend(LIST *list, void *item)
{
    // add item after tail
    // current pointer = new item
    // make head = new item
    // return 0 for success and -1 for failure
    // if (isValid)
    // {add item after the current item in the list}
    // return 0 for success and -1 for failure (out of memory)
    NODE *newListNode = FindNewListNode(list);
    NODE *temp;
    if ((!isValid(list) || (list == NULL) || (newListNode == NULL)) 
        return -1; 
    
    if (list->size == 0)
    {
        list->head->item = item;
        list->head = newListNode;
        list->tail = list->head;
    } else {
        temp = newListNode;
        temp->next = list->head;
        list->head->prev = temp;
        list->head = temp;
    } 

    list->size++;

    return 0;
}

// List Prepend
int ListPrepend(list, item)
{
    // add item before head
    // current pointer = new item
    // make head = new item
    // return 0 for success and -1 for failure
    // if (isValid)
    // {add item after the current item in the list}
    // return 0 for success and -1 for failure (out of memory)
    NODE *newListNode = FindNewListNode(list);
    NODE *temp;
    if ((!isValid(list) || (list == NULL) || (newListNode == NULL)) 
        return -1; 
    
    if (list->size == 0)
    {
        list->head = newListNode;
        list->tail = list->head;
    } else {
        temp = newListNode;
        temp->next = list->head;
        list->head->prev = temp;
        list->head = temp;
    } 

    list->size++;

    return 0;
}

// List trim
void *ListTrim(list)
{
    // set temp = tail
    // set tail  = tail->prev
    // tail->next = NULL
    // temp2 = temp
    // freeNode(temp)
    // set current = tail
    // size--
    // return temp2
}

// List remove
void *ListRemove(list)
{
    // -> move to the next current pointer
    // set temp = current
    // set current = current->next
    // -> link new item with the old one
    // set temp->prev->next = current
    // set current->prev = temp->prev
    // set temp2 = temp
    // -> turn into free node
    // freeNodeFromList(temp);
    // size--
    // return temp2;
}

// List free
void ListFree(list, itemFree)
{
    // set current = tail
    // while (current != head)
    // {Trim list}
    // freeHeadFromList(head);
    // list = NULL
}

void ListConcat(list1, list2)
{
    // list1->tail->next = list2->head
    // list2->head->prev = list1->tail
    // list1->tail = list2->tail
    // list1->size += list2->size
    // ListFree(list2)
}

void *ListSearch(list, comparator, comparisionArg)
{
    // if (list == NULL) or (size = 0) or (comparator = 0) or (comparisionArg = NULL) or (!isValid(current))
    // {return NULL}
    // while (comparator(comparisionArg, current)) and current != tail
    // if (current->prev == tail)
    // {break
    // set current = current->next}
    // checkCurrentItemStatus(list)
    // return current
}

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