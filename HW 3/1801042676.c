#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void menu ();		//menu for choosing.

void draw_baklava_shape ();		//Only draws the shape.

int take_grades ( int [] );		//This function gets both lab and homeworks grades.
int take_exam_grades ( int [] );
double calculate_homework( int [] );
double calculate_lab ( int [] );
double calculate_all ( int, int[], int );

void calculator_menu ();				//Prints how the calculator works.
int add (int number1,  int number2);
int sub (int number1,  int number2);
int multi (int number1,  int number2);
int divi (int number1,  int number2);
int power (int number1,  int number2);
int mod (int number1,  int number2);
void calculator_functions ();			//The main calculator program


int main(){

	menu();
	
return 0;
}

void menu (){
	
	int choice;
	int i;
	int lab_grades[10], hw_grades[10], exams[2]; 
	double labAverage=0, hwAverage=0;
	
	do{	
		printf("\n***** MENU *****\n");
		printf("1. Calculator\n");
		printf("2. Grades\n");
		printf("3. Draw baklava shape\n");
		printf("4. Exit\n");
			
		printf("\nChoice: ");
		scanf("%d", &choice);
			
		switch(choice){
			case 1:{
				calculator_menu();
				calculator_functions();		
				break;
			}
				
			case 2:{
				printf("Enter lab grades of the student: \n");
				take_grades (lab_grades);
				
				printf("\n");
				
				printf("Enter hw grades of the student: \n");
				take_grades (hw_grades);
				
				printf("\n");
				
				printf("Enter exam grades of the student: \n");
				take_exam_grades(exams);
				
				labAverage = calculate_lab(lab_grades);
				hwAverage = calculate_homework(hw_grades);
				
				printf("\n");
				
				printf("Lab Average: %.1lf , Homework Average: %.1lf \n\n", labAverage, hwAverage);
				printf("Weighted Average: %.1lf\n", calculate_all (labAverage, exams, hwAverage) );
				break;
			}
	
			case 3:{
				draw_baklava_shape();
				break;
			}
			
			case 4:{
				break;
				
			}
			default:{
				printf("Unsupported value. Try again.\n");
				break;
			}
		}	
		
	}while(choice!=4);
		
}

void draw_baklava_shape(){
	int height;
	int i, j;
	
	printf("\nWrite the height of the shape: ");
	scanf("%d", &height);
	
	while(height==0 || height<0){
		printf("You can't draw the shape with this length value. Try again with a proper one: ");
		scanf("%d", &height);
	}
	
	if(height>0){
		printf("\n");
		for(i=1 ; i<=height ; i++){
			for(j=i; j<height ; j++){
				printf(" ");
			}
			printf("/");
			
			
			for(j=2; j<=(i*2)-1 ; j++){
				printf("*");
			}	
			printf("\\\n");
		}
		
		for(i=height ; i>=1 ; i--){
			for(j=i; j<height ; j++){
				printf(" ");
			}
			printf("\\");
		
			for(j=2; j<=(i*2)-1 ; j++){
				printf("*");
			}	
			printf("/\n");
		}	
	}	
}

//This function fills the array with lab or homework grades.
int take_grades ( int lab_hw_grades[]){
	
	int i, grade;
	
	for(i=0 ; i<10 ; i++){
		printf("%d. grade: ",i+1);
		scanf("%d",&lab_hw_grades[i]);
	}
	
	return 0;
}

//This function gets two values for midterm and final grades.
int take_exam_grades ( int exams[]){
	
	int i, midterm, final;
	
	printf("Midterm Grade: ");
	scanf("%d", &midterm);
	printf("Final Grade: ");
	scanf("%d", &final);
	
	exams[0]=midterm;
	exams[1]=final;

	return 0;
}

//This function gets the average value for homeworks, by summing the array and returning the mean.
double calculate_homework( int homeworkGradesMean[]){
	
	double sum = 0;
	int i=0;
	
    for (i=0; i<10 ; i++){
    	sum += homeworkGradesMean[i];
	}

	return (sum/10);
	
}

//This function gets the average value for labs, by summing the array and returning the mean.
double calculate_lab( int labGradesMean[]){
	double sum = 0;
	int i=0; 
	
    for (i=0 ; i<10 ; i++){
    	sum += labGradesMean[i];
	}
	return (sum/10);
}

//This function calculates the weighted average with given values.
double calculate_all( int labAverage, int exam[], int hwAverage){
	
	double average = 0;
	average = (double)(hwAverage*0.1 + labAverage*0.2 + exam[0]*0.3 + exam[1]*0.4);
	
	return average; 
}

//The function below only prints how the calculator works.
void calculator_menu(){
		printf("\n**** Simple Calculator ****\n");
		printf("Addition \t+\n");
		printf("Substraction \t-\n");
		printf("Multiplication \t*\n");
		printf("Division \t/\n");
		printf("Power\t\t**\n");
		printf("Modulo\t\t %% \n\n");
		printf("For exit, press 'e'. \n");
		
		printf("\n");
		
		printf("An example run of the program is as follows: \n");
		printf("+ 10 2\n");
		printf("12\n");
		printf("/ 12 2\n");
		printf("6\n");

		printf("\n");		
}


//These 6 functions below essentially do the same thing: They get the values and return the result with selected operation. 
int add (int number1,  int number2){
	return number1+number2;
}

int sub (int number1,  int number2){
	return number1-number2;
}

int multi (int number1,  int number2){
	return number1*number2;
}

int divi (int number1,  int number2){
	return number1/number2;
}

int power (int number1,  int number2){
	return pow(number1, number2);
}

int mod (int number1,  int number2){
	return number1%number2;
}

//This is for calling the functions above, in the main calculator function.
int doit  (int function(int no1, int no2), int first_number, int second_number){
	return function(first_number, second_number);
} 


void calculator_functions(){
	char operation[2];
	int result;
	int number1, number2;

	
	scanf("%s", &operation );
	
	while(operation[0]!= 'e' ){	
		
		scanf("%d %d", &number1, &number2);
		
		if (strlen(operation)==2){		//By measuring the length of the array, I can know if it is either two characters or not.
										//If it is two characters, then it must be power operation. If not, then it is only one character, which is other operations.
			result=doit (power, number1, number2);
			printf("%d", result);
			scanf("%s", &operation );
		}
		else{
			//We got the first element of the array filled with the operation. If I can look what is it, I can tell which function I am going to do. This is for exactly that.
			if (operation[0]=='+')		result=doit (add, number1, number2);
			else if (operation[0]=='-')	result=doit (sub, number1, number2);
			else if (operation[0]=='*')	result=doit (multi, number1, number2);
			else if (operation[0]=='/')	result=doit (divi, number1, number2);
			else if (operation[0]=='%')	result=doit (mod, number1, number2);
					
			printf("%d", result);
			scanf("%s", &operation );
			
		}
	}
			
	printf("Exiting from calculator...\n");
	
}
