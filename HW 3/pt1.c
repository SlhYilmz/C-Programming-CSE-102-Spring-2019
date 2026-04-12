#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void calculator_menu(){
		printf("***** Simple Calculator *****\n");
		printf("Addition \t+\n");
		printf("Substraction \t-\n");
		printf("Multiplication \t*\n");
		printf("Division \t/\n");
		printf("Power\t\t**\n");
		printf("Modulo\t\t %% \n\n");
		printf("For exit, press 'E' or 'e' two times. \n");
		
		printf("\n");
		
		printf("An example run of the program follows: \n");
		printf("+ 10 2\n");
		printf("12\n");
		printf("/ 12 2\n");
		printf("6\n");

		printf("\n");		
}



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

int doit  (int function(int no1, int no2), int first_number, int second_number){
	return function(first_number, second_number);
} 

void calcutor_functions(){
	char operation[2];
	int result;
	int number1, number2;

	do{
		
		
		scanf("%s", &operation );
		scanf("%d %d", &number1, &number2);
		
		if (strlen(operation)==2){
			
			result=doit (power, number1, number2);
			printf("%d", result);
		}
		else{
							
			if (operation[0]=='+')		result=doit (add, number1, number2);
			else if (operation[0]=='-')	result=doit (sub, number1, number2);
			else if (operation[0]=='*')	result=doit (multi, number1, number2);
			else if (operation[0]=='/')	result=doit (divi, number1, number2);
			else if (operation[0]=='%')	result=doit (mod, number1, number2);
			else if (operation[0]== 'e' || operation[0]== 'E') break;
			
			printf("%d", result);
		}
	}while(operation[0]!= 'e' || operation[0] != 'E');
			
	printf("Exiting");
	
}

int main(){
	calculator_menu();
	calcutor_functions();
return 0;
}
