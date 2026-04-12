#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20 

typedef struct stack{
	int data;
	struct stack * next;
}stack;

typedef struct queue{
	int data;
	struct queue * next;
}queue;

typedef struct bst{
	int data;
	struct bst * right;
	struct bst * left;
}bst;

/*I created the first three extra funcitons, which will make the fill_stuctures funciton tidier.*/
void fill_stack (stack ** stack_, int data);
void fill_queue (queue ** queue_, int data);
void fill_bst (bst ** bst_, int data);
void fill_structures (stack ** stack_, queue ** queue_, bst ** bst_, int data[20]);

void PrintInOrderBST (bst * bst_);
void PrintStackQueueOrdered (stack * stack_);
void ordered_print (stack * stack_, queue * queue_, bst * bst_);

void search(stack * stack_, queue * queue_, bst * bst_, int val_to_search);
void special_traverse(stack * stack_, queue * queue_, bst * bst_);

int main()
{
	int data[20]={5, 2, 7, 8, 11, 3, 21, 7, 6, 15, 19, 35, 24, 1, 8, 12, 17, 8, 23, 4};		/*instead of using int data[20], it would be better to use int data[MAX_SIZE] */
	bst * bst_; 
	queue * queue_; 
	stack * stack_; 
	fill_structures(&stack_, &queue_, &bst_, data); 
	ordered_print(stack_, queue_, bst_); 
/*	search(stack_, queue_, bst, 5); */ 				/* I couldn't implement these functions.*/
/*	special_traverse(stack_, queue_, bst_);	*/		/* I couldn't implement these functions.*/
	return 0;
}


void fill_stack( stack ** stack_, int data)
{
	stack * temp = (stack*)malloc(sizeof(stack));	/* Allocates memory for our temporary stack, so we wont lose our original one. */
	
	temp->data = data;	
	temp->next = NULL;
	
	temp->next = (*stack_);
	(*stack_) = temp;		/* Our temporary stack which we did the process with, is now our original stack.*/

}

void fill_queue (queue ** queue_, int data)
{
	queue * temp = (queue*)malloc(sizeof(queue));
	queue * queuePointer;
	
	temp->data = data;
	temp->next = NULL;

	if( (*queue_) == NULL){
		
		(*queue_) = temp;
	}
	else{
		queuePointer = (*queue_);
		
		while(queuePointer->next != NULL){
			queuePointer = queuePointer->next;
		}
		queuePointer->next = temp;
	}
}

void fill_bst(bst ** bst_, int data)
{
	bst * temp = (bst*)malloc(sizeof(bst));
	
	if( (*bst_) == NULL){

		temp->data = data;
		(*bst_) = temp;
		(*bst_)->right = NULL;
		(*bst_)->left = NULL;
		
	}
	else{
		if(data > (*bst_)->data)
			fill_bst( &((*bst_)->right), data);
		else
			fill_bst( &((*bst_)->left), data);
	}
}

void fill_structures(stack ** stack_, queue ** queue_, bst ** bst_, int data[20])
{
	int i=0;
	*stack_ = NULL;		/* I null'd the structures, so that it wont try to reach the junk values, if they exist. Otherwise there is a very high potential program will not work.*/
	*queue_ = NULL;
	*bst_ = NULL;
	
	clock_t startStack = clock();
		for(i=0 ; i<MAX_SIZE ; i++){
			fill_stack(stack_, data[i]);
		}
	clock_t endStack = clock();
	float secondsStack = (float)(endStack - startStack) / CLOCKS_PER_SEC;	
	
	clock_t startQueue = clock();
		for(i=0 ; i<MAX_SIZE ; i++){
			fill_queue (queue_, data[i]);
		}
	clock_t endQueue = clock();
	float secondsQueue = (float)(endQueue - startQueue) / CLOCKS_PER_SEC;
	
	clock_t startBST = clock();
		for(i=0 ; i<MAX_SIZE ; i++){
			fill_bst(bst_ , data[i]);
		}
	clock_t endBST = clock();
	float secondsBST = (float)(endBST - startBST) / CLOCKS_PER_SEC;
		
	printf("Structure:	STACK		QUEUE		BST\n");
	printf("Fill Time:	%.3lf		%.3lf		%.3lf\n\n", secondsStack, secondsQueue, secondsBST);
}

void ordered_print(stack * stack_, queue * queue_, bst * bst_)
{
	stack * tempStack = stack_;
	queue * tempQueue = queue_;
	bst * tempBst = bst_;
	
	printf("Ordered Stack: ");
		clock_t startStack = clock();			/* Starts measuring the time for BST the sort and print*/
			PrintStackQueueOrdered(	tempStack);
		clock_t endStack = clock();
		float secondsStack = (float)(endStack - startStack) / CLOCKS_PER_SEC;
		
	printf("\nOrdered Queue: ");
		clock_t startQueue = clock();			/* Starts measuring the time for Queue the sort and print*/
			PrintStackQueueOrdered(	(stack*)tempQueue);		/*  I casted Queue with stack, so that I wont be needing to write another funciton.	*/
															/*	I did this, because function works whether it is queue or stack.				*/
		clock_t endQueue = clock();
		float secondsQueue = (float)(endQueue - startQueue) / CLOCKS_PER_SEC;

	printf("\nOrdered BST:   ");						
		clock_t startBST = clock();				/* Starts measuring the time for Queue the sort and print*/
			PrintInOrderBST(tempBst);
		clock_t endBST = clock();
		
		float secondsBST = (float)(endBST - startBST) / CLOCKS_PER_SEC;
		
		printf("\n\n");
		printf("Structure:	STACK		QUEUE		BST\n");
		printf("Sort. Time:	%.3lf		%.3lf		%.3lf\n", secondsStack, secondsQueue, secondsBST);
	
}
void PrintInOrderBST (bst * bst_)
{
	/*	This is a pretty known algorithm for printing a binary tree.*/
	/*	It traverses the tree until there is are more nodes left */
	/*	The recursive function goes as far as it go in the direction right, and when there is no more right it will print it. After that it will try to go to the left once and recur again.*/
		
	if(bst_==NULL)
		return;
	else {
		PrintInOrderBST(bst_->right);
		printf("%d ", bst_->data);
		PrintInOrderBST(bst_->left);
	}
	
}

void PrintStackQueueOrdered (stack * stack_)
{
	/* I am getting all the values from the stack, or the queue for that matter, and copy them to an array. */
	/* After which I bubble sort the array that I put the values in and then print them. */
	/* Since I am using an array to sort the data, I don't need to know whether if the data structure is a queue or a stack. They will act as if they are the the same. */
	/* Due to that mindset, I used stack as the names but it can also be queue. */
	
	int i=0, j=0;
	int array[MAX_SIZE], tempArray;
	
	stack * tempStack = stack_;		/* I create a temporary stack so that if I need it later, I can access the original one.*/
	
	while(tempStack !=NULL){		/* Traverse until the stack is null, while copying the data of each node to the array.*/
	
		array[i]=tempStack->data;
		tempStack=tempStack->next;
		++i;
	}
	
	for (i = 0; i < MAX_SIZE; i++){			/* Bubble sort the array.*/
		for (j = i + 1; j < MAX_SIZE; j++){
			if(array[i] < array[j]){
				tempArray = array[i];
				array[i] = array[j];
				array[j] = tempArray;
			}
		}
	}

	for(i=0 ; i<MAX_SIZE ; i++){
		printf("%d ", array[i]);		/*Print the array.*/
	}
	
}

/*

void search(stack * stack_, queue * queue_, bst * bst_, int val_to_search)
{

}

void special_traverse(stack * stack_, queue * queue_, bst * bst_)
{
	
}

*/
