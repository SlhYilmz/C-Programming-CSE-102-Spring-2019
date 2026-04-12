#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.0
#define SQUARE 1
#define RECTANGULAR 2
#define CIRCULAR 3
#define RED 0
#define YELLOW 1
#define BLUE 2
#define BLACK 3
#define WHITE 4
#define COLORRANGE 5
double CreateBody (int shape);
int SetColor (int color);
double LoadMoves(int shape, double body_size);
int SetAtackPower(int lower_bound, int upper_bound);
void ShowPokemon(int shape, double body_size, int color, double move_length, int attack_power);

int main()
{
	int shape, color, attack_power;
	double size_of_body, move_length;
	shape = CIRCULAR;
	size_of_body = CreateBody (shape);
	color = 72;
	color = SetColor(color);
	move_length = LoadMoves(shape, size_of_body);
	attack_power = SetAtackPower (50, 150);
	ShowPokemon(shape, size_of_body, color, move_length, attack_power);
}
double CreateBody (int shape)
{
	double body_size;
	if (shape==CIRCULAR)
	{
		double radius=-1;
		while (radius<=0)
		{
			printf("\nPlease enter a positive number for the radius of the circle:");
			scanf("%lf",&radius);
		}
		body_size=PI*pow(radius,2);
	}
	else if (shape==RECTANGULAR)
	{
		double short_edge=-1, long_edge=-1;
		while (short_edge<=0 )
		{
			printf("\nPlease enter a positive number for short edge of the rectangle:");
			scanf("%lf",&short_edge);
		}
		while (long_edge<=0 )
		{
			printf("\nPlease enter a positive number for long edge of the rectangle:");
			scanf("%lf",&long_edge);
		}
		body_size=long_edge*short_edge;
		
	}
	else if (shape==SQUARE)
	{
		double edge=-1;
		while (edge<=0 )
		{
			printf("\nPlease enter a positive number for the edge of the square:");
			scanf("%lf",&edge);
		}
		body_size=edge*edge;
	}
	else
	{
		printf("You can't have a pokemon with this shape!\n");
		return 0;
	}
	return body_size;
}

int SetColor (int color) 
{
	if (color > 1000) return YELLOW;
	else
	{
		int revized_color=color%COLORRANGE;
		if (revized_color==RED) return RED;
		else if (revized_color==YELLOW) return YELLOW;
		else if (revized_color==BLUE) return BLUE;
		else if (revized_color==BLACK) return BLACK;
		else if (revized_color==WHITE) return WHITE;
	}
}

double LoadMoves(int shape, double body_size)
{
	double move;
	if (shape==RECTANGULAR) 
	{
		double long_edge, short_edge=5;
		long_edge=body_size/short_edge;
		move=(2*long_edge)+ (2 * short_edge);
	}
	if (shape==SQUARE) 
	{
		double edge;
		edge=sqrt(body_size);
		move=4*edge;
	}
	if (shape==CIRCULAR) 
	{
		double radius;
		radius=sqrt(body_size/PI);
		move=2*PI*radius;
	}
	return move;
}

int SetAtackPower(int lower_bound, int upper_bound)
{
	srand(time(NULL));
	int random_number = rand();
	int attack_power=(random_number % (upper_bound - lower_bound + 1)) + lower_bound;
	return attack_power;
}

void ShowPokemon(int shape, double body_size, int color, double move_length, int attack_power)
{
	int i,j;
	if (shape==CIRCULAR)
	{
		
		int radius=sqrt(body_size/PI);
		
		int range,first_line_align,i,j,head_tab_count,middle_tab_count;
		head_tab_count=radius/2;
		if (radius%2==0)
		{
			range=radius+1;
			middle_tab_count=-1;
			first_line_align=-1;
		}
		else
		{
			range=radius;
			middle_tab_count=0;
			first_line_align=0;
		}
		for (i=1;i<=range;i++)
		{
			if (i==1 || i==range)
			{
				 
				for (j=0;j<head_tab_count+first_line_align;j++)
				{
					printf("\t");
				}
				if (first_line_align==-1)
				{
					printf("    X\n");
				}else printf("X\n");
			}
			else
			{
				for (j=0;j<head_tab_count;j++)
				{
					printf("\t");			
				}
				printf("X");
				for (j=0;j<middle_tab_count;j++)
				{
					printf("\t");			
				}
				printf("X\n");

			}
			if (range/i>1)
			{
				head_tab_count--;
				middle_tab_count+=2;		
			}
			else
			{
				head_tab_count++;
				middle_tab_count-=2;	
			}
		}
		printf("\nName: Circular Pokemon\n");
	}
	else if (shape==RECTANGULAR)
	{
		int default_short_edge=5;
		int long_edge=body_size/5;
		for (i=0;i<default_short_edge;i++)
		{
			for (j=0;j<long_edge;j++)
			{
				printf("X");
			}
			printf("\n");
		}
		printf("\nName: Rectangular Pokemon\n");
	}
	else if (shape==SQUARE)
	{
		int edge=sqrt(body_size);
		for (i=0;i<edge;i++)
		{
			for (j=0;j<edge;j++)
			{
				printf("X");
			}
			printf("\n");
		}
		printf("\nName: Square Pokemon\n");
	}
	else
	{
		printf("Bu tipte bir pokemon olamaz!");
		return;
	}
	printf("Size: %.2lf\n",body_size);
	if (color == RED) printf("Color: Red\n");
	else if (color == YELLOW) printf("Color: Yellow\n");
	else if (color == BLUE) printf("Color: Blue\n");
	else if (color == BLACK) printf("Color: Black\n");
	else if (color == WHITE) printf("Color: White\n");
	else printf("You can't have a pokemon in this color!\n");
	printf("Move: %.2lf\n", move_length);
	printf("Attack Power: %d\n", attack_power);
	
	
}


