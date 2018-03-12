/*
Marc Giannandrea | AC21008 
ordered_list_set.c | C Source file containing all functions relevant to the OrderedListSet
*/
#include <stdio.h>
#include <stdlib.h>
#include "ordered_list_set.h"

/* search is used to find the passed value in the passed ordered list set
	and return the node with that value*/
static OLSNode* search(OrderedListSet* ols,int v){
    if(ols == NULL || ols->head == NULL){
        return NULL;   
    }
	OLSNode* curNode = ols->head;//Set curNode to head to start traversal
	while(curNode != NULL){
		if(curNode->data == v){
			return curNode;//If node is found return it.
		}else if(curNode->data > v){ //Surpassed where the node would be if it was in the set
			return NULL;
		}else{
			curNode = curNode->next;//If not traverse further
		}
	}
	return NULL;
}

/* DeteminePos is used to determine what case the passed node is in.
E.g if there is only a previous node and no next then the node must be the head*/
static char determinePos(OLSNode* nodeDet){ 
	if (nodeDet != NULL){
		if (nodeDet->prev == NULL && nodeDet->next !=NULL ){
			return 'h';	// h for Head
		}else if (nodeDet->next != NULL && nodeDet->prev !=NULL){
			return 'b'; // b for body e.g inbetween head or tail
		}else if (nodeDet->next == NULL && nodeDet->prev !=NULL){
			return 't'; // t for tail
		}else if (nodeDet->next == NULL && nodeDet->prev == NULL){
			return 'l'; // l is for last e.g last node in the set
		}
	}
	return 'e'; // Return e for error
}

/* deleteNode is used to delete a passed node from the passed ordered list set
	it will change the relevant surrounding nodes to compensate for the deletion*/
static void deleteNode(OrderedListSet* ols,OLSNode* nodeToDel){
	if(nodeToDel != NULL && ols != NULL ){
		char pos = determinePos(nodeToDel);
		switch(pos){
			case 'h'://Case for head
				ols->head=nodeToDel->next;//Set head to nodeToDel's next
				nodeToDel->next=NULL;//Set nodeToDel's next to null
				ols->head->prev=NULL;
				break;

			case 'b'://Case for body
				nodeToDel->prev->next=nodeToDel->next;//Set nodeToDel's previous's next to nodeToDel's next
				nodeToDel->next->prev=nodeToDel->prev;//Set nodeToDel's next's prev to nodeToDel's prev
				break;
			
			case 't'://Case for tail
				ols->tail=nodeToDel->prev;//Set tail to nodeToDel's prev
				nodeToDel->prev=NULL;//Set nodeToDel prev to NULL
				ols->tail->next=NULL;//Set the tail's next to NULL
			break;

			case 'l'://Case for last
				ols->head=NULL;//Set head and tail to Null as set will be empty
				ols->tail=NULL;
			break;
			
			default:
				return;
			break;
		}
		ols->size--;//Decrease set size	
		nodeToDel->data=0;//Set data to null
		free(nodeToDel);//Free the node from memory
	}
	
}

/* Allocate an empty ordered list set, initialize its values, and return pointer to it.
   Returns NULL if memory allocation fails. */
OrderedListSet* createOLS(){
	OrderedListSet* ols = malloc(sizeof(ols));

	// Check for malloc failure and initialise variables
	if(ols !=NULL){
		ols->size = 0;
		ols->head = NULL;
		ols->tail = NULL;
		return ols;
	}else{
		return NULL;
	}
}

/* Free the memory for 'ols's elements and then 'ols' itself. */
void deleteOLS(OrderedListSet* ols){
	if(ols == NULL){
		return;
	}	
	
	if(ols->size >0){ //Check if set is empty
		OLSNode* nodeToDel = ols->head; //Set the starting node to the head in order to traverse the set

		while (nodeToDel != NULL) {
			deleteNode(ols,nodeToDel);//Delete the node via the deleteNode function
			nodeToDel = ols->head;//Traverse to the next node as it will now be the head
		}
	}
	ols->size =0;//Set size to 0
	free(ols);//Free ols from memory
}

/* Add value 'v' to 'ols' at the correct ordered location.
   If 'ols' already contains' v', then do nothing. */
void insertOLS(OrderedListSet* ols, int v){
	//Error checking if set is null
	if(ols == NULL){
		return;
	}
	//If v is already in set then do not add
	if(containsOLS(ols,v)){
		return;
	}	

	OLSNode* newNode = malloc(sizeof(newNode));
	//Check for malloc failure
	if(newNode == NULL){
		return;
	}
	//Initialise newNode's fields to default
	newNode->data = v;
	newNode->next = NULL;
	newNode->prev = NULL;

	if(ols->head == NULL){
		//If head does not exist then set newNode to head and tail and increase the size of set
		ols->head = newNode;
		ols->tail = newNode;
		ols->size = ols->size + 1;
		return;
	}

	OLSNode* curNode = ols->head; //Used for traversing the set starting from the head
	while(curNode != NULL){
		
		if(v < curNode->data){ // if v is less than the node we are currently pointing at then
			if(curNode == ols->head){
				ols->head = newNode;//If the current node is head then set the head to newNode
			}else if(curNode != ols->head){
				curNode->prev->next = newNode;//Set the current nodes previous next field to newNode
			}
			newNode->prev = curNode->prev;//Set newNodes prev to curNodes prev
			newNode->next = curNode;//Set newNodes next to curNode
			curNode->prev = newNode;//Set curNodes prev to newNode
			ols->size++;//Increase size of set
			return;

		}else if(v > curNode->data){//If v is greater than the current nodes data then
			if(curNode->next == NULL){ //Check if we are at the tail
				curNode->next = newNode;//Set curNodes next to newNode
				newNode->prev = curNode;//Set newNodes prev to curNode
				ols->tail = newNode;//Set the set tail to newNode
				ols->size++;//Increase the size
				return;
			}
	
		}
		curNode = curNode->next;//Traverse to next node
	}	
}

/* Report true/false whether 'ols' contains value 'v'. */
bool containsOLS(OrderedListSet* ols, int v){

	if(ols->size ==	0 || ols == NULL){
		return false;
	}
	OLSNode* searched = search(ols,v); //Search for the node
	if(searched != NULL){//If the node does exist then return true
		return true;
	}else{
		return false; //Else return false
	}

}
/* Remove value 'v' from 'ols'. 'ols' may be empty, and 'ols' might not contain 'v'. */
void removeOLS(OrderedListSet* ols, int v){
	if(ols->size ==	0 || ols == NULL){
		return;//If ols is null or empty then do not continue
	}
	OLSNode* searched = search(ols,v);//Search for node in the set

	if (searched == NULL){
		return;
	}else{
		deleteNode(ols,searched);//Call delete node with ols and searched node passed if the node exists
	}
}
