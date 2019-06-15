#ifndef _BST_H_
#define _BST_H_
/* ############################## #INCLUDES ################################ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/* ############################# ENUMERATIONS ############################## */
enum boolean {false, true};
typedef enum boolean bool;
/* ############################## STRUCTURES ############################### */
struct bst {            /* Structure for the binary search tree */
   char* store_word;    /* Pointing to a 1d array that stores */
                        /* a word from the loaded files */
   struct bst* left;    /* Storing the address of the left child */
   struct bst* right;   /* Storing the address of the right child */
};
typedef struct bst bst;

struct dic {            /* Structure for the dictionary */
   bst* tree_head;      /* Pointing to the root of the binary search tree */
   int element_size;    /* Size of word stored */
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
void dic_free(dic** s);
/* ######################################################################### */
#endif
