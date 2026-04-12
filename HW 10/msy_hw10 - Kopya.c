#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

void fill_stack( stack ** stack_, int data);
void fill_queue (queue ** queue_, int data);
void fill_bst(bst ** bst_, int data);
void fill_structures(stack ** stack_, queue ** queue_, bst ** bst_, int data[20]);
void PrintInOrderBST (bst * bst_);
void PrintStackOrdered( stack * stack_);
void ordered_print(stack * stack_, queue * queue_, bst * bst_);
void search(stack * stack_, queue * queue_, bst * bst_, int val_to_search);
void special_traverse(stack * stack_, queue * queue_, bst * bst_);

int main()
{ 	int data[20]={5, 2, 7, 8, 11, 3, 21, 7, 6, 15, 19, 35, 24, 1, 8, 12, 17, 8, 23, 4}; 
	bst * bst_; 
	queue * queue_; 
	stack * stack_; 
	fill_structures(&stack_, &queue_, &bst_, data); 
	ordered_print(stack_, queue_, bst_); 
	//search(stack_, queue_, bst, 5); 
//	special_traverse(stack_, queue_, bst_); 
	return 0;
}


void fill_stack( stack ** stack_, int data)
{
	stack * temp = (stack*)malloc(sizeof(stack));
	
	temp->data = data;
	temp->next = NULL;
	
	temp->next = (*stack_);
	(*stack_) = temp;

}

void fill_queue (queue ** queue_, int data)
{
	queue * temp = (queue*)malloc(sizeof(queue));
	queue * qp;
	
	temp->data = data;
	temp->next = NULL;

	if((*queue_) == NULL){
		
		(*queue_) = temp;
	}
	else{
		qp = (*queue_);
		while(qp->next !=NULL){
			qp=qp->next;
		}
		qp->next = temp;
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
	*stack_ = NULL;
	*queue_ = NULL;
	*bst_ = NULL;

	for(i=0 ; i<20 ; i++)
		fill_stack(stack_, data[i]);
		
	for(i=0 ; i<20 ; i++)
		fill_queue (queue_, data[i]);
	
	for(i=0 ; i<20 ; i++)
		fill_bst(bst_ , data[i]);
	
	
}

void ordered_print(stack * stack_, queue * queue_, bst * bst_)
{
	int i;
	
	stack * tempStack = stack_;
	queue * tempQueue = queue_;
	bst * tempBst = bst_;
	/*
	while(tempStack !=NULL)
	{
		printf("%d ", tempStack->data);
		tempStack= tempStack->next;
	}
	
	
	printf("\n");
	tempStack=stack_;*/
	
	PrintStackQueueOrdered(tempStack);
	
	printf("\n");
	
	PrintStackQueueOrdered((stack*)tempQueue);
	
	printf("\n");
/*	while(tempQueue !=NULL)
	{
		printf("%d ", tempQueue->data);
		tempQueue= tempQueue->next;
	}
	printf("\n");
	tempQueue = queue_;
	*/
	
	
	
	PrintInOrderBST(tempBst);
	
}
void PrintInOrderBST (bst * bst_)
{
	if(bst_==NULL) return;
	
	PrintInOrderBST(bst_->right);
	printf("%d ", bst_->data);
	PrintInOrderBST(bst_->left);
	
}


void PrintStackQueueOrdered( stack * stack_)
{
	int i=0, j=0;
	int array[20], tempArray;
	int size = 20;
	stack * tempStack = stack_;
	
	while(tempStack !=NULL){
	
		array[i]=tempStack->data;
		tempStack=tempStack->next;
		++i;
	}
	
	for (i = 0; i < size; i++){
		for (j = i + 1; j < size; j++){
			if(array[i] < array[j]){
				tempArray = array[i];
				array[i] = array[j];
				array[j] = tempArray;
			}
		}
	}
	
	for(i=0 ; i<size ; i++){
		printf("%d ", array[i]);
	}
}

    
/*
void search(stack * stack_, queue * queue_, bst * bst_, int val_to_search)
{

}

void special_traverse(stack * stack_, queue * queue_, bst * bst_)
{
	
}*/
