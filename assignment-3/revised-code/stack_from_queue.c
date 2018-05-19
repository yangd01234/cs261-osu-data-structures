

/*
 * This is the file in which you'll write the functions required to implement
 * a stack using two queues.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name: Derek Yang
 * Email: yangde@oregonstate.edu
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

# ifndef TYPE
# define TYPE int
# define TYPE_SIZE sizeof(int)
# endif
struct link {
    TYPE value;
    struct link * next;
};

struct linkedListStack {
    struct link *firstLink;
};

struct listQueue {
    struct link *firstLink;
    struct link *lastLink;
};

struct doubleStack{
    struct listQueue *queueOne;
    struct listQueue *queueTwo;
};


void linkedListStackInit (struct linkedListStack * s)
{ s->firstLink = 0; };

TYPE linkedListStackTop (struct listQueue *q) {
    assert(q->firstLink);

    assert(!listQueueIsEmpty(q));

    struct link *tmp = q->firstLink;

    while(tmp->next != NULL){
        tmp = tmp->next;
    }

    return tmp->value;
}


void listQueueInit (struct listQueue *q) {
    struct link *lnk = (struct link *) malloc(sizeof(struct link));
    assert(lnk != 0); /* lnk is the sentinel */
    lnk->next = 0;
    q->firstLink = q->lastLink = lnk;
}

int listQueueIsEmpty (struct listQueue *q) {
    return (q->firstLink == q->lastLink);
}

int linkedListStackIsEmpty (struct doubleStack *s) {
    return listQueueIsEmpty(s->queueOne);
}

void listQueueAddBack (struct listQueue *q, TYPE e) {

    struct link *lnk = (struct link*) malloc(sizeof(struct link));
    assert (lnk !=0);
    lnk->next = 0;
    lnk->value = e;
    q->lastLink->next = lnk;
    q->lastLink = lnk;
}


TYPE listQueueFront (struct listQueue *q) {
    assert(!listQueueIsEmpty(q));
    /*return the value from the link that is pointed to by the sentinel*/
    return q->firstLink->next->value;
}


void listQueueRemoveFront (struct listQueue *q) {
    assert(q->firstLink != q->lastLink);

    struct link* tmp = q->firstLink->next;

    if(q->firstLink->next == q->lastLink){//if the first link points to an element
        q->lastLink = q->firstLink;
        q->firstLink->next = NULL;
    }else{//otherwise if there is more than one element, point to firstLink->element->next
        q->firstLink->next = q->firstLink->next->next;
    }

    //free tmp
    free(tmp);
    tmp = NULL;

}
void linkedListStackPop (struct doubleStack *s) {

    assert(!linkedListStackIsEmpty(s));

    struct listQueue *tmp = s->queueOne;

    //since we have two queues, we need to move the values from one queue to another to mimic the behavior of a stack
    while (s->queueOne->firstLink->next->next != NULL) {
        listQueueAddBack(s->queueTwo, s->queueOne->firstLink->next->value);
        listQueueRemoveFront(s->queueOne);
    }
    listQueueRemoveFront(s->queueOne);

    s->queueOne = s->queueTwo;
    //free(s->queueTwo);
    s->queueTwo = tmp;
}


void linkedListStackPush (struct doubleStack *s, TYPE d) {
    if(listQueueIsEmpty(s->queueOne)){
        //if the list is empty, initialize and add queueOne
        s->queueOne = (struct listQueue*)malloc(sizeof(struct listQueue));
        listQueueInit(s->queueOne);
    }
    //if not empty, add to the back of queueOne
    listQueueAddBack(s->queueOne,d);
}

void printQueue(struct listQueue *q){
    assert(!listQueueIsEmpty(q));

    struct link *tmp = q->firstLink;

    while(tmp->next != NULL){
        printf("%d\n",tmp->next->value);
        tmp = tmp->next;
    }
}

void linkedListStackFree (struct linkedListStack *s) {
    while (!linkedListStackIsEmpty(s)){
        linkedListStackPop(s);
    }
    free(s);
}
int main() {

    //Make the stack and queues
    struct doubleStack  *s = (struct doubleStack* ) malloc(sizeof(struct doubleStack));
    s->queueOne = (struct listQueue *) malloc(sizeof(struct listQueue));
    s->queueTwo = (struct listQueue *) malloc(sizeof(struct listQueue));

    listQueueInit(s->queueOne);
    listQueueInit(s->queueTwo);

    //testing push
    printf("Testing Push: \n");
    linkedListStackPush(s,5);
    linkedListStackPush(s,4);
    linkedListStackPush(s,3);
    linkedListStackPush(s,2);
    linkedListStackPush(s,1);
    printQueue(s->queueOne);

    //testing pop
    printf("Testing Pop: \n");
    linkedListStackPop(s);
    linkedListStackPop(s);
    printQueue(s->queueOne);

    //testing top, note that in this case top is the top of a stack
    printf("Getting Top: \n");
    printf("%d\n",linkedListStackTop(s->queueOne));

    linkedListStackFree(s);
    return 0;
}