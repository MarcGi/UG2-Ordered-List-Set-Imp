/* David Flatla    1234567890    AC21008 Assignment #2 */

#ifndef HEADER_ORDERED_LIST_SET
#define HEADER_ORDERED_LIST_SET

#include <stdbool.h>

/* The struct used as nodes in my ordered list set. */
typedef struct MyNode{
	int data;
	struct MyNode* next;
	struct MyNode* prev;
} OLSNode;

/* The struct used to represent my ordered list set. */
typedef struct MyOrderedListSet{
	int size;
	struct MyNode* head;
	struct MyNode* tail;
} OrderedListSet;

/* Allocate an empty ordered list set, initialize its values, and return pointer to it.
   Returns NULL if memory allocation fails. */
OrderedListSet* createOLS();

/* Add value 'v' to 'ols' at the correct ordered location.
   If 'ols' already contains' v', then do nothing. */
void insertOLS(OrderedListSet* ols, int v);

/* Report true/false whether 'ols' contains value 'v'. */
bool containsOLS(OrderedListSet* ols, int v);

/* Remove value 'v' from 'ols'. 'ols' may be empty, and 'ols' might not contain 'v'. */
void removeOLS(OrderedListSet* ols, int v);

/* Free the memory for 'ols's elements and then 'ols' itself. */
void deleteOLS(OrderedListSet* ols);

#endif
