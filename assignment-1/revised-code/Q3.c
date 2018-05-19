/* CS261- Assignment 1 - Q.3*/
/* Name: Derek Yang
 * Date: 1/12/2017
 * Solution description:Use a simple bubble
 * sort to sort an array of int.
 */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>


void sort(int* number, int n){
    /*Sort the given array number , of length n*/
    //using a bubble sort
    int tmp = 0;
    for(int i = 0;i<(n-1);i++){
        for(int j = 0; j<n-i-1;j++){
            if(number[j]>number[j+1]){
                tmp = number[j];
                number[j] = number[j+1];
                number[j+1] = tmp;
            }
        }
    }
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    /*Allocate memory for an array of n integers using malloc.*/
    int *arr = (int*)malloc(n* sizeof(int));

    /*Fill this array with random numbers, using rand().*/
    for(int i = 0; i<n;i++){
        arr[i] = rand() % 100 + 1;
    }

    /*Print the contents of the array.*/
    for(int i = 0; i<n;i++){
        printf("Pre-sorted: %d\n",arr[i]);
    }

    /*Pass this array along with n to the sort() function of part a.*/
    sort(arr,n);

    /*Print the contents of the array.*/
    for(int i = 0; i<n;i++){
        printf("Sorted: %d\n",arr[i]);
    }

    return 0;
}
