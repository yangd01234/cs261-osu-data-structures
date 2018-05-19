/*  stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
    param:  s pointer to a string
    pre: s is not null
*/
char nextChar(char* s)
{
    static int i = -1;
    char c;
    ++i;
    c = *(s+i);
    if ( c == '\0' )
        return '\0';
    else
        return c;
}

/* Checks whether the (), {}, and [] are balanced or not
    param:  s pointer to a string
    pre: s is not null
    post:
*/
int isBalanced(char* s)
{
    struct DynArr *arr = newDynArr(10);
    char tmp;

    while((tmp = nextChar(s)) != 0){
        switch (tmp){
            case '(':
            case '{':
            case '[':
                pushDynArr(arr,tmp);
                break;
            case ')':
                if(topDynArr(arr) == '('){
                    popDynArr(arr);//removes the last element in the array
                    break;
                }
            case '}':
                if(topDynArr(arr) == '{'){
                    popDynArr(arr);
                    break;
                }
            case ']':
                if(topDynArr(arr) == '['){
                    popDynArr(arr);
                    break;
                }
        }
    }

    if(sizeDynArr(arr)){
        deleteDynArr(arr);
        return 0;
    } else {
        deleteDynArr(arr);
        return 1;
    }
}

int main(int argc, char* argv[]){

    char* s=argv[1];
    int res;

    printf("Assignment 2\n");

    res = isBalanced(s);

    if (res)
        printf("The string %s is balanced\n",s);
    else
        printf("The string %s is not balanced\n",s);

    return 0;
}

