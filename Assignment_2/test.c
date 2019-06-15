#include "sold.h"

void testing_functions()
{
   Cluster array;
   Cluster array_temp;
   int y, x;


   populate_board_2d_test(&array);
   printed_board_test(&array);

   /* Testing copy_board */
   copied_board_test(&array, &array_temp);

   /* Testing the rules applied to the board */
   available_moves_test(&array);
   peg_jump_rules_test(&array);

   y = 3, x = 3;
   /* These are the coordinates where the last peg has moved to so
      the function below can test if it found its solution or not */
   is_solution_test(y, x, &array);
}

void is_solution_test(int y, int x, Cluster *array)
{
   assert(is_solution(y, x, array) == true);
}

void printed_board_test(Cluster *array)
{
   /* Testing population of board */
   assert(array->board[0][0] == peg_dead);
   assert(array->board[0][4] == peg_dead);
   assert(array->board[1][1] == peg_dead);
   assert(array->board[1][4] == peg_dead);
   assert(array->board[2][2] == peg_alive);
   assert(array->board[2][3] == peg_alive);
   assert(array->board[3][3] == peg_alive);
   assert(array->board[3][2] == peg_alive);
}

void available_moves_test(Cluster *array)
{
   /* Testing peg rules on the first generated board */
   assert(available_move(north, array, 0, 3) == false);
   assert(available_move(north, array, 1, 2) == false);
   assert(available_move(north, array, 2, 1) == false);
   assert(available_move(north, array, 3, 0) == true);
   assert(available_move(north, array, 3, 4) == true);

   assert(available_move(south, array, 0, 3) == false);
   assert(available_move(south, array, 1, 2) == false);
   assert(available_move(south, array, 3, 4) == false);
   assert(available_move(south, array, 3, 0) == false);
   assert(available_move(south, array, 1, 4) == false);

   assert(available_move(west, array, 0, 3) == false);
   assert(available_move(west, array, 1, 2) == false);
   assert(available_move(west, array, 2, 1) == false);
   assert(available_move(west, array, 3, 0) == false);
   assert(available_move(west, array, 2, 4) == false);

   assert(available_move(east, array, 0, 3) == false);
   assert(available_move(east, array, 1, 2) == false);
   assert(available_move(east, array, 2, 1) == false);
   assert(available_move(east, array, 3, 0) == false);
   assert(available_move(east, array, 2, 52) == false);
}
   /* It is generaly assumed thatv the 2D board
      starts counting from the top left corner */
void peg_jump_rules_test(Cluster *array)
{
   /* Testing the jump up rule */
   peg_jump_rules(north, array, 3, 1);
   peg_jump_rules(north, array, 3, 2);

   /* Checking which cell has a peg and which one does not f*/
   assert(array->board[1][1] == peg_alive);
   assert(array->board[1][2] == peg_alive);
   assert(array->board[3][2] == peg_dead);

   /* Refreshing the 2D board*/
   populate_board_2d_test(array);

   /* Testing the jump right rule */
   peg_jump_rules(north, array, 3, 1);
   peg_jump_rules(north, array, 3, 2);
   peg_jump_rules(east, array, 1, 1);

   assert(array->board[1][1] == peg_dead);
   assert(array->board[1][3] == peg_alive);
   assert(array->board[3][1] == peg_dead);

   populate_board_2d_test(array);

   /* Testing the jump left rule */
   peg_jump_rules(north, array, 3, 1);
   peg_jump_rules(north, array, 3, 2);
   peg_jump_rules(west, array, 1, 2);

   assert(array->board[1][0] == peg_alive);
   assert(array->board[1][2] == peg_dead);
   assert(array->board[3][2] == peg_dead);

   populate_board_2d_test(array);

   /* Testing the jump down rule */
   peg_jump_rules(north, array, 3, 2);
   peg_jump_rules(west, array, 2, 4);
   peg_jump_rules(south, array, 1, 2);

   assert(array->board[3][3] == peg_alive);
   assert(array->board[2][2] == peg_dead);
   assert(array->board[1][4] == peg_dead);
}

void copied_board_test(Cluster *array, Cluster *array_temp)
{
   copy_array_test(array_temp, array);
   assert(array->board[0][0] == array_temp->board[0][0]);
   assert(array->board[1][3] == array_temp->board[1][3]);
   assert(array->board[3][2] == array_temp->board[3][2]);
   assert(array->board[2][4] == array_temp->board[2][4]);
}

void copy_array_test(Cluster *new_array, Cluster *old_array)
{
   int y, x;

   for (y = 0; y < ROWS_TEST; y++) {
      for (x = 0; x < COLUMNS_TEST; x++) {
         new_array->board[y][x] = old_array->board[y][x];
      }
   }
}

void populate_board_2d_test(Cluster *array)
{
   int y, x;

   for (y = 0; y < ROWS_TEST; y++) {
      for (x = 0; x < COLUMNS_TEST; x++) {
         if (y < ROW_MIDDLE_TEST) {
            array->board[y][x] = peg_dead;
         }
         else {
            array->board[y][x] = peg_alive;
         }
      }
   }
}

void print_array_test(Cluster *array)
{
   int y, x;

   for (y = 0; y < ROWS_TEST; y++) {
      for (x = 0; x < COLUMNS_TEST; x++) {
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
