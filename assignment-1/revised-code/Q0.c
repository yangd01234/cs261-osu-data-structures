/* CS261- Assignment 1 - Q. 0*/
/* Name: Derek Yang
 * Date: 1/11/2018
 * Solution description: Practice with pointers and memory address
 */

#include <stdio.h>
#include<stdlib.h>

void fooA(int* iptr){
    /*Print the value pointed to by iptr*/
    printf("FooA value: %d\n",*iptr);

    /*Print the address pointed to by iptr*/
    printf("Address point to by iptr: %p\n",iptr);

    /*Print the address of iptr itself*/
    printf("Address of iptr: %p\n",&iptr);
}

int main(){

    /*declare an integer x*/
    int x = 10;

    /*print the address of x*/
    printf("Address of x: %p\n",&x);

    /*Call fooA() with the address of x*/
    fooA(&x);

    /*print the value of x*/
    printf("Value of x: %d\n",x);

    return 0;
}
