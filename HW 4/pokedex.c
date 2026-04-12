#include <stdio.h>

//karakter karakter incele. flag kullan. eðer karakterlerden bir tanesi diðeriyle uyuþmuyorsa, flag=0 olsun ve döngüden çýksýn.

typedef enum pokemon {Charmander, Pikachu, Squirtle, Bulbasaur, Pidgeotto, Ratata, Mug, Caterpie, Zubat, Krabby} pokemon;
typedef enum attack_type {quadratic, linear} attack_type;


void pokedex (char Pokemon_name[10][11], int range[], int attack_power[], int stamina[]){
	
	char nameOfPokemon[11];
	
	printf("Please type the name of the Pokemon (type exit to close Pokedex):\n");
	scanf("%s", nameOfPokemon);
	
	int checkFlag=0;
	int i, j;
	
	for(i=0 ; i<10 ; i++){
		
		for(j=0 ; Pokemon_name[i][j]!='\0' ; j++){
			
			if(Pokemon_name[i][j] != nameOfPokemon[j]){
				checkFlag=1;
			}     	
		}
		
		if(checkFlag==0){
			
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

//pokemon Pokemon_name;


int main(){

	int range[10] = { 1, 3, 4, 3, 2, 2, 1, 2, 3, 2};
	int attack_power[10] = {500, 350, 300, 400, 250, 250, 350, 200, 350, 300};
	int stamina[10]= { 2200, 1500, 1700, 2500, 1900, 2500, 3000, 1200, 1250,  2600};
	
	char Pokemon_name[10][11]=  {"Charmander", "Pikachu", "Squirtle", "Bulbasaur", "Pidgeotto", "Ratata", "Mug", "Caterpie", "Zubat", "Krabby"} ;
	
	
	pokedex (Pokemon_name, range, attack_power, stamina);

	
return 0;
}
