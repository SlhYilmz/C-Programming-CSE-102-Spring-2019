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


/*mandatory functions*/
void print_stack();
void addNode (char name[], char surname[], char creation[], int age);
void deleteNode ();
void sort_alphabetically();
void sort_increasingly();
void menu();

/*helper functions*/
int isEmpty();
void free_all();
struct person * fillPerson(char name[], char surname[], char creation[], int age);
struct person * pop();

int main()
{
	menu();
	return 0;
}

/*Function to print the stack. Checks if the stack is full or not. if it is not full, it continues to print it.*/
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
			printf("\nN: %s\n", temp->name);
			printf("S: %s\n", temp->surname);
			printf("C: %s\n", temp->musical_work);
			printf("A: %d\n", temp->age);
			temp=temp->next;	/*To go the other person*/
		}	
	}
}

/*This function is to make addNode tidier. If we need to add more properties to the struct, we wouldn't need to change all the code of the function.*/
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

/*Helper functions to check whether the struct is empty or not*/
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

/*Sorting alphabetically and by the ages, is essentially the same. Instead of using standart comparison tools (such as "bigger than and smaller than signs") we use string compare function from the string library.*/
/*Everything that I say for this function, is also valid for sort_increasingly function.*/
void sort_alphabetically ()
{
	struct person* temp_stack = NULL;
	struct person* current = NULL;
	
	if(top == NULL)
	{
		printf("Stack is empty. Can't sort.");
	}
	else 
	{		
		while(!isEmpty())		/*If stacks is not empty, do the below.*/
		{
			current = pop();		/*We are getting the current person's properties out of the first stack of ours.*/
			while(temp_stack != NULL &&  strcmp(((struct person *)temp_stack)->name,((struct person *)current)->name) < 0 ) /*If it succeeds our needs, we put it to the second stack.*/
			{																												/*If it doesnt, we put all the things we compared before to the original stack and get the other value. And compare it with second stack. */			
				addNode(temp_stack->name, temp_stack->surname, temp_stack->musical_work, temp_stack->age);					/*Until that other value is the thing we wanted, we do it repeatedly.*/
				temp_stack = temp_stack->next;
			}
			current->next = temp_stack;	
			temp_stack = current;
		}
		top = temp_stack;
	}
}

void sort_increasingly ()
{
	struct person* temp_stack = NULL;
	struct person* current = NULL;
	
	if(top == NULL)
	{
		printf("Stack is empty. Can't sort.");
	}
	else
	{		
		while(!isEmpty())
		{
			current = pop();
			while(temp_stack != NULL &&  ((struct person *)temp_stack)->age < ((struct person *)current)->age )
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

/*Helper function to free all the allocated area for once and for all.*/
void free_all()
{
	struct person* temp;
	
	while(top!=NULL)
	{
		temp=top;
		top=top->next;
		free(temp);
	}
}

void menu()
{
	int choice;
	char name[20];
	char surname[20];
	char musical_work[50];
	int age;
	
	top=NULL;
	
	do
	{
		printf("\n*****MENU*****\n");
		printf("1 - Add a person to the stack\n");
		printf("2 - Pop a person to the stack\n");
		printf("3 - Sort the stack alphabetically\n");
		printf("4 - Sort the stack in age increasing order\n");
		printf("5 - Exit menu\n");
		printf("**************\n");
		
		printf("Choice: ");
		scanf("%d",&choice);
		
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
			//	printf("Pushing completed!\n");	
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
				break;
			}
			default:{
				printf("Unsupported selection. Enter a proper value.\n");
				break;
			}	
		}
	}while(choice !=5);
}
