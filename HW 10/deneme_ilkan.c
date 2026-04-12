#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct stack{
	int data;
	struct stack * next;
}stack;

void reverse(stack * top);
void push(stack ** top,int data);
void printStack(stack * top);

int main()
{
	stack * top=NULL;
	int data;
	
	printf("enter data:\n");
	scanf(" %d",&data);
	
	while(data>-1){
		push(&top,data);
		scanf(" %d",&data);
	}
	
	printf("\nstack:\n");
	printStack(top);
	
	printf("\nrev stack:\n");
	reverse(top);	
	return 0;
	
}

void push(stack ** top,int data){
	stack * temp = (stack *)malloc(sizeof(stack));
	
	temp->data = data;
	
	temp->next = *top;
	(*top)= temp;
}

void printStack(stack * top){
	stack * p = top;
	
	while(p!=NULL){
		printf("%d ",p->data);
		p = p->next;
	}
}

void reverse(stack * top){
	if(top->next == NULL){
		printf("%d ",top->data);
		return;
	}
	reverse(top->next);
	printf("%d ",top->data);
}
