#include <stdio.h>
#include <math.h>

int take_grades ( int [] );
int take_exam_grades (int [] );
double calculate_homework( int [] );
double calculate_lab( int [] );
double calculate_all( int, int[], int );


int main(){
	int i, lab_grades[10], hw_grades[10], exams[2]; 
	double labAverage=0, hwAverage=0;
	
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
	printf("Weighted Average: %.1lf\n", calculate_all(labAverage, exams, hwAverage));
	
return 0;
}

int take_grades ( int lab_hw_grades[]){
	
	int i, grade;
	
	for(i=0 ; i<10 ; i++){
		printf("%d. grade: ",i+1);
		scanf("%d",&lab_hw_grades[i]);
	}
	return 0;					
}

int take_exam_grades (int exams[]){
	
	int i, midterm, final;
	
	printf("Midterm Grade: ");
	scanf("%d", &midterm);
	printf("Final Grade: ");
	scanf("%d", &final);
	
	exams[0]=midterm;
	exams[1]=final;

	return 0;
}
double calculate_homework( int homeworkGradesMean[]){
	
	double sum = 0;
	int i=0;
	
    for (i=0; i<10 ; i++){
    	sum += homeworkGradesMean[i];
	}

	return (sum/10);
	
}
double calculate_lab( int labGradesMean[]){
	double sum = 0;
	int i=0; 
	
    for (i=0 ; i<10 ; i++){
    	sum += labGradesMean[i];
	} 
    
	return (sum/10);
	
}

double calculate_all( int labAverage, int exam[], int hwAverage){
	
	double average=0;
	average =(double)(hwAverage*0.1 + labAverage*0.2 + exam[0]*0.3 + exam[1]*0.4);
	
	return average; 
}


