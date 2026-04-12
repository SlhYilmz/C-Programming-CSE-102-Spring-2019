#include <stdio.h>

typedef enum block_type{start, property, tax, punish} block_type;
typedef enum player_type{noone, cap, car} player_type;


struct player{
	player_type type;		/* Holds type of the player. The player_type must be defined as enumerated type which consist of noone, cap and car values.*/
	int current_block_id;	/*Holds player location as block id.*/
	int owned_block_ids[11];	/* Holds property block ids that are owned by the user*/
	int account;			/*Holds amount of the current money of the player. */
	int turn_to_wait;		/* Holds number of turns to wait if the player got a punishment. */
	char * name;			/* Holds the name of the player. */
	
}player; 

struct block{
	int block_id;	/*Holds id of the block.*/
	char * name;	/*Holds text of the block that is shown on the top of the block*/
	int price;		/*If the block is property, holds the price of property. If the block is a tax block than holds the tax fee and if the block is punishment block, then holds the number of turns to wait.*/
	int rent;		/* Holds the default rent of a property (no house). */
	int rent_1;		/* Holds the rent of a property with one house.*/
	int rent_2;		/* Holds the rent of a property with two houses. */
	int rent_3;		/*Holds the rent of a property with three houses*/
	int house_price;	/* Holds price of building a house on the block.*/
	int house_count;	/*Holds the number of the houses on the block that are already built.*/
	struct player owner;	/*Holds the owner of the block. */
	block_type type;	/*Holds type of the block. The block_type must be defined as enumerated type which consist of start, property, tax, punish values. */
	
}block;

int roll_dice (int lower_bound, int upper_bound);
void init_the_board(struct block board[20]);
void show_board(struct block board[20],struct player player_one, struct player player_two);
void show_properties(struct block board[20]);

int main(){
	struct block board[20];
	struct player player_one;
	struct player player_two;
	
	init_the_board(board);
	show_board(board,player_one,player_two);
	show_properties(board);
	
//	gameplay(board, player_one, player_two);
	
	
	
return 0;
}

/*initializes all the board with their properties.*/
void init_the_board(struct block board[20]) {
	board[0].block_id= 0;	board[0].name= "Start";			board[0].price= 0;		board[0].rent= 0;		board[0].rent_1 = 0;		board[0].rent_2= 0;			board[0].rent_3= 0;			board[0].house_price= 0; 		board[0].type= start;
	board[1].block_id= 1;	board[1].name= "Esenyurt";		board[1].price= 1600;	board[1].rent= 800;		board[1].rent_1 = 4000;		board[1].rent_2= 9000;		board[1].rent_3= 25000;		board[1].house_price= 10000; 	board[1].type= property;
	board[2].block_id= 2;	board[2].name= "Car Park";		board[2].price= 0;		board[2].rent= 1500;	board[2].rent_1 = 0;		board[2].rent_2= 0;			board[2].rent_3= 0;			board[2].house_price= 0;		board[2].type= tax;
	board[3].block_id= 3;	board[3].name= "Tuzla";			board[3].price= 16500;	board[3].rent= 850;		board[3].rent_1 = 4250;		board[3].rent_2= 9500;		board[3].rent_3= 26000;		board[3].house_price= 12000; 	board[3].type= property;
	board[4].block_id= 4;	board[4].name= "Arnavutkoy";	board[4].price= 17000;	board[4].rent= 875;		board[4].rent_1 = 4500;		board[4].rent_2= 10000;		board[4].rent_3= 28000;		board[4].house_price= 12000; 	board[4].type= property;
	board[5].block_id= 5;	board[5].name= "Wait 2 Turn";	board[5].price= 0;		board[5].rent= 2;		board[5].rent_1 = 0;		board[5].rent_2= 0;			board[5].rent_3= 0;			board[5].house_price= 0; 		board[5].type= punish;
	board[5].block_id= 6;	board[6].name= "Catalca";		board[6].price= 20000;	board[6].rent= 1000;	board[6].rent_1 = 5000;		board[6].rent_2= 12000;		board[6].rent_3= 30000;		board[6].house_price= 13000; 	board[6].type= property;
	board[7].block_id= 7;	board[7].name= "Beykoz";		board[7].price= 23000;	board[7].rent= 1100;	board[7].rent_1 = 5500;		board[7].rent_2= 12500;		board[7].rent_3= 33000;		board[7].house_price= 13000; 	board[7].type= property;
	board[8].block_id= 8;	board[8].name= "Car Fix";		board[8].price= 0;		board[8].rent= 1750;	board[8].rent_1 = 0;		board[8].rent_2= 0;			board[8].rent_3= 0;			board[8].house_price= 0; 		board[8].type= tax;
	board[9].block_id= 9;	board[9].name= "Maltepe";		board[9].price= 30000;	board[9].rent= 1350;	board[9].rent_1 = 7000;		board[9].rent_2= 15000;		board[9].rent_3= 40000;		board[9].house_price= 15000; 	board[9].type= property;
	board[10].block_id= 10;	board[10].name= "Bills";		board[10].price= 0;		board[10].rent= 2000;	board[10].rent_1 = 0;		board[10].rent_2= 0;		board[10].rent_3= 0;		board[10].house_price= 0; 		board[10].type= tax;
	board[11].block_id= 11;	board[11].name= "Sisli";		board[11].price= 33000;	board[11].rent= 1500;	board[11].rent_1 = 8000;	board[11].rent_2= 16000;	board[11].rent_3= 42000;	board[11].house_price= 16000; 	board[11].type= property;
	board[12].block_id= 12;	board[12].name= "Oil";			board[12].price= 0;		board[12].rent= 2250;	board[12].rent_1 = 0;		board[12].rent_2= 0;		board[12].rent_3= 0;		board[12].house_price= 0; 		board[12].type= tax;
	board[13].block_id= 13;	board[13].name= "Atasehir";		board[13].price= 35000;	board[13].rent= 1600;	board[13].rent_1 = 8500;	board[13].rent_2= 17000;	board[13].rent_3= 45000;	board[13].house_price= 17000; 	board[13].type= property;
	board[14].block_id= 14;	board[14].name= "Sariyer";		board[14].price= 40000;	board[14].rent= 1750;	board[14].rent_1 = 9500;	board[14].rent_2= 19000;	board[14].rent_3= 48000;	board[14].house_price= 19000; 	board[14].type= property;
	board[15].block_id= 15;	board[15].name= "Wait 1 Turn";	board[15].price= 0;		board[15].rent= 1;		board[15].rent_1 = 0;		board[15].rent_2= 0;		board[15].rent_3= 0;		board[15].house_price= 0; 		board[15].type= punish;
	board[16].block_id= 16;	board[16].name= "Kadikoy";		board[16].price= 43000;	board[16].rent= 1900;	board[16].rent_1 = 11000;	board[16].rent_2= 21500;	board[16].rent_3= 55000;	board[16].house_price= 23000; 	board[16].type= property;
	board[17].block_id= 17;	board[17].name= "Besiktas";		board[17].price= 60000;	board[17].rent= 2500;	board[17].rent_1 = 15000;	board[17].rent_2= 28000;	board[17].rent_3= 60000;	board[17].house_price= 30000; 	board[17].type= property;
	board[18].block_id= 18;	board[18].name= "Vocation";		board[18].price= 0;		board[18].rent= 5000;	board[18].rent_1 = 0;		board[18].rent_2= 0;		board[18].rent_3= 0;		board[18].house_price= 0; 		board[18].type= tax;
	board[19].block_id= 19;	board[19].name= "Bebek";		board[19].price= 70000;	board[19].rent= 3500;	board[19].rent_1 = 20000;	board[19].rent_2= 35500;	board[19].rent_3= 65000;	board[19].house_price= 35000; 	board[19].type= property;

	
}

void show_board(struct block board[20],struct player player_one, struct player player_two) {
	
	int i;
	for(i=0 ; i<118 ;i++){
		printf("-");
	}
	printf("\n");
	
	printf("|     %s\t|\t%s\t|\t%s\t|\t%s\t|\t%s\t|\t%s  |\n", board[0].name, board[1].name, board[2].name, board[3].name, board[4].name, board[5].name);
	printf("|		|\t%d$\t\t|\t\t\t|\t%d$\t|\t%d$\t\t|	  	     |\n", board[1].price, board[3].price, board[4].price, board[5].price);
	printf("|\t\t|\t\t\t|\t\t\t|\t\t|\t\t\t|\t\t     |\n");
	
	for(i=0 ; i<118 ;i++){
		printf("-");
	}
	printf("\n");
	
	printf("|     %s\t|											|	%s      |\n", board[19].name , board[6].name);
	printf("|     %d$\t|											|	%d$	     |\n", board[19].price , board[6].price);
	printf("|	  	|											|\t\t     |\n");
	for(i=0 ; i<17 ;i++){
		printf("-");
	}
	for(i=0 ; i<83 ;i++){
		printf(" ");
	}
	for(i=0 ; i<18 ;i++){
		printf("-");
	}
	printf("\n");

	printf("|     %s\t|											|	%s       |\n", board[18].name , board[7].name);
	printf("|     \t\t|											|	%d$	     |\n", board[7].price);
	printf("|	  	|											|\t\t     |\n");
	for(i=0 ; i<17 ;i++){
		printf("-");
	}
	for(i=0 ; i<83 ;i++){
		printf(" ");
	}
	for(i=0 ; i<18 ;i++){
		printf("-");
	}
	printf("\n");
	
	printf("|     %s\t|											|	%s      |\n", board[17].name , board[8].name);
	printf("|     %d$\t|											|		     |\n", board[17].price);
	printf("|	  	|											|\t\t     |\n");
	for(i=0 ; i<17 ;i++){
		printf("-");
	}
	for(i=0 ; i<83 ;i++){
		printf(" ");
	}
	for(i=0 ; i<18 ;i++){
		printf("-");
	}
	printf("\n");
	
	printf("|     %s\t|											|	%s      |\n", board[16].name , board[6].name);
	printf("|     %d$\t|											|	%d$\t     |\n", board[16].price, board[6].price);
	printf("|	  	|											|\t\t     |\n");
	
	
	for(i=0 ; i<118 ;i++){
		printf("-");
	}
	printf("\n");
	
	
	printf("|  %s\t|\t%s\t\t|\t%s\t|\t%s\t|\t%s\t\t|\t%s\t     |\n", board[15].name, board[14].name, board[13].name, board[12].name, board[11].name, board[10].name);
	printf("|\t\t|\t%d$\t\t|\t%d$\t\t|\t\t|\t%d$\t\t|	  	     |\n", board[14].price, board[13].price,  board[11].price, board[10].price);
	printf("|\t\t|\t\t\t|\t\t\t|\t\t|\t\t\t|\t\t     |\n");
	
	for(i=0 ; i<118 ;i++){
		printf("-");
	}
	printf("\n");
}

void show_properties(struct block board[20]) {
	
	int i, selection;
	do{
		printf("Please select a property to see the details:\n");
		printf("1 -\t%s\n", board[1].name);
		printf("4 -\t%s\n", board[4].name);
		printf("6 -\t%s\n", board[6].name);
		printf("7 -\t%s\n", board[7].name);
		printf("9 -\t%s\n", board[9].name);
		printf("11 -\t%s\n", board[11].name);
		printf("13 -\t%s\n", board[13].name);
		printf("14 -\t%s\n", board[14].name);
		printf("16 -\t%s\n", board[16].name);
		printf("17 -\t%s\n", board[17].name);
		printf("19 -\t%s\n", board[19].name);
		printf("0 -\tExit\n\n");
		
		printf("Your selection: ");
		scanf("%d", &selection);
		
		if(selection==2 || selection==3 || selection==5 || selection==8 || selection==12 ||selection==15 || selection==18) printf("Not a property, try again.\n\n");
		
		
	}while( selection==2 || selection==3 || selection==5 || selection==8 || selection==12 ||selection==15 || selection==18);
	
	if(selection==0){
		printf("exiting...");
	}
	
	else{
		printf("\n\n");
	
		for(i=0 ; i<33 ; i++){
			printf("-");
		}
		printf("\n");
		printf("|	  %s		|\n", board[selection].name);
		
		for(i=0 ; i<33 ; i++){
			printf("-");
		}
		printf("\n");
		
		printf("|	  Rent		%d$	|\n", board[selection].rent);
		printf("|	  Rent 1 H	%d$	|\n", board[selection].rent_1);
		printf("|	  Rent 2 H	%d$	|\n", board[selection].rent_2);
		printf("|	  Rent 3 H	%d$	|\n", board[selection].rent_3);
		
		for(i=0 ; i<33 ; i++){
			printf("-");
		}
		printf("\n");
		
		printf("|	  House Price	%d$	|\n", board[selection].house_price);
		
		for(i=0 ; i<33 ; i++){
			printf("-");
		}
		printf("\n");
	}
	
}

int roll_dice (int lower_bound, int upper_bound){
	
	int result;
	
	srand(time(NULL));
    result = ( rand() % (upper_bound - lower_bound + 1) ) + lower_bound;
    
    return result;
        
}
/*
//This function should work, but i dont know why it doesnt.
void gameplay (struct block board[20], struct player player_one, struct player player_two){
	
	int choice;
	printf("1 - Roll the dice\n");
	printf("4 - Show property deeds\n");
	printf("Your Choice: ");
	scanf("%d", choice);
	
	switch(choice){
			case 1:{
				
				printf("%d", roll_dice(1,6));
				break;
			}
				
			case 2:{
				
				break;
			}
	
			case 3:{
				
				break;
			}
			
			case 4:{
				show_properties(board);
				break;
			}
			
			case 5:{
				
				break;
			}
			default:{
				
				break;
			}
		}	
	
}
*/
