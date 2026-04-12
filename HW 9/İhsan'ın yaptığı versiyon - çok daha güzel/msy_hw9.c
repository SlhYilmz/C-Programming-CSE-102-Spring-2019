#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person{
	char name[20];
	char surname[20];
	char musical_work[50];
	int age;
	struct person *next;
} *top;

void print_stack()
{
	struct person* temp = (struct person*) malloc (sizeof(struct person));
	temp = top;
	
	if(temp==NULL)
	{
		printf("There is no more people left!\n\n");
	}
	else
	{
		while(temp != NULL)
		{
			printf("\nName: %s\n", temp->name);
			printf("Surname: %s\n", temp->surname);
			printf("Creation: %s\n", temp->musical_work);
			printf("Age: %d\n", temp->age);
			temp=temp->next;
		}	
	}
}

struct person * fillPerson(char name[], char surname[], char creation[], int age)
{
	struct person* kisi = (struct person*) malloc (sizeof(struct person));
	strcpy(kisi->name, name);
	strcpy(kisi->surname, surname);
	strcpy(kisi->musical_work, creation);
	kisi->age = age;
	return kisi;
}

void addNode (char name[], char surname[], char creation[], int age)
{
	struct person* kisi = fillPerson(name, surname, creation, age);	
	kisi->next = top;
	top=kisi;
}

void deleteNode ()
{
	struct person * toDelete = top; 
	if(top==NULL)
		printf("There is no element to pop! \n");
	else
	{
		top = top->next;
	}
	free(toDelete);
}

int isEmpty() 
{ 
    if (top == NULL) 
        return 1; 
    return 0;
}

struct person * pop()
{
	struct person * temp = fillPerson(top->name, top->surname, top->musical_work, top->age);	
	deleteNode();
	return temp;
}

int ageComparator(const void *p, const void *q)  
{ 
   return ((struct person *)p)->age < ((struct person *)q)->age; 
}

int nameComparator(const void *p, const void *q)
{
	 return strcmp(((struct person *)p)->name,((struct person *)q)->name) < 0;
}
int sort(int (*comparator)(const void*,const void*))
{
	struct person* temp_stack = NULL;
	struct person* current = NULL;
	if(top == NULL){
		printf("Stack is empty. Can't sort.");
	}
	else {		
		while(!isEmpty())
		{
			current = pop();
			while(temp_stack != NULL &&  comparator(temp_stack, current))
			{
				addNode(temp_stack->name, temp_stack->surname, temp_stack->musical_work, temp_stack->age);	
				temp_stack = temp_stack->next;
			}
			current->next = temp_stack;
			temp_stack = current;
		}
		top = temp_stack;
	}
}

void sort_alphabetically ()
{
	sort(&nameComparator);
}

void sort_increasingly ()
{
	sort(&ageComparator);
}



void menu()
{
	int choice=-1, check=1, value=-1;
	
	char name[20];
	char surname[20];
	char musical_work[50];
	int age;
	
	top=NULL;
	
	while(check)
	{
		printf("\n*****MENU*****\n");
		printf("1 - Push\n");
		printf("2 - Pop\n");
		printf("3 - Sort alphabetically\n");
		printf("4 - Sort age in increasing order\n");
		printf("5 - Exit menu\n");
		printf("**************\n");
		
		while(choice<1||choice>6)
		{
			printf("Choice: ");
			scanf("%d",&choice);
		}
		switch (choice)
		{
			case 1:{
				printf("Name: ");
				scanf(" %[^\n]s", name);
				printf("Surname: ");
				scanf(" %[^\n]s", surname);
				printf("Creation: ");
				scanf(" %[^\n]s", musical_work);
				printf("Age: ");
				scanf("%d", &age);
				
				addNode(name, surname, musical_work, age);
				print_stack();
				printf("Pushing completed!\n");	
				break;
			}
				
			case 2:{
				deleteNode();
				print_stack();
				break;
			}
				
			case 3:{
				sort_alphabetically();
				print_stack();
				break;
			}
			
			case 4:{
				sort_increasingly();
				print_stack();
				break;
			}
			case 5:{
				free_all();
				check = 0;
				break;
			}	
		}
		choice=-1;
	}
}

void free_all(){
	struct person* temp;
	
	while(top!=NULL){
		temp=top;
		top=top->next;
		free(temp);
		
	}
	
}
int main()
{
	menu();
	return 0;
}

