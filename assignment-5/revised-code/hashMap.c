/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Derek Yang
 * Date: 3/12/2018
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
        //loop through the map just like in traversal
        for (int i = 0; i < map->capacity; i++)
        {
            HashLink* link = map->table[i];
            if (link != NULL)
            {
                while (link != NULL)
                {
                    HashLink* tmpLink = link->next;
                    hashLinkDelete(link);
                    link = tmpLink;
                }
            }
        }
    free(map->table);
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
// FIXME: implement
int* hashMapGet(HashMap* map, const char* key)
{
    //use HASH_FUNCTION(key) and the maps capacity to find the index
    int idx = HASH_FUNCTION(key)% hashMapCapacity(map);
    HashLink * tmp = map->table[idx];

    //searches the entire list
    while(tmp != NULL){
        if(strcmp(tmp->key,key)==0){
            //returns a pointer to the value of the link with the given key
            return &tmp->value;
        }
        tmp = tmp->next;
    }
    //returns NULL if no link with that key is in the table
    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 *
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 *
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{

    struct HashMap  * tmpTable = map;
    struct HashLink * tmpLink;

    //Resizes the hash table to have a number of buckets equal to the given capcity
    hashMapInit(map,capacity);

    for(int i  = 0; i<capacity;i++) {
        //go through and add a header to the table for each link
        tmpLink = map->table[i];
        while (tmpLink != 0) {
            //rehash all links because capacity has changed
            hashMapPut(map, tmpLink->key, tmpLink->value);
            tmpLink = tmpLink->next;
        }
    }

        //free links CHECK IF i CAN JUST DO HASHMAPCLEANUP
        for(int i  = 0; i<capacity; i++){
            tmpLink = tmpTable->table[i];
            tmpTable->table[i] = NULL;
            while (tmpLink != 0){
                HashLink* tmpDelete = tmpLink;
                tmpLink = tmpLink->next;
                hashLinkDelete(tmpDelete);
            }
            free(tmpTable->table[i]);
        }
    //free old tables
        free(tmpTable);

    }

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @param value
 */


void hashMapPut(HashMap* map, const char* key, int value) {
    // FIXME: implement
    //resizes the map if needed
    //if(hashMapTableLoad(map) >= MAX_TABLE_LOAD){
    //    resizeTable(map,2*hashMapCapacity(map));
    // }

    //figure out the index location for hash
    int idx = HASH_FUNCTION(key) % hashMapCapacity(map);

    //creates a new temporary pointer to the table index
    struct HashLink *tmp = map->table[idx];

    if (tmp == NULL) {//if tmp is empty,create the first link
        struct HashLink *tmpLink = hashLinkNew(key, value, NULL);
        map->table[idx] = tmpLink;
        map->size++;
        //return;
    } else {//if tmp is not empty
        while (tmp != NULL) {//replace the value if it is the same
            if (strcmp(tmp->key, key)==0) {
                tmp->value = value;
                return;
            }
            tmp = tmp->next;
            //map->size++;
        }

        struct HashLink* tmpLink = map->table[idx];

        if(tmpLink->next == NULL){ //there is no next, meaning there is only one node
            struct HashLink * tmpLinkNext = hashLinkNew(key,value,NULL);
            tmpLink->next = tmpLinkNext;
            map->size++;
        } else {//there is a next, therefore there is more than one node
            struct HashLink *tmpLinkNext = hashLinkNew(key,value,NULL);
            while (tmpLink->next!= NULL){
                tmpLink = tmpLink->next;
            }
            tmpLink->next = tmpLinkNext;
            map->size++;
        }
        //return;
    }
}




/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */


void hashMapRemove(HashMap* map, const char* key)
{
// FIXME: implement

    //returns if the map does not contain key
    if(hashMapContainsKey(map,key)==0){
        return;
    }

    int idx = HASH_FUNCTION(key)%hashMapCapacity(map);

    HashLink* tmp = map->table[idx];
    HashLink * lastLink = map->table[idx];

    while(tmp != NULL){
        if(strcmp(tmp->key,key)==0){
            if(tmp == map->table[idx]){
                map->table[idx] = tmp->next;
                hashLinkDelete(tmp);
                map->size--;
                return;
            } else {
                lastLink->next = tmp->next;
                hashLinkDelete(tmp);
                map->size--;
                return;
            }
        } else {

            lastLink = tmp;
            tmp = tmp->next;
        }
        }

}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */

// FIXME: implement
int hashMapContainsKey(HashMap* map, const char* key)
{

    int idx;
    struct HashLink* tmp;

    //figure out the index location for hash
    idx = HASH_FUNCTION(key) % map->capacity;

    if(idx<0){
        idx += map->capacity;//just like wrapping in an array
    }

    tmp = map->table[idx];

    while(tmp !=NULL){//aka if tmp is not empty
        if(strcmp(tmp->key,key)==0){
            return 1;
        } else {
            tmp= tmp->next;//advance to next link in list
        }

    }
    return 0;

}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{

    return map->size;
    return 0;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
// FIXME: implement
int hashMapEmptyBuckets(HashMap* map)
{
    int count = 0;

    for(int i = 0; i<map->capacity;i++){
        if(map->table[i] == NULL){
            count++;
        }
    }

    //returns the count of empty buckets from the capacity
    return count;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
// FIXME: implement
float hashMapTableLoad(HashMap* map)
{

    return (float)map->size/map->capacity;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}