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
	// FIXME: you must write this
	list->sentinel = (struct Link*)malloc(sizeof(struct Link)); 
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
	list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// FIXME: you must write this
	struct Link* newLink = (struct Link*)malloc(sizeof(struct Link));
	newLink->value = value;
	newLink->next = NULL;
	newLink->prev = NULL;
	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
	// STOP
	struct Link *newLink = createLink(value);

	struct Link *temp = link->next;
	link -> next = newLink;
	temp -> prev = newLink;
	newLink -> prev = link;
	newLink -> next = temp;

	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXME: you must write this
	struct Link* prev = link->prev;
	prev->next = prev->next->next;
	prev->next->prev = prev;
	free(link);
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
	// FIXME: you must write this
	while (!circularListIsEmpty(list))
	{
		circularListRemoveFront(list);
	}
	free(list->sentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
	//struct Link *newLink = createLink(value);
	addLinkAfter(list,list->sentinel,value);
	// struct Link *head = list->sentinel->next;

	// head -> prev = newLink;
	// newLink -> next = head;

	// list->sentinel->next = newLink;
	// newLink -> prev = list->sentinel;

}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
	//struct Link *newLink = createLink(value);
	addLinkAfter(list,list->sentinel->prev,value);
	// struct Link *tail = list->sentinel->prev;

	// list->sentinel->prev = newLink;
	// newLink->next = list->sentinel;

	// newLink->prev = tail;
	// tail->next = newLink;

}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != NULL);
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != NULL);
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this
	if (list->size > 0)
	{
		removeLink(list, list->sentinel->next);
	}
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this
	if (list->size > 0)
	{
		removeLink(list, list->sentinel->prev);
	}

}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// FIXME: you must write this
	if (list->size == 0)
		return 1;
	else
		return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(list->size != 0);
	struct Link* curr = list->sentinel->next;

	while(curr != list->sentinel)
	{
		printf("%g\n", curr->value);
		curr = curr->next;
	}
	

}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(list->size != 0);

	//make a new link as head
	// take last one of the list and add to that until list is empty
	// set the link as sentinal
	struct Link * curr = list->sentinel->prev;
		
	while(curr != list->sentinel)
	{
		TYPE value = curr -> value;
		// circularListRemoveFront(list);
		circularListAddBack(list,value);
		curr = curr -> prev;
	}
	
	int count = list->size;
	count = count/2;
	while (count > 0)
	{
		circularListRemoveFront(list);
		count--;
	}
}
