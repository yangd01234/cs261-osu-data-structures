/* CS261- Assignment 1 - Q.4*/
/* Name:Derek Yang
 * Date:1/19/2018
 * Solution description:Sort an array of students.
 */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
	/*Sort the n students based on their score*/
	struct student tmp;
	for(int i = 0;i<(n-1);i++){
		for(int j = 0; j<n-i-1;j++){
			if(students[j].score>students[j+1].score){
				tmp = students[j];
				students[j] = students[j+1];
				students[j+1] = tmp;
			}
		}
	}

}

int main(){
	/*Declare an integer n and assign it a value.*/
	int n = 4;
	/*Allocate memory for n students using malloc.*/
	struct student *students = (struct student*)malloc(n*sizeof(struct student));

	/*Generate random and unique IDs and random scores for the n students, using rand().*/
	//list all the students from 1-10
	for (int i = 0; i < n; i++) {
		(students + i)->id = i + 1;
		(students + i)->score = rand() % 100 + 0;
	}
	//shuffles the id's
	for(int i = 0; i<n;i++){
		int rnd = (rand()%n+1);
		int tmp = (students + rnd)->id;
		int tmp2 = (students+i)->id;

		(students + rnd)->id = tmp2;
		(students+i)->id = tmp;
	}
	/*Print the contents of the array of n students.*/
	printf("Pre-Sort\n");
	for (int i = 0; i < n; i++) {
		printf("ID%d", (students + i)->id);
		printf(" Score %d\n", (students + i)->score);
	}
	/*Pass this array along with n to the sort() function*/
	sort(students,n);

	/*Print the contents of the array of n students.*/
	printf("Sorted\n");
	for (int i = 0; i < n; i++) {
		printf("ID%d", (students + i)->id);
		printf(" Score %d\n", (students + i)->score);
	}
	return 0;
}
