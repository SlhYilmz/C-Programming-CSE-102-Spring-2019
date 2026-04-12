#include <stdio.h>

int merge_sort(int array[], int lower, int higher){
	
	int middle;
	
	if(lower !=   higher){
		
		middle = (lower+higher)/2;
		
		merge_sort(array, lower, middle);
		merge_sort(array, middle+1, higher);
		
		merger_function(array, lower, middle, higher);
	}
	
}

int merger_function (int array[], int lower, int middle, int higher){
	
	int i, j;
	int left = middle-lower+1;
	int right = higher-middle;
	
	int tempArrayLeft[left], tempArrayRight[right];
	
	i=0;	/*This is for 'while loop' to start properly. Basically an initialization part. */
	j=0;	/*This is for 'while loop' to start properly. Basically an initialization part. */
	
	while(i<left){
		tempArrayLeft[i]=array[lower+i];
		i++;
	}
		
	while(j<right){
		tempArrayRight[j]=array[(middle+1)+j];
		j++;
	}
	
	
	i=0;	/*This is for 'while loops' to start properly. Basically an initialization part. */
	j=0;	/*This is for 'while loops' to start properly. Basically an initialization part. */
	
	while(i < left && j < right ){
		
		if(tempArrayLeft[i] <= tempArrayRight[j]){
			array[lower]=tempArrayLeft[i++];			
		}
		else{
			array[lower]=tempArrayRight[j++];
		}
		
		lower++;
	}
		
	/*Copies the elements in the temporary array to the original array. This is for left (lower) part.*/
	while(i < left){				
		array[lower++] = tempArrayLeft[i++];
	}
	
	/*Copies the elements in the temporary array to the original array. This is for right (upper) part.*/
	while(j < right){			
		array[lower++] = tempArrayRight[j++];
	}
}

int main(){
	
	int noOfElements, i;
	int arrayList[50];
	
	printf("Write number of elements for array, for maximum number of 50: ");
	scanf("%d", &noOfElements);
	printf("Write the elements for the array:\n");
	
	for(i=0 ; i< noOfElements; i++){
		scanf("%d", &arrayList[i]);
	
	}
	merge_sort(arrayList, 0, noOfElements-1);

	printf("Sorted array:\n");
	for(i=0 ; i< noOfElements; i++){
		printf("%d ", arrayList[i]);

	}
		
return 0;
}
