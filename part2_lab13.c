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
	struct stack* list=NULL;

	while(check)
	{
        printf("\n(1) -> Print Stack\n");
		printf("(2) -> Push\n");
		printf("(3) -> Pop\n");
		printf("(4) -> Exit\n\n");
		while(choice<1||choice>4)
		{
			printf("Choice : ");
			scanf("%d",&choice);
		}
		clear();
		switch (choice)
		{
			case 1:
				print_stack(list);
			break;
			
			case 2:
				printf("Value : ");
				scanf("%d",&value);
				push(&list,value);
			break;
			
			case 3:
				pop(&list);
			break;

			case 4:
			check=0;
			break;
		}
		choice=-1;
	}
}
void push(struct stack** initial,int value)
{
	struct stack* temp=malloc(sizeof(struct stack));

	if((*initial)==NULL)
	{
		(*initial)=malloc(sizeof(struct stack));
		(*initial)->value=value;
		(*initial)->next=NULL;
	}
	else
	{
		printf("initial -> %d\n",(*initial)->value);
		temp->value=value;
		temp->next=(*initial);
		(*initial) = temp;
	}
	printf("----------------------------\n");
	printf("Pushing is complated !		\n");
	printf("----------------------------\n");
}
void pop(struct stack** initial)
{
	if((*initial)==NULL)
	{
		printf("----------------------------\n");
		printf("There is no element to pop !\n");
		printf("----------------------------\n");
	}
	else
	(*initial)=(*initial)->next;
}
void print_stack(struct stack* initial)
{
	printf("\nStack -> \n");
	if(initial==NULL)
	{
		printf("----------------------------\n");
		printf("There is no element to pop !\n");
		printf("----------------------------\n");
	}
	else
	{
		while(initial!=NULL)
		{
			printf("\t|  %-3d|\n",initial->value);
			initial=initial->next;
		}
		printf("\t-------\n\n");
	}
}
