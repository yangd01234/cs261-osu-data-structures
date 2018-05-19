/* CS261- Assignment 1 - Q.2*/
/* Name:Derek Yang
 * Date:1/12/2018
 * Solution description:  More practice with pointers
 */

#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = *a * 2;

    /*Set b to half its original value*/
    *b = *b/2;

    /*Assign a+b to c*/
    c = *a+*b;

    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x,y,z;
    x = 5;
    y = 6;
    z = 7;
    /*Print the values of x, y and z*/
    printf("The value of x is: %d\n",x);
    printf("The value of y is: %d\n",y);
    printf("The value of z is: %d\n",z);

    /*Call foo() appropriately, passing x,y,z as parameters*/
    int val = foo(&x,&y,z);

    /*Print the value returned by foo*/
    printf("The value returned by foo: %d\n",val);

    /*Print the values of x, y and z again*/
    printf("The new value of x is: %d\n",x);
    printf("The new value of y is: %d\n",y);
    printf("The new value of z is: %d\n",z);

    /*Is the return value different than the value of z?  Why?*/
    /*The return value is different then the value of z.  This is
     * because z was passed by value not by reference, therefore
     *x and y were modified, but z was not.*/
    return 0;
}


