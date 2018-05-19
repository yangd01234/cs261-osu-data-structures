#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';

    for(int i = 0; word[i];i++){
        word[i] = tolower(word[i]);
    }

    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
// FIXME: implement
void loadDictionary(FILE* file, HashMap* map)
{
    //printf("printing map\n");
    char *tmp = nextWord(file);

    while(tmp != NULL){
        //printf("this is: %s\n",tmp);
       hashMapPut(map,tmp,1);
        //free(tmp);
        tmp = nextWord(file);
    }
    //free(tmp);

    //hashMapPrint(map);
}
//levenshtein implementation source: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C
int levenshtein(char *s1, char *s2) {
    unsigned int s1length, s2length, x, y, lastd, oldd;

    //assign the lengths for string 1 and 2
    s1length = strlen(s1);
    s2length = strlen(s2);

    unsigned int column[s1length+1];

    for (y = 1; y <= s1length; y++)
        column[y] = y;
    for (x = 1; x <= s2length; x++) {
        column[0] = x;
        for (y = 1, lastd = x-1; y <= s1length; y++) {
            oldd = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1,
                             lastd + (s1[y-1] == s2[x-1] ? 0 : 1));
            lastd = oldd;
        }
    }
    //return the grid where you receive the int for distance
    return(column[s1length]);
}


//traverse
void traverse(HashMap* map,char *s1)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            while (link != NULL)
            {
                link->value = levenshtein(s1,link->key);//sets the link value to levenshtein's distance
                link = link->next;
            }
        }
    }
    //hashmap
   // hashMapPrint(map);
//add to array if >array element
}


void traversal(HashMap* map){
    int counter5 = 0;
    int counterLev = 1;

    while(counter5<5){

        //loop through the map
        for (int i = 0; i < map->capacity; i++)
        {
            HashLink* link = map->table[i];
            if (link != NULL)
            {
                while (link != NULL && counter5<5)
                {
                    if(link->value == counterLev){
                        //if the link value is counterLev, print
                        printf("Did you mean: %s\n",link->key);
                        counter5++;
                    }
                    link = link->next;
                }
            }
        }
        counterLev++;


    }
}
/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);

        //make input buffer all lower case
        for(int i = 0; inputBuffer[i];i++){
            inputBuffer[i] = tolower(inputBuffer[i]);
        }
        // Implement the spell checker code here..


        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        } else if (hashMapContainsKey(map,inputBuffer)){
            printf("Spelled correctly: %s\n",inputBuffer);

        } else {
            printf("Please see the following top 5 results\n");
            traverse(map,inputBuffer);
            traversal(map);
            //hashMapPrint(map);
        }


    }
    
    hashMapDelete(map);
    return 0;
}