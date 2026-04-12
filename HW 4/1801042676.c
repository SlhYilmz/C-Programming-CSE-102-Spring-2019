#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum pokemon {Charmander, Pikachu, Squirtle, Bulbasaur, Pidgeotto, Ratata, Mug, Caterpie, Zubat, Krabby} pokemon;
typedef enum attack_type {quadratic, linear} attack_type;

void menu ();
void pokedex (char Pokemon_name[10][11], int range[], int attack_power[], int stamina[]);
void oaks_laboratory (char Pokemon_name[10][11], pokemon Pokemons[], pokemon *my_Pokemons );
void show_Pokemons (char Pokemon_name[10][11], pokemon Pokemons[], int pokemon_count );
void catch_a_pokemon (char Pokemon_name[10][11], pokemon Pokemons[], pokemon *my_pocket );

/*
void release_a_pokemon (char Pokemon_name[10][11], pokemon Pokemons[], pokemon *my_pocket );

void battle (char Pokemon_name[10][11], int range[], attack_type type[], int attack_power[], int stamina[], pokemon user_Pokemons[] );

void show_area (char Pokemon_name[10][11], int area[8][8], int pokemon_staminas_view[8][8] );

*/

int main(){
	
	menu();		/*This menu function includes all the other functions within a switch-case. This way, the main function is not cluttered.  */
	
	
return 0;
}

void menu (){
	
	/*Things below this include pre-determined values for each pokemon. Pokemon_name double array, includes the names.*/
	char Pokemon_name[10][11]=  {"Charmander", "Pikachu", "Squirtle", "Bulbasaur", "Pidgeotto", "Ratata", "Mug", "Caterpie", "Zubat", "Krabby"} ;
	int range[10] = { 1, 3, 4, 3, 2, 2, 1, 2, 3, 2};
	int attack_power[10] = { 500, 350, 300, 400, 250, 250, 350, 200, 350, 300};
	int stamina[10]= { 2200, 1500, 1700, 2500, 1900, 2500, 3000, 1200, 1250, 2600};
	
	pokemon my_Pokemons[4];
	pokemon Pokemons[10]={Charmander, Pikachu, Squirtle, Bulbasaur, Pidgeotto, Ratata, Mug, Caterpie, Zubat, Krabby };
	
	int choice;
	
	do{	
		printf("\n***** MENU *****\n");
		printf("1. Open Pokedex\n");
		printf("2. Go to Oak's Laboratory\n");
		printf("3. Enter the tournament\n");
		printf("4. Exit\n");
			
		printf("\nChoice: ");
		scanf("%d", &choice);
			
		switch(choice){
			case 1:{
				pokedex (Pokemon_name, range, attack_power, stamina);		
				break;
			}
				
			case 2:{
				oaks_laboratory(Pokemon_name, Pokemons, my_Pokemons);
				break;
			}
	
			case 3:{
				/* I couldn't do these parts */		
				break;
			}
			
			case 4:{
				/* I couldn't do these parts */	
				break;
			}
			default:{
				
				break;
			}
		}	
		
	}while(choice!=4);
		
}

void pokedex (char Pokemon_name[10][11], int range[], int attack_power[], int stamina[]){
	
	char nameOfPokemon[11];
	
	printf("Please type the name of the Pokemon (type exit to close Pokedex):\n");
	scanf("%s", nameOfPokemon);
	
	int checkFlag=0;
	int i, j;
	
	/* This double for loop looks for all the letters in the array.
	 * If it is the same as the Pokemon name we want, it goes to the switch-case, which prints the properties of each Pokemon.
	 */
	for(i=0 ; i<10 ; i++){
		
		for(j=0 ; Pokemon_name[i][j]!='\0' ; j++){
			
			if(Pokemon_name[i][j] != nameOfPokemon[j]){
				checkFlag=1;
				break;			/*If the string that user wrote does not match the name of the Pokemons, it exits from the pokedex. */
			}     	
		}
		
		if(checkFlag==0){
			
			/*I can use strings in the case statements, since they are in enum type.*/
			switch(i){
				case (Charmander):{
					printf("Name: Charmander\n");
					printf("A. type: quadratic\n");
					printf("Range: %d block\n", range[i]);
					printf("A. power: %d\n", attack_power[i]);
					printf("Stamina: %d\n", stamina[i]);
					break;
				}
				case (Pikachu):{
					printf("Name: Pikachu\n");
					printf("A. type: linear\n" );
					printf("Range: %d block\n", range[i]);
					printf("A. power: %d\n", attack_power[i]);
					printf("Stamina: %d\n", stamina[i]);
					break;
				}
				case (Squirtle):{
					printf("Name: Squirtle\n");
					printf("A. type: linear\n" );
					printf("Range: %d block\n", range[i]);
					printf("A. power: %d\n", attack_power[i]);
					printf("Stamina: %d\n", stamina[i]);
					break;
				}
				case (Bulbasaur):{
					printf("Name: Bulbasaur\n");
					printf("A. type: linear\n" );
					printf("Range: %d block\n", range[i]);
					printf("A. power: %d\n", attack_power[i]);
					printf("Stamina: %d\n", stamina[i]);
					break;
				}
				case (Pidgeotto):{
					printf("Name: Pidgeotto\n");
					printf("A. type: quadratic\n" );
					printf("Range: %d block\n", range[i]);
					printf("A. power: %d\n", attack_power[i]);
					printf("Stamina: %d\n", stamina[i]);
					break;
				}
				case (Ratata):{
					printf("Name: Ratata\n");
					printf("A. type: linear\n" );
					printf("Range: %d block\n", range[i]);
					printf("A. power: %d\n", attack_power[i]);
					printf("Stamina: %d\n", stamina[i]);
					break;
				}
				case (Mug):{
					printf("Name: Mug\n");
					printf("A. type: quadratic\n" );
					printf("Range: %d block\n", range[i]);
					printf("A. power: %d\n", attack_power[i]);
					printf("Stamina: %d\n", stamina[i]);
					break;
				}
				case (Caterpie):{
					printf("Name: Caterpie\n");
					printf("A. type: quadratic\n" );
					printf("Range: %d block\n", range[i]);
					printf("A. power: %d\n", attack_power[i]);
					printf("Stamina: %d\n", stamina[i]);
					break;
				}
				case (Zubat):{
					printf("Name: Zubat\n");
					printf("A. type: linear\n" );
					printf("Range: %d block\n", range[i]);
					printf("A. power: %d\n", attack_power[i]);
					printf("Stamina: %d\n", stamina[i]);
					break;
				}
				case (Krabby):{
					printf("Name: Krabby\n");
					printf("A. type: linear\n" );
					printf("Range: %d block\n", range[i]);
					printf("A. power: %d\n", attack_power[i]);
					printf("Stamina: %d\n", stamina[i]);
					break;
				}
				default:{
					
					break;
				}
			}
		}	
		checkFlag=0;
	}	

}

void oaks_laboratory (char Pokemon_name[10][11], pokemon Pokemons[], pokemon *my_Pokemons ){
	
	int i, choice;
	int pokemonCount=10;
	
	printf("1. Show Pokemons\n");
	printf("2. Catch Pokemons\n");
	printf("3. Release Pokemons\n");
	printf("4. Show my pocket\n");
	scanf("%d", &choice);
	
	switch(choice){
		case 1:{
			show_Pokemons(Pokemon_name, Pokemons, pokemonCount);
			break;
		}
		case 2:{
			catch_a_pokemon(Pokemon_name, Pokemons, my_Pokemons);
			break;
		}
		case 3:{
			/* I couldn't do these parts */	
			break;
		}
		case 4:{
			/* I couldn't do these parts */	
			break;
		}
		default:{
			
			break;
		}
		
		
	}
	
}

void show_Pokemons (char Pokemon_name[10][11], pokemon Pokemons[], int pokemon_count ){
	
	int i;
	printf("\n");
	/*A basic for loop to print all the Pokemons.*/
	for(i=0 ; i<pokemon_count ; i++){
		printf("%d - %s\n", i, Pokemon_name[i]);
	}
}

void catch_a_pokemon (char Pokemon_name[10][11], pokemon Pokemons[], pokemon *my_pocket ){
	
	int i, j, k=4, pick;
	int pokemonCount = 10;
	
	show_Pokemons(Pokemon_name, Pokemons, pokemonCount);		/*Prints the list of Pokemons. */
	
	for(i=0 ; i<k ; i++){		
		scanf("%d", &pick);
		pick == *(my_pocket+i);;
	}
		
	
		
}
