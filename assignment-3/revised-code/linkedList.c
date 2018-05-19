#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
    TYPE value;
    struct Link* next;
    struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
    int size;
    struct Link* frontSentinel;
    struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
    list->frontSentinel = malloc(sizeof(struct Link));
    assert(list->frontSentinel != 0);
    list->backSentinel = malloc(sizeof(struct Link));
    assert(list->backSentinel);
    list->frontSentinel->next = list->backSentinel;
    list->backSentinel->prev = list->frontSentinel;
    list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{

    //dummy link
    struct Link *tmp = link->prev;
    //allocates size for the new link
    struct Link *newLink = (struct Link*)malloc(sizeof(struct Link));
    link->prev = newLink;
    tmp->next = newLink;

    newLink->prev = tmp;
    newLink->next = link;


    newLink->value = value; //assign new value to newLink

    list->size++;

}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
    struct Link *tmpLink = link->prev; //sentinel
    struct Link *nextLink = link->next;//link2

    tmpLink->next = nextLink; //sentinel point to link2
    nextLink->prev = tmpLink; //link2 point to sentinel
    free(link); //free link 1 since link1 = lnk
    list->size--; //reduce the size

}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
    struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
    init(newDeque);
    return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
    while (!linkedListIsEmpty(list))
    {
        linkedListRemoveFront(list);
    }
    free(list->frontSentinel);
    free(list->backSentinel);
    free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
    addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{

    addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
    return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
    return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
    assert(!linkedListIsEmpty(list));
    removeLink(list, list->frontSentinel->next);

}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
    assert(!linkedListIsEmpty(list));
    removeLink(list, list->backSentinel->prev);

}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
    return list->size == 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
    assert(list->size > 0);
    struct Link *lp = list->frontSentinel->next;
    while (lp->next != list->backSentinel->next) {
        printf("%d\n",lp->value);
        lp = lp->next;
    }
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
    linkedListAddFront(list,value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
    assert(list->size > 0);
    struct Link * lp = list->frontSentinel;
    while (lp = lp->next) {
        if (lp->value == value)
            return 1;
    }
    return 0;

}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
    assert(list->size > 0);
    struct Link * lp = list->frontSentinel->next;
    while (lp != list->backSentinel->next) {
        if (lp->value == value) {//if it finds the value
            lp->prev->next = lp->next;
            lp->next->prev = lp->prev;
            free(lp);
            list->size--;
            return;
        }
        lp = lp->next;
    }
}
