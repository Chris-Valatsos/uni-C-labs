#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* ############################### #DEFINES ################################ */
#define ROWS 8
#define COLUMNS 7
#define ROW_MIDDLE (ROWS / 2)
#define STORE_STRUCTS 5000000
#define START_POSITION 0
#define NEXT_POSITION 1
#define PREVIOUS_STEP 1
#define NORTH_LIMIT 2
#define SOUTH_LIMIT (ROWS - 3)
#define WEST_LIMIT 2
#define EAST_LIMIT (COLUMNS - 3)
#define MAX_EXPECTED_GENERATIONS 15
#define ROWS_TEST 4
#define COLUMNS_TEST 5
#define ROW_MIDDLE_TEST (ROWS_TEST/2)
#define THREE_ARGUMENTS 3
/* ############################# ENUMERATIONS ############################## */
enum directions {north, south, west, east};
typedef enum directions Directions;

enum peg_status {peg_dead, peg_alive};
typedef enum peg_status Peg_status;

enum boolean {false, true};
typedef enum boolean Boolean;
/* ############################## STRUCTURES ############################### */
struct cluster {  /* Inner Structure */
   int board[ROWS][COLUMNS];
   int location_parent; /* Indicates parent number of each child generated */
};
typedef struct cluster Cluster;

struct elements { /* Outer Structure */
   Cluster array[STORE_STRUCTS];
   int location_current; /* Location of parent case*/
   int location_next; /* Location of last child case generated*/
};
typedef struct elements Elements;
/* ############################### FUNCTIONS ############################### */
/* --------------------------- sold.c functions ---------------------------- */
/* Prints 2D array inside the inner structure */
void print_array(Cluster *array);

/* Populates 2D array with peg_alive = 'X' and peg_dead = '.'*/
void populate_board_2d(Cluster *array);

/* Initialising all data types within the structure 'Elements' */
void initialise_structure(Elements *e);

/* Creating a copy of each cell in the 1D array to apply rules to the
   temporary cell and then print it as a child case*/
void copy_array(Cluster *new_array, Cluster *old_array);

/* Testing for available moves within each cell of the 2D array and use the
   peg rules to move in any direction available*/
Boolean populate_array_1d(int y_coords, int x_coords, Elements *e);

/* Checking if the tested cell can move in any direction
   (it can not move diagonally) */
int available_move(Directions mobilise, Cluster *c, int y, int x);

/* Applies the available jump rule and sets the 2D board accordingly */
void peg_jump_rules(Directions mobilise, Cluster *c, int y, int x);

/* Once all child cases are generated the current and next positions
   are updated */
void parent_child_new_position(Elements *e);

/* Checking if the coordinates given from the user are found by applying
   the peg rules */
Boolean is_solution(int y, int x, Cluster *check);

/* Combining all steps for a succesfull generation of the
   children of each parent as well as updating their position  */
int create_new_node_and_check_against_solution(Directions mobilise,
         Cluster *old_array, Cluster *new_array, Elements *e, int y,
                        int x, int y_coords_user, int x_coords_user);

/* Tracking back the location of child and showing where its parent case
   until it reaches the first board*/
int find_backtrack(int array[], Elements *e);

/* Acquiring target coordinates from user, from the command line, and
   making sure that the correct input is inserted */
void acquire_user_coorinates(int first_arg, char const *second_arg[],
                              int *y_coordinate, int *x_coordinate);
/* --------------------------- test.c functions ---------------------------- */
void testing_functions();
void populate_board_2d_test(Cluster *array);
void print_array_test(Cluster *array);
void printed_board_test(Cluster *array);
void available_moves_test(Cluster *array);
void peg_jump_rules_test(Cluster *array);
void copy_array_test(Cluster *new_array, Cluster *old_array);
void copied_board_test(Cluster *array, Cluster *array_temp);
void is_solution_test(int y, int x, Cluster *array);
