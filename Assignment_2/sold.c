#include "sold.h"
/* ############################# MAIN FUNCTION ############################# */
int main(int argc, char const *argv[])
{
   static Elements node;
   static int array_backtrack[MAX_EXPECTED_GENERATIONS];
   int generations, y_coordinate, i, x_coordinate;
   int iterations = 0;
   Boolean result = false;

   acquire_user_coorinates(argc, argv, &y_coordinate, &x_coordinate);
   initialise_structure(&node);

   while(!result)
   {
      if(populate_array_1d(y_coordinate, x_coordinate, &node)) {
         result = true;
      }
      iterations++;
   }
   generations = find_backtrack(array_backtrack, &node);

   for(i = 0; i <= generations; i++){
      printf("\nParent Position = %d\n", array_backtrack[i]);
      printf("Step Number %d\n", (generations-i));
      print_array(&node.array[array_backtrack[i]]);
   }
   testing_functions();
   return EXIT_SUCCESS;
}
/* ############################### FUNCTIONS ############################### */
void acquire_user_coorinates(int first_arg, char const *second_arg[],
                              int *y_coordinate, int *x_coordinate)
{
   if (first_arg < THREE_ARGUMENTS || first_arg > THREE_ARGUMENTS){
      printf("\nError in entering the required input\n"\
      "Enter the data in the following format:\n");
      printf("Name of file, Vertical Coordiantes, Horizontal Coordinates\n\n");
      exit(EXIT_FAILURE);
   }

   if(sscanf(second_arg[1],"%d", y_coordinate) != 1){
      printf("\nPlease enter only one number in each coordinate\n\n");
      exit(EXIT_FAILURE);
   }
   if(sscanf(second_arg[2],"%d", x_coordinate) != 1){
      printf("\nPlease enter only one number in each coordinate\n\n");
      exit(EXIT_FAILURE);
   }

   if (*y_coordinate < 0 || *y_coordinate >= ROWS){
      printf("\nThe following coorinates must be entered within the"\
      " range: 0 < y < 7\n\n");
      exit (EXIT_FAILURE);
   }
   if (*x_coordinate < 0 || *x_coordinate >= COLUMNS ){
      printf("\nThe following coordinates must be entered within the"\
      " range: 0 < x < 6\n\n");
      exit (EXIT_FAILURE);
   }
   if(*y_coordinate >= ROW_MIDDLE){
      printf("\nThere is already a peg there\n"\
      "Please enter a different set of coordinates\n\n");
      exit (EXIT_FAILURE);
   }
}

int find_backtrack(int array[], Elements *e)
{
   int array_length = 0;
   int current_position = e->location_next - PREVIOUS_STEP;
   /* "PREVIOUS_STEP" is used to equalise the array length with the
      position of the final child case since the location of the
      first child is +1 because it was initialised in this manner */
   do {
      array[array_length] = current_position;
      current_position = e->array[current_position].location_parent;
      array_length++;

   }while(current_position != START_POSITION);

   return array_length;
}

int create_new_node_and_check_against_solution(Directions mobilise,
         Cluster *old_array, Cluster *new_array, Elements *e, int y,
                        int x, int y_coords_user, int x_coords_user)
{
   copy_array(new_array, old_array);
   peg_jump_rules(mobilise, new_array, y, x);
   copy_array(&e->array[e->location_next], new_array);
   parent_child_new_position(e);
   return is_solution(y_coords_user, x_coords_user, new_array);
}

Boolean is_solution(int y, int x, Cluster *check)
{
   if(check->board[y][x] == peg_alive) {
      return true;
   }
   return false;
}

void parent_child_new_position(Elements *e)
{
   e->array[e->location_next].location_parent = e->location_current;
   e->location_next = e->location_next + NEXT_POSITION;
}

void peg_jump_rules(Directions mobilise, Cluster *c, int y, int x)
{
   switch(mobilise) {
      case north:
         c->board[y-2][x] = peg_alive;
         c->board[y-1][x] = peg_dead;
         c->board[y][x] = peg_dead;
         break;
      case south:
         c->board[y+2][x] = peg_alive;
         c->board[y+1][x] = peg_dead;
         c->board[y][x] = peg_dead;
         break;
      case west:
         c->board[y][x-2] = peg_alive;
         c->board[y][x-1] = peg_dead;
         c->board[y][x] = peg_dead;
         break;
      case east:
         c->board[y][x+2] = peg_alive;
         c->board[y][x+1] = peg_dead;
         c->board[y][x] = peg_dead;
         break;
      default:
         printf("Error reading peg_jum_rules function\n");
         break;
   }
}

int available_move(Directions mobilise, Cluster *c, int y, int x)
{
   switch(mobilise) {
      case north:
         if ((y >= NORTH_LIMIT) && (c->board[y-1][x] == peg_alive) &&
            (c->board[y-2][x] == peg_dead)) {
            return true;
         }
         else {
            return false;
         }
      case south:
         if ((y <= SOUTH_LIMIT) && (c->board[y+1][x] == peg_alive) &&
            (c->board[y+2][x] == peg_dead)) {
            return true;
         }
         else {
            return false;
         }
      case west:
         if ((x >= WEST_LIMIT) && (c->board[y][x-1] == peg_alive) &&
            (c->board[y][x-2] == peg_dead)) {
            return true;
         }
         else{
            return false;
         }
      case east:
         if ((x <= EAST_LIMIT) && (c->board[y][x+1] == peg_alive)
            && (c->board[y][x+2] == peg_dead)) {
            return true;
         }
         else {
            return false;
         }
      default:
         printf("Error reading available_move function\n");
         break;
   }
   return false;
}

/* Populate 1d array with respect to the jump rules */
Boolean populate_array_1d(int y_coords_user, int x_coords_user, Elements *e)
{
   int y,x;
   Cluster old_array = e->array[e->location_current];
   Cluster new_array;
   /* Entering the 2D array and changing it according to the peg rules */
   for (y = 0; y < ROWS; y++) {
      for (x = 0; x < COLUMNS; x++) {
         if (old_array.board[y][x] == peg_alive ) {
            /* Testing each peg jump rule in all directions */
            if(available_move(north, &old_array, y, x)) {
               int solution = create_new_node_and_check_against_solution
               (north, &old_array, &new_array, e, y, x,
               y_coords_user, x_coords_user);
               if (solution) {
                  return true;
               }
            }
            if(available_move(south, &old_array, y, x)) {
               int solution = create_new_node_and_check_against_solution
               (south, &old_array, &new_array, e, y, x,
               y_coords_user, x_coords_user);
               if (solution) {
                  return true;
               }
            }
            if(available_move(west, &old_array, y, x)) {
               int solution = create_new_node_and_check_against_solution
               (west, &old_array, &new_array, e, y, x,
               y_coords_user, x_coords_user);
               if (solution) {
                  return true;
               }
            }
            if(available_move(east, &old_array, y, x)) {
               int solution = create_new_node_and_check_against_solution
               (east, &old_array, &new_array, e, y, x,
               y_coords_user, x_coords_user);
               if (solution) {
                  return true;
               }
            }
         }
      }
   }
   /* the position for the next parent case is updated */
   e->location_current = e->location_current + NEXT_POSITION;
   if(STORE_STRUCTS <= e->location_next) {
      printf("\nNot enough memory to store the entered coordinates\n"\
      "Please enter a new set of coordinates\n\n");
      exit(EXIT_FAILURE);
   }
   return false;
}

void copy_array(Cluster *new_array, Cluster *old_array)
{
   int y, x;

   for (y = 0; y < ROWS; y++) {
      for (x = 0; x < COLUMNS; x++) {
         new_array->board[y][x] = old_array->board[y][x];
      }
   }
}

void initialise_structure(Elements *e)
{
   populate_board_2d(e->array);
   e->location_current = START_POSITION;
   e->location_next = NEXT_POSITION;
}

void populate_board_2d(Cluster *array)
{
   int y, x;

   for (y = 0; y < ROWS; y++) {
      for (x = 0; x < COLUMNS; x++) {
         if (y < ROW_MIDDLE) {
            array->board[y][x] = peg_dead;
         }
         else {
            array->board[y][x] = peg_alive;
         }
      }
   }
}

void print_array(Cluster *array)
{
   int y, x;

   for (y = 0; y < ROWS; y++) {
      for (x = 0; x < COLUMNS; x++) {
         if(array->board[y][x] == peg_dead) {
            printf(".");
         }
         else if(array->board[y][x] == peg_alive) {
            printf("X");
         }
      }
      printf("\n");
   }
   printf("\n");
}
/* ######################################################################### */
