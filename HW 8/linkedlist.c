#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct node{
	
	int name;
	struct node * next;
	
}node;


node * something (int number) {
		
	int i=0;
	node *head =NULL;
	node *p =NULL;
	node *temp =NULL;
	
	for(i=0 ; i<number; i++){
		temp= (node*)malloc(sizeof(node));
		
		printf("write number: ");
		scanf("%d", &(temp->name));
		
		temp->next=NULL;
		
		if(head==NULL){
			head=temp;
		}
		else{
			p=head;
			
			while(p->next!=NULL){
				p=p->next;
			}
			
			p->next=temp;
		}
	}
	
	return head;
	
	
}


void PrintFunction (node *head){
	
	int i;
	
	node *iteration;
	
	iteration = head;
	
	while(iteration->next!=NULL){
		printf("%d ", iteration->name);
		iteration=iteration->next;
	}
	printf("%d ", iteration->name);
}
int main() {
	
	int num;
	
	node * head = NULL;
	
//	head = (node*)malloc(sizeof(node));
	printf("write: ");
	scanf("%d", &num);
	
	
	head = something (num);
	PrintFunction(head);
	
	return 0;
}


