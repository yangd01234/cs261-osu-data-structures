#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
    TYPE value;
    struct Link * next;
    struct Link * prev;
};

struct CircularList
{
    int size;
    struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
    list->sentinel = malloc(sizeof(struct Link));
    assert(list->sentinel != 0);


    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;
    list->sentinel->value = 0;
    list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
    struct Link *tmp = (struct Link*)malloc(sizeof(struct Link));
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->value = value;

    return tmp;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
    struct Link *tmp = createLink(value);

    tmp->next = link->next;//sets tmp link to nxt
    tmp->prev = link; //sets current to prev

    //sets new tmp location
    (tmp->next)->prev = tmp;
    (tmp->prev)->next = tmp;

    //increase list size
    list->size++;

}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
    //sets each of the before and after links to each other
    link->prev->next = link->next;
    link->next->prev = link->prev;

    free(link);
    link = NULL;
    list->size--;

}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
    struct CircularList* list = malloc(sizeof(struct CircularList));
    init(list);
    return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
    while(!circularListIsEmpty(list)){
        struct Link *tmp = list->sentinel->next;//points tmp to first link
        removeLink(list,tmp);//removes each link
    }
    free(list->sentinel);
    free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
    addLinkAfter(list,list->sentinel,value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
    //since it is a circular linked list, add to back
    addLinkAfter(list,list->sentinel->prev,value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
    return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
    return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
    removeLink(list,list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
    removeLink(list,list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
    if((list->size == 0)&&(list->sentinel->next == list->sentinel)){
        return 1;
    }
    return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
    struct Link *tmp = list->sentinel->next;

    for(int i = 0;i<list->size;i++){
        printf("%g\n",tmp->value);
        tmp = tmp->next;
    }

}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
    struct Link * current = list->sentinel;
    for(int i  = 0; i< list->size+1; i++){
        struct Link * temp = current->next;

        current->next = current->prev;
        current->prev = temp;
        current = current->next;
    }
}
