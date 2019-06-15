#include "hsh.h"
/* ############################### #DEFINES ################################ */
#define INITIALISE_NUMBER 0
#define INITIALISE_CELL 0
#define BACKSLASH_NULL_CHARACTER 1
#define LOAD_FACTOR 0.6
#define HASHING_PRIME_NUMBER 5381
#define HASHING_NUMBER 33
#define EMPTY_CELL 0
#define GROW_TABLE_SIZE 2
#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)
/* ########################### PRIVATE FUNCTIONS ########################### */
/* Intialise the linked list (element) structure */
element* element_init(char *v);

/* Using the Berntein hashing method */
int hashing_function(char* s,int size);

/* Check number of elements in the board with respect to the load */
/* factor and resize the the hashboard by a growth factor of 2 */
void resize_hasing_board(dic* s);

/* Using the swap function by generating a temporary dictionary */
/* structure in order to resize the hashing table if necessary */
void swap_dictionaries(dic* dst, dic* src);
/* ######################################################################### */
dic* dic_init(int size)
{
   dic* d;
   int x;
   d = (dic* )malloc(sizeof(dic));
   if (d == NULL) {
      ON_ERROR("Failed to create a dictionary structure\n");
   }
   d->table_size = size;
   d->elements_number = INITIALISE_NUMBER;
   d->hashboard = (element** )calloc(size, sizeof(element* ));
   if (d->hashboard == NULL) {
      ON_ERROR("Failed to create a hash-table\n");
   }
   for (x = 0; x < d->table_size; x++) {
      d->hashboard[x] = INITIALISE_CELL;
   }
   return d;
}

element* element_init(char* v)
{
   element* list;
   list = (element* )malloc(sizeof(element));
   if (list == NULL) {
      ON_ERROR("Failed to create an element structure\n");
   }
   list->key = (char* )malloc((strlen(v) + BACKSLASH_NULL_CHARACTER)
                                                      * sizeof(char));
   if (list->key == NULL) {
      ON_ERROR("Failed to create space for each word \n");
   }

   list->next = NULL;

   return list;
}

void dic_insert(dic* s, char* v)
{
   int index_array;
   element* new_list;
   new_list = element_init(v);
   strcpy(new_list->key,v);
   /* The hashing function returns the int value, */
   /* which is used as the index for the hash-table */
   index_array = hashing_function(v,s->table_size);
   /* Pointing to the next new_list node */
   new_list->next = s->hashboard[index_array];
   /* Point back to the index of the hash-table */
   s->hashboard[index_array] = new_list;
   s->elements_number++;
   /* Checking if the number of elements is over the load factor */
   /* with respect to the size of the hash-table. In this case */
   /* the table is resized */
   if (s->elements_number >= (s->table_size * LOAD_FACTOR)) {
      resize_hasing_board(s);
   }
}

int hashing_function(char* s, int size)
{
   unsigned long hash = HASHING_PRIME_NUMBER;
   int c;
   while ((c = (*s++))) {
      hash = HASHING_NUMBER * hash ^ c;
   }
   return (int)(hash % size);
}

bool dic_isin(dic* s, char* v)
{
   int index_array;
   element* list;
   index_array = hashing_function(v,s->table_size);
   list = s->hashboard[index_array];
   /* Searching through each link of the linked list */
   while(list != EMPTY_CELL) {
      if(strcmp(list->key,v)==0) {
         return true;
      }
      list = list->next;
   }
   return false;
}

void resize_hasing_board(dic *s)
{
   dic* next_dictionary;
   element* list;
   int x;
   /* Resizing the dictionary to be two times larger */
   next_dictionary = dic_init(s->table_size * GROW_TABLE_SIZE);
   for (x = 0; x < s->table_size; x++) {
      list = s->hashboard[x];
      /* Rehashing the current dictionary. Then insert */
      /* everything from the old dictionary into the new one */
      while(list != EMPTY_CELL) {
         dic_insert(next_dictionary,list->key);
         list = list->next;
      }
   }
   /* Storing the old dictionary in a temporary dictionary. */
   /* Also swap between the new and the old dictionary */
   swap_dictionaries(s, next_dictionary);
   /* Free the temporary dictionary which contains the old dictionary */
   dic_free(&next_dictionary);
}

void swap_dictionaries(dic* dst, dic* src)
{
   dic temp_dictionary;

   temp_dictionary = *dst;
   *dst = *src;
   *src = temp_dictionary;
}

void dic_free(dic** s)
{
   int x;
   dic* ptr= *s;
   element *list, *next_list;
   /* Going through each link of the linked list */
   /* and free each node that is not empty */
   for (x = 0; x < ptr->table_size; x++) {
      list = ptr->hashboard[x];
      while(list != EMPTY_CELL) {
         next_list = list->next;
         free(list->key);
         free(list);
         list = next_list;
      }
   }
   free(ptr->hashboard);
   free(ptr);
   /* Ensuring that all allocated memory from the heap has been freed */
   *s = NULL;
}
