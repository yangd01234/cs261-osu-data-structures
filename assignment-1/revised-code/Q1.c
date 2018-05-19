/* CS261- Assignment 1 - Q.1*/
/* Name:Derek Yang
 * Date:1/19/2018
 * Solution description:Practice with student structures and
 * memory allocation
 */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
    int id;
    int score;
};

struct student* allocate(){
    /*Allocate memory for ten students*/
    struct student *multi_student = (struct student*)malloc(10*sizeof(struct student));
    /*return the pointer*/
    return multi_student;
}

void generate(struct student* students){
    /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
    int j,k,tmp;
    //list all the students from 1-10
    for (int i = 0; i < 10; i++) {
        (students + i)->id = i + 1;
        (students + i)->score = rand() % 100 + 0;
    }
    //shuffles the id's
    for(int i = 0; i<10;i++){
        int rnd = (rand()%10+1);
        int tmp = (students + rnd)->id;
        int tmp2 = (students+i)->id;

        (students + rnd)->id = tmp2;
        (students+i)->id = tmp;
    }

}

void output(struct student* students){
    /*Output information about the ten students in the format:
             ID1 Score1
             ID2 score2
             ID3 score3
             ...
             ID10 score10*/
    for (int i = 0; i < 10; i++) {
        printf("ID%d", (students + i)->id);
        printf(" Score %d\n", (students + i)->score);
    }
}

void summary(struct student* students){
    /*Compute and print the minimum, maximum and average scores of the ten students*/
    int min = 0;
    int max = 0;
    int avg = 0;
    int total = 0;
    for(int i = 0;i<10;i++){
        //min check
        if(min>(students + i)->score){
            min = (students + i)->score;
        }
        //max check
        if(max<(students + i)->score){
            max = (students + i)->score;
        }
        //total
        total += (students + i)->score;
    }
    avg = total/10;
    printf("The minimum is: %d\n",min);
    printf("The maximum is: %d\n",max);
    printf("The average is: %d\n",avg);

}

void deallocate(struct student* stud){
    /*Deallocate memory from stud*/
    free(stud);
}

int main(){
    struct student* stud = NULL;

    /*call allocate*/
    stud  = allocate();

    /*call generate*/
    generate(stud);

    /*call output*/
    output(stud);

    /*call summary*/
    summary(stud);

    /*call deallocate*/
    deallocate(stud);

    return 0;
}
