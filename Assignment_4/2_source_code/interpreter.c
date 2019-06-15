#include "../1_external_libraries/interpreter.h"
/* ###################### FUNCTION FOR COMMAND LINE ######################## */
state read_inputfile(int argc, char* argv[], char* inputfile)
{
   if(argc != TWO_ARGUMENTS) {
      printf("Please input only: programme_name and read_filename\n");
      ON_ERROR("Correct Format: ./interp 3_test_files/filename.txt\n");
   }

   if(sscanf(argv[1], "%s", inputfile) != ONE_ITEM_SCANNED) {
      ON_ERROR("Please input only: programme_name and read_filename\n");
   }
   return pass;
}
/* ####################### FUNCTIONS FOR INTERPRETER ####################### */
state parse_main(parse* data)
{
   if(strcmp(data->string_board[data->programme_cnt],
                              OPENING_BRACKET) != 0) {
      ERROR("parse_main function: Fatal error expecting an opening bracket",
                                    data->string_board[data->programme_cnt]);
   }
   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   if(!instrctlst(data)) {
      return error;
   }
   return pass;
}

state instrctlst(parse* data)
{
   if(strcmp(data->string_board[data->programme_cnt],
                              CLOSING_BRACKET) == 0) {
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      return pass;
   }
   if(!instruction(data)) {
      return error;
   }
   /* Check if the closing bracket is missing */
   if(strcmp(data->string_board[data->programme_cnt], "") == 0) {
      ERROR("instrctlst function: Fatal error expecting a closing bracket",
                                 data->string_board[data->programme_cnt]);
   }
   return instrctlst(data);
}

state instruction(parse* data)
{
   if(move_forward(data) || rotate_left(data) || rotate_right(data) ||
      set(data) || do_loop(data)) {
      return pass;
   }
   return error;
}

state do_loop(parse* data)
{
   int current_position, next_position;

   if(strcmp(data->string_board[data->programme_cnt],
                                 DO_INSTRUCTION) == 0) {
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if(!check_variable(data->string_board[data->programme_cnt])) {
         ERROR("do_loop function: Fatal error expecting <VAR>",
                     data->string_board[data->programme_cnt]);
      }
      /* The first position in which the first cell is stored  */
      current_position = *data->string_board[data->programme_cnt] - CHAR_A;

      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if(strcmp(data->string_board[data->programme_cnt],
                                 FROM_INSTRUCTION) != 0) {
         ERROR("do_loop function: Fatal error expecting a FROM",
                     data->string_board[data->programme_cnt]);
      }

      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if(!varnum(data->string_board[data->programme_cnt])) {
         ERROR("do_loop function: Fatal error expecting <VARNUM>",
                        data->string_board[data->programme_cnt]);
      }

      data->variables[current_position] = set_variable(data);

      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if(strcmp(data->string_board[data->programme_cnt],
                                 TO_INSTRUCTION) != 0) {
         ERROR("do_loop function: Fatal error expecting a TO",
                     data->string_board[data->programme_cnt]);
      }

      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if(!varnum(data->string_board[data->programme_cnt])) {
         ERROR("do_loop function: Fatal error expecting <VARNUM>",
                        data->string_board[data->programme_cnt]);
      }

      next_position = set_variable(data);

      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if(strcmp(data->string_board[data->programme_cnt],
                                 OPENING_BRACKET) != 0) {
         ERROR("do_loop function: Fatal error expecting an opening bracket {",
                                    data->string_board[data->programme_cnt]);
      }

      data->programme_cnt = data->programme_cnt + NEXT_LINE;

      if(!normal_and_reverse_loop(data, current_position, next_position)) {
         return error;
      }
      return pass;
   }
   return error;
}

state set(parse* data)
{
   stack top = NULL;
   int position;

   if (strcmp(data->string_board[data->programme_cnt],
                              SET_INSTRUCTION) == 0) {
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if (!check_variable(data->string_board[data->programme_cnt])) {
         ERROR("set function: Fatal error expecting <VAR>",
                  data->string_board[data->programme_cnt]);
      }
      /* The result of the reverse polish expression is stored in the correct
         position of the storing array */
      position = *data->string_board[data->programme_cnt] - CHAR_A;

      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if(strcmp(data->string_board[data->programme_cnt], ":=") != 0) {
         ERROR("set function: Fatal error expecting :=",
               data->string_board[data->programme_cnt]);
      }

      data->programme_cnt = data->programme_cnt + NEXT_LINE;

      if(!reverse_polish(data, &top)) {
         free_stack(top);
         return error;
      }
      /* Now the pointer of the stack ath the top must be the same as the
         set to the position of the storing array */
      data->variables[position] = top->input;

      free_stack(top);
      return pass;
   }
   return error;
}

state reverse_polish(parse* data, stack* top)
{
   if (strcmp(data->string_board[data->programme_cnt], SEMICOLON) == 0) {
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      return pass;
   }
   if(!check_operator(data->string_board[data->programme_cnt])) {
      if(!varnum(data->string_board[data->programme_cnt])) {
         ERROR("reverse_polish function: Fatal error expecting <POLISH>",
                                 data->string_board[data->programme_cnt]);
      }
   }
   /* Computing the result from two values on the stack using the reverse
      polish expression */
   if(!compute_reverse_polish(data, top)) {
      return error;
   }
   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   return reverse_polish(data, top);
}

state rotate_right(parse* data)
{
   if(strcmp(data->string_board[data->programme_cnt], MOVE_RIGHT) == 0) {
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if (!varnum(data->string_board[data->programme_cnt])) {
         ERROR("move_forward function: Fatal error expecting <VARNUM>",
                              data->string_board[data->programme_cnt]);
      }
      data->coords.rotation = data->coords.rotation + set_variable(data)
                                                       * M_PI / M_ANGLE;

      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      return pass;
   }
   return error;
}

state rotate_left(parse* data)
{
   if(strcmp(data->string_board[data->programme_cnt], MOVE_LEFT) == 0) {
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if (!varnum(data->string_board[data->programme_cnt])) {
         ERROR("move_forward function: Fatal error expecting <VARNUM>",
                              data->string_board[data->programme_cnt]);
      }
      data->coords.rotation = data->coords.rotation - set_variable(data)
                                                       * M_PI / M_ANGLE;

      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      return pass;
   }
   return error;
}

state move_forward(parse* data)
{
   int input_coords;

   if(strcmp(data->string_board[data->programme_cnt], MOVE_FORWARD) == 0) {
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if (!varnum(data->string_board[data->programme_cnt])) {
         ERROR("move_forward function: Fatal error expecting <VARNUM>",
                              data->string_board[data->programme_cnt]);
      }
      data->coords.coord_cnt = data->coords.coord_cnt + 1;

      input_coords = data->coords.coord_cnt;

      data->coords.x_coord[old][input_coords] =
      data->coords.x_coord[new][input_coords - PREVIOUS_POSITION];

      data->coords.x_coord[new][input_coords] =
      data->coords.x_coord[old][input_coords] + set_variable(data)
                                      * cos(data->coords.rotation);

      data->coords.y_coord[old][input_coords] =
      data->coords.y_coord[new][input_coords - PREVIOUS_POSITION];

      data->coords.y_coord[new][input_coords] =
      data->coords.y_coord[old][input_coords] + set_variable(data)
                                      * sin(data->coords.rotation);

      if(data->coords.coord_cnt >= MAX_COORDS_STORED) {
         printf("No more available space to store additional coordinates.\n");
         ON_ERROR("Please incease the #define MAX_COORDS_STORED\n");
      }

      data->programme_cnt = data->programme_cnt + NEXT_LINE;

      return pass;
   }
   return error;
}

state varnum(char* symbol)
{
   int x, counter_a = INITIALISE_INTEGER, counter_b = INITIALISE_INTEGER;

   if (check_variable(symbol)) {
      return pass;
   }
   else {
      /* Check if the symbol is a single character and an operator, since any
         operator by itself cannot be a valid number */
      if(strlen(symbol) == ONE_CHARACTER && check_operator(symbol)) {
         return error;
      }

      for(x = 0; x < (int)strlen(symbol); x++) {
         if(symbol[x] == DOT_CHAR) {
            /* Impossible to have an input with more than one '.' character */
            if (++counter_a > ONE_CHARACTER) {
               return error;
            }
         }
         else if (symbol[x] == MINUS_SIGN) {
            /* Impossible to have an input with more than one '-' sign */
            if (++counter_b > ONE_CHARACTER) {
               return error;
            }
         }

         if(!isdigit(symbol[x]) && symbol[x] != MINUS_SIGN &&
                                   symbol[x] != DOT_CHAR) {
            return error;
         }
      }
   }
   return pass;
}

state check_variable(char* variable)
{
   if(isupper(variable[0]) && strlen(variable) == ONE_CHARACTER) {
      return pass;
   }
   return error;
}

state check_operator(char* symbol)
{
   if(strcmp(symbol, "+") == 0 || strcmp(symbol, "-") == 0 ||
      strcmp(symbol, "*") == 0 || strcmp(symbol, "/") == 0) {
         return pass;
      }
   return error;
}

int check_calculation(char operat)
{
   if(operat == '+' || operat == '-' || operat == '*' ||
      operat == '/') {
      return TRUE_OPERAT;
   }
   else {
      /* Ensures that the stack has available moves to perform with
         multiple operands by using a big number such as MAX_LIMIT */
      return MAX_LIMIT;
   }
}

float compute_operation(stack *top, char operat)
{
   float temp;

   if(operat == '+') {
      return pop_stack(top) + pop_stack(top);
   }
   if(operat == '-') {
      temp = pop_stack(top);
      return pop_stack(top) - temp;
   }
   if(operat == '*') {
      return pop_stack(top) * pop_stack(top);
   }
   if(operat == '/') {
      temp = pop_stack(top);
      if(equal_float(temp, 0)) {
         ON_ERROR("Fatal error cannot divide by 0");
      }
      return pop_stack(top) / temp;
   }
   else {
      ON_ERROR("Please insert a valid operand");
   }
}

state equal_float(float x, float y)
{
   return fabs(x - y) < FLT_EPSILON;
}

int compute_reverse_polish(parse* data, stack* top)
{
   int position;

   if (varnum(data->string_board[data->programme_cnt])) {
      if (check_variable(data->string_board[data->programme_cnt])) {
         /* The programme is set to the position in which the input is
            represented as a VAR */
         position = *data->string_board[data->programme_cnt] - CHAR_A;

         /* Using the push function to insert the given data into the top of
            the stack */
         push_stack(top, data->variables[position]);
         data->stack_size++;
      }
      else {
         /* convert the string into an integer using "atoi" function */
         push_stack(top, atof(data->string_board[data->programme_cnt]));
         data->stack_size++;
      }
   }
   else {
      if (data->stack_size <
         check_calculation(data->string_board[data->programme_cnt][0])){
         ERROR("The stack does not have the correct number of items in it",
                                  data->string_board[data->programme_cnt]);
      }
      push_stack(top, compute_operation(top,
      data->string_board[data->programme_cnt][0]));

      data->stack_size--;
   }
   return pass;
}

int set_variable(parse* data)
{
   int value;
   /* Use the check_variable function to ensure that the number that is
      acquired is a valid integer. If not then the input on
      data->string_board[data->programme_cnt] arae converted to an integer */
   if(check_variable(data->string_board[data->programme_cnt])) {
      value = *data->string_board[data->programme_cnt] - CHAR_A;
      return data->variables[value];
   }
   else {
      /* convert the string into an integer using "atoi" function */
      return atoi(data->string_board[data->programme_cnt]);
   }
}

state normal_and_reverse_loop(parse* data, int initial_coords, int final_coords)
{
   int current_position, x;

   current_position = data->programme_cnt;
   if (data->variables[initial_coords] < final_coords) {
      for(x = data->variables[initial_coords]; x <= final_coords; x++){
         data->programme_cnt = current_position;
         data->variables[initial_coords] = x;
         if(!instrctlst(data)) {
            return error;
         }
      }
   }
   else {
      for(x = data->variables[initial_coords]; x >= final_coords; x--){
         data->programme_cnt = current_position;
         data->variables[initial_coords] = x;
         if(!instrctlst(data)) {
            return error;
         }
      }
   }
   return pass;
}
/* ########################## FUNCTIONS FOR STACK ########################## */
void push_stack(stack* top, float result)
{
	stack head;

   head = malloc(sizeof(*head));
	if (head == NULL) {
      ON_ERROR("Failed to create space for head\n");
	}

	head->input = result;
	head->next = *top;
	*top = head;
}

float pop_stack(stack* top)
{
   float result;
	stack start;

	if (*top == NULL) {
      ON_ERROR("There are no more items in the stack\n");
	}

	start = *top;
	result = start->input;
	*top = start->next;
	free(start);

	return result;
}

void free_stack(stack top)
{
   stack head;

   while(top != NULL) {
     	head = top->next;
     	free(top);
    	top = head;
   }
}
/* ########## FUNCTION FOR DYNAMIC MEMORY ALLOCATION AND FREEING ########### */
parse* initialise_parse()
{
   int x, y;
   parse* data;

   data = (parse*) malloc(sizeof(parse));
   if (data == NULL) {
      ON_ERROR("Failed to create parse head\n");
   }

   data->string_board = (char**) malloc(TOKEN_NUMBER * sizeof(char*));
   if (data->string_board == NULL) {
      ON_ERROR("Failed to create a string-board\n");
   }

   for (x = 0; x < TOKEN_NUMBER; x++) {
      data->string_board[x] = (char*) malloc(SIZE_OF_TOKEN * sizeof(char));
      if(data->string_board[x] == NULL) {
         ON_ERROR("Failed to create space for string-board cell\n");
      }
   }

   for (x = 0; x < SIZE_OF_VARIABLE_ARRAY; x++) {
      data->variables[x] = INITIALISE_INTEGER;
   }

   data->programme_cnt = INITIALISE_INTEGER;
   data->stack_size = INITIALISE_INTEGER;

   for (x = 0; x < TWO_COORDS; x++) {
      for (y = 0; y < MAX_COORDS_STORED; y ++)
      data->coords.x_coord[x][y] = INITIALISE_INTEGER;
      data->coords.y_coord[x][y] = INITIALISE_INTEGER;
   }
   /* Changing the initial position in order to comply with the initial
      window size of the neillsdl2.h file (800 x 600). Furthermore, the
      coordiantes in SDL start at the top left point. Thus, the coordinate
      set (400 x 300) is used as a starting position for both the old
      and new coordinates */
   data->coords.x_coord[0][0] = STARTING_HORIZONTAL_COORDINATES;
   data->coords.y_coord[0][0] = STARTING_VERTICAL_COORDINATES;
   data->coords.x_coord[1][0] = STARTING_HORIZONTAL_COORDINATES;
   data->coords.y_coord[1][0] = STARTING_VERTICAL_COORDINATES;

   /* Convert from rads to degrees. Also use 270 degrees in order to change
      theorientation of the turtle to start its motion towards the North */
   data->coords.rotation = STARTING_DIRECTION * M_PI/M_ANGLE;
   data->coords.coord_cnt = INITIALISE_INTEGER;

   return data;
}

void free_parse(parse* data)
{
   int x;

   for (x = 0; x < TOKEN_NUMBER; x++) {
      free(data->string_board[x]);
   }
   free(data->string_board);
   free(data);
}
/* ######################################################################### */
