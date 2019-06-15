#include "bst.h"
/* ############################### #DEFINES ################################ */
#define BACKSLASH_NULL_CHARACTER 1
#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)
/* ########################### PRIVATE FUNCTIONS ########################### */
/* Intialise the binary search tree (bst) structure */
bst* bst_init(char* v);

/* Inserting a new node into the binary search tree */
void bst_insert(bst* s, char* v);

/* Return true if the inserted word (v) exists in the */
/* binary search tree, or return false if it does not */
bool bst_isin(bst* s, char* v);

/* Clear all dynamic memory allocation related to the binary */
/* search tree by setting all the pointers to NULL */
void bst_free(bst* s);
/* ######################################################################### */
dic* dic_init(int size)
{
   dic* d;
   d = (dic* )malloc(sizeof(dic));
   if (d == NULL) {
      ON_ERROR("Failed to create dictionary node\n");
   }
   d->tree_head = NULL;
   d->element_size = size;

   return d;
}

bst* bst_init(char* v)
{
   bst* b;
   b = (bst* )malloc(sizeof(bst));
   if (b == NULL) {
      ON_ERROR("Failed to create bst node\n");
   }

   b->store_word = (char* )calloc(strlen(v) + BACKSLASH_NULL_CHARACTER,
                                                         sizeof(char));
   if (b->store_word == NULL) {
      ON_ERROR("Failed to create a sizeable array to store the word\n");
   }
   b->left = NULL;
   b->right = NULL;

   return b;
}

void dic_insert(dic* s, char* v)
{
   /* Check if the inserted word (v) is smaller than the string size limit */
   if (s->element_size < (int)(strlen(v) + BACKSLASH_NULL_CHARACTER)) {
      ON_ERROR("Size of word is greater than the space allocated\n");
   }
   /* Populate the binary search tree */
   if (s->tree_head == NULL) {
      s->tree_head = bst_init(v);
      bst_insert(s->tree_head, v);
   }
   else {
      bst_insert(s->tree_head, v);
   }
}

void bst_insert(bst* s, char* v)
{
   bst* bst_node;
   /* Traversing through the binary search tree */
   if (s == NULL || strcmp(v, s->store_word) == 0) {
      return;
   }
   /* If the word that is inserted is smaller than the one in */
   /* the node then store it to its left pointer (child) */
      if (strcmp(v, s->store_word) < 0) {
         if (s->left == NULL) {
         bst_node = bst_init(v);
         strcpy(bst_node->store_word, v);
         s->left = bst_node;
      }
      else {
         bst_insert(s->left, v);
      }
   }
   /* If the word that is inserted is greater than the one in */
   /* the node then store it to its right pointer (child) */
   else {
      if (s->right == NULL) {
         bst_node = bst_init(v);
         strcpy(bst_node->store_word, v);
         s->right = bst_node;
      }
      else {
         bst_insert(s->right, v);
      }
   }
}

bool dic_isin(dic* s, char* v)
{
   return bst_isin(s->tree_head, v);
}

bool bst_isin(bst* s, char* v)
{
   if (s == NULL) {
      return false;
   }
   /* Finding the stored word */
   if (strcmp(v, s->store_word) == 0) {
      return true;
   }
   /* Traversing through the binary search tree */
   /* (left or right) to find the searched word */
   if (strcmp(v, s->store_word) < 0) {
      return bst_isin(s->left, v);
   }
   else {
      return bst_isin(s->right, v);
   }
}

void bst_free(bst* s)
{
   if (s == NULL) {
      return;
   }
   bst_free(s->left);
   bst_free(s->right);
   free(s->store_word);
   free(s);
}

void dic_free(dic** s)
{
   if (s != NULL) {
      dic* b = *s;
      bst_free(b->tree_head);
      free(b);
      /* Ensuring that all allocated memory from the heap has been freed */
      *s = NULL;
   }
}
