/* CS261- Assignment 1 - Q.5*/
/* Name:Derek Yang
 * Date: 1/17/2018
 * Solution description: Used a for loop and if/then statements for
 * solving the sticky caps problem.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
    return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
    return ch-'A'+'a';
}

void sticky(char* word){
    /*Convert to sticky caps*/
    for(int i = 0; i<strlen(word);i++){
        //if lower case and even change to upper
        if((word[i] >= 'a' && word[i] <= 'z') && (i%2 == 0)){
            word[i] = toUpperCase(word[i]);
        }//if upper case and odd change to
        else if ((word[i] >= 'A' && word[i] <= 'Z') && (i%2 != 0)){
            word[i] = toLowerCase(word[i]);
        }
    }
}

int main(){
    /*Read word from the keyboard using scanf*/
    char word[100];
    printf("Enter in a word to be converted: ");
    scanf("%[^\n]",word);

    /*Call sticky*/
    sticky(word);

    /*Print the new word*/
    printf("%s\n",word);

    return 0;
}
