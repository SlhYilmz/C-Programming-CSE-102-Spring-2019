#include <stdio.h>
#include <stdlib.h>
#define clear() printf("\033[H\033[J") 	/* Cleaning The Terminal */
struct stack{
	int value;
	struct stack* next;
};
void menu();
void print_stack(struct stack* initial);
void push(struct stack** initial,int value);
void pop(struct stack** initial);
int main()
{
	menu();
	return 0;
}
void menu()
{
	int choice=-1,check=1,value=-1;

	struct stack* templist=malloc(sizeof(struct stack));
	struct stack* list=malloc(sizeof(struct stack));

	list->next=NULL;

	templist=list;

	while(check)
	{
		printf("\n(1) -> Print Queue\n");
		printf("(2) -> Enqueu\n");
		printf("(3) -> Denqueu\n\n");
		while(choice<1||choice>3)
		{
			printf("Choice : ");
			scanf("%d",&choice);
		}
		switch (choice)
		{
			case 1:
			print_stack(templist);
			break;
			
			case 2:
				printf("Value : ");
				scanf("%d",&value);
				push(&list,value);
			break;
			
			case 3:
			pop(&templist);
			break;
		}
		choice=-1;
	}
}
void push(struct stack** initial,int value)
{
	(*initial)->value=value;
	(*initial)->next=malloc(sizeof(struct stack));

	(*initial)=(*initial)->next;
	(*initial)->next=NULL;
	printf("Pushing complated !\n\n");
}
void pop(struct stack** initial)
{
	if((*initial)==NULL)
		printf("There is no element to pop ! \n");
	else
	{
		(*initial)=(*initial)->next;
	}
}
void print_stack(struct stack* initial)
{
	if(initial==NULL)
		printf("There is no member ! \n\n");
	else
	{
		while(initial->next!=NULL)
		{
			printf("%d ",initial->value);
			initial=initial->next;
		}
	}
}
