#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
	
	#define PI 3
	
	#define SQUARE 1
	#define RECTANGULAR 2
	#define CIRCULAR 3
	
	#define RED 0
	#define YELLOW 1
	#define BLUE 2
	#define BLACK 3
	#define WHITE 4

double CreateBody (int shape); /*gets the needed integer informations for the selected shapes.*/
int SetColor (int color);	/*returns an integer to ShowPokemon function the select the color.*/
double LoadMoves (int shape, double body_size);	/*Calculates the perimeter or the circumference of the selected shape.*/
int SetAttackPower (int lower_bound, int upper_bound); /*This function generates a random number by checking the time.*/
void ShowPokemon (int shape, double body_size, int color, double move_length, int attack_power); /*Prints the information about the Pokemon*/

/*These two functions are written to make the code look better and more readible. They are called inside a function.*/
void ColorPrinter (int color);
void ShapePrinter (int shape, double body_size);


int main (){
	
	int shape, color, attack_power;
	double size_of_body, move_length;
	
		shape = RECTANGULAR; /* SQUARE; // CIRCULAR; //      Pick one of them*/
		size_of_body = CreateBody (shape);		/*returns the area*/
		color = 798;
		color = SetColor(color);
		move_length = LoadMoves(shape, size_of_body);	/*returns the perimeter*/
		attack_power = SetAttackPower (0, 150);
		ShowPokemon(shape, size_of_body, color, move_length, attack_power);
		
return 0;		
}

/*gets the needed integer informations for the selected shapes.*/
double CreateBody (int shape){
	
	int rectSide1, rectSide2, side;
	int radius;
	double area;
		
	if (shape == SQUARE){
		
	/*	printf("Pre-selected shape: Square\n");	 */		/*This is for letting the user which shape he has chosen from main, can be opened and disabled without any errors.*/
		printf("Write the length of one of the sides: ");
		scanf("%d", &side);
		
		printf("\n");
		
		area = side * side;
	}
	
	else if(shape == RECTANGULAR){
		
	/*	printf("Pre-selected shape: Rectangle\n");	*/	/*This is for letting the user which shape he has chosen from main, can be opened and disabled without any errors.*/
		printf("Write the length of the first side: ");
		scanf("%d", &rectSide1);
	
		printf("Write the length of the second side: ");
		scanf("%d", &rectSide2);
		
		printf("\n");
		
		area = rectSide1 * rectSide2;
	}
	
	else if (shape == CIRCULAR){
		
	/*	printf("Pre-selected shape: Circle\n");	*/	/*This is for letting the user which shape he has chosen from main, can be opened and disabled without any errors.*/
		printf("Write the radius of the circle: ");
		scanf("%d", &radius);
		
		printf("\n");
		
		area = PI * radius * radius;
	}
	
	return area;	
}

/*returns an integer to ShowPokemon function the select the color.*/
int SetColor (int color){
	
	if (color>1000)
		return 1;
	else	
		return (color % 5);
}

/*This function calculates the perimeter or the circumference of the selected shape.*/
double LoadMoves (int shape, double body_size){
	
	double move;
	
		if (shape == SQUARE){
			move = sqrt(body_size) *4;
		}
		else if (shape == RECTANGULAR){
			move = ( (body_size /5) + 5)*2;			/* We used this mathematical formula, because it is known that one of the sides will always be 5.*/
													/* This would NOT give the correct result, if user enters something else to one of the sides rather than 5.*/
		}
		else if (shape == CIRCULAR){
			move =  sqrt(body_size / PI) * 2 * PI;
		}
		
	return move;	
}

/*This function generates a random number by checking the time.*/
int SetAttackPower (int lower_bound, int upper_bound){
	
	int num;
	
	srand(time(NULL));
    num = ( rand() % (upper_bound - lower_bound + 1) ) + lower_bound;
    
    return num;
        
}

//Prints the information about the Pokemon
void ShowPokemon (int shape, double body_size, int color, double move_length, int attack_power){

//	To not make this function crowded, I made some other functions to print the shape and colors.
//	They are below this function.

	ShapePrinter(shape, body_size);			//Prints the shape and the name of it.
	printf("Size: %.0f\n", body_size);		//Prints the area of the shape. Even though return is double, result will never be double under these circumstances. So I put ".0"lf. 
	ColorPrinter(color);					//Prints the color
	printf("Move: %.0f\n", move_length);	//Prints the perimeter (or the circumference). Even though return is double, result will never be double under these circumstances. So I put ".0"lf. 
	printf("Attack Power: %d\n", attack_power);	//Generates a random number and prints it.
}

//Functions below this line are used in ShowPokemon function.
void ColorPrinter (int color){
	if(color == RED){
		printf("Color: Red\n");
	}
	else if(color == YELLOW){
		printf("Color: Yellow\n");
	}
	else if(color == BLUE){
		printf("Color: Blue\n");
	}
	else if(color == BLACK){
		printf("Color: Black\n");
	}
	else if(color == WHITE){
		printf("Color: White\n");
	}
}

void ShapePrinter(int shape, double body_size){
	
	int i, j;
	
	if(shape== RECTANGULAR ){
		
		for(i=0 ; i< 5 ; i++){	
			for(j=0 ; j< (body_size /5) ; j++){	
				printf("X");	
			}
			printf("\n");
		}
		printf("\n");
		
		printf("Name: Rectangular Pokemon\n" );
	}
	
	else if(shape== SQUARE){
		
		for(i=0 ; i<sqrt(body_size) ; i++){	
			for(j=0 ; j<sqrt(body_size) ; j++){	
				printf("X ");	
			}
			printf("\n");
		}
		printf("\n");
	
		printf("Name: Square Pokemon\n" );
	}	
	else if(shape == CIRCULAR){
		
		
		printf("Name: Circular Pokemon\n");
	}	
}
