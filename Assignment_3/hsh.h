#ifndef _HSH_H_
#define _HSH_H_
/* ############################## #INCLUDES ################################ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/* ############################# ENUMERATIONS ############################## */
enum boolean {false, true};
typedef enum boolean bool;
/* ############################## STRUCTURES ############################### */
/* A linked List will be used to solve possible collisions that will be */
/* encountered by using the hashing method */

struct element {         /* Structure for the linked list */
   char* key;            /* Storing a word from the dictionary */
   struct element* next; /* Link for the next item in the linked list */
};
typedef struct element element;

struct dic {             /* Structure for the dictionary */
   element** hashboard;  /* Storing pointers that point to each key */
   int elements_number;  /* Number of elements stored in the hash-table */
   int table_size;       /* Keeping track of the hash-table size */
};
typedef struct dic dic;
/* ########################### PUBLIC FUNCTIONS ############################ */
/* Initialising dictionary structure */
dic* dic_init(int size);

/* Inserting a new element into the dictionary */
void dic_insert(dic* s, char* v);

/* Search the dictionary to find if the inserted word (v) is in */
bool dic_isin(dic* s, char* v);

/* Finish up */
/* Clear all dynamic memory allocation related to the */
/* dictionary by setting all the pointers to NULL */
void dic_free(dic **s);
/* ######################################################################### */
#endif
