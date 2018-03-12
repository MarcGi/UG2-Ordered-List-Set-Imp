/* David Flatla    1234567890    AC21008 Assignment #2 */

#include "ordered_list_set.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printOLS(OrderedListSet* ols) {
	printf("  OLS:: address:%p size:%d head:%p tail:%p\n", (void*)ols, ols->size, (void*)ols->head, (void*)ols->tail);
	OLSNode* curr = ols->head;
	int i=1;
	while (curr != NULL) {
		printf("    N%d:: address:%p data:%d next:%p prev:%p\n", i, (void*)curr, curr->data, (void*)curr->next, (void*)curr->prev);
		curr = curr->next;
		i = i + 1;
	}
}

int main() {
	/* Create a list. */
	printf("Creating OrderedListSet...\n");
	OrderedListSet* ols = createOLS();
	printOLS(ols);
	printf("\n");

	/* Test out insertion (empty, at head, at tail, inbetween). */
	int insertValues[] = { 10, 5, 15, 20, 1, 3, 17, 12, 7 };
	int numInsertValues = sizeof(insertValues) / sizeof(int);
	for (int i=0; i<numInsertValues; i=i+1) {
		printf("Insert %d...\n", insertValues[i]);
		insertOLS(ols, insertValues[i]);
		printOLS(ols);
	}
	printf("\n");

	/* Test duplicate insertion (should change nothing). */
	int dupInsertValues[] = { 10, 1, 20 };
	int numDupInsertValues = sizeof(dupInsertValues) / sizeof(int);
	for (int i=0; i<numDupInsertValues; i=i+1) {
		printf("Duplicate insert %d...\n", dupInsertValues[i]);
		insertOLS(ols, dupInsertValues[i]);
		printOLS(ols);
	}
	printf("\n");

	/* Test out contains. */
	for (int i=-4; i<25; i=i+1) {
		printf("contains %d:: %s\n", i, (containsOLS(ols, i) ? "true" : "false"));
	}
	printf("\n");

	/* Test out remove. */
	int removeValues[] = { 22, 14, 4, -1, 11, 17, 9, 23, 3, -3, 20, 19, 0, 10, 5, 12, 16, 7, -4, 15, 2, 18, 8, 1, -2, 21, 13, 24, 6, 10, 7, 15, 1 };
	int numRemoveValues = sizeof(removeValues) / sizeof(int);
	for (int i=0; i<numRemoveValues; i=i+1) {
		printf("Remove %d...\n", removeValues[i]);
		removeOLS(ols, removeValues[i]);
		printOLS(ols);
	}
	printf("\n");

	/* Release memory. */
	printf("Destroying OrderedListSet...\n");
	deleteOLS(ols);
	printOLS(ols);	// illegal memory access, but wanted to check nothing changes
	printf("\n");

	return 0;
}
