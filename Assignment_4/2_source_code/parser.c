#include "../1_external_libraries/parser.h"
/* ###################### FUNCTION FOR COMMAND LINE ######################## */
state read_inputfile(int argc, char* argv[], char* inputfile)
{
   if(argc != TWO_ARGUMENTS) {
      printf("Please input only: programme_name and read_filename\n");
      ON_ERROR("Correct Format: ./parse 3_test_files/filename.txt\n");
   }

   if(sscanf(argv[1], "%s", inputfile) != ONE_ITEM_SCANNED) {
      ON_ERROR("Please input only: programme_name and read_filename\n");
   }
   return pass;
}
/* ######################### FUNCTIONS FOR PARSER ########################## */
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
   if(strcmp(data->string_board[data->programme_cnt], "") == 0){
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
   if(strcmp(data->string_board[data->programme_cnt],
                                 DO_INSTRUCTION) == 0) {
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if(!check_variable(data->string_board[data->programme_cnt])) {
         ERROR("do_loop function: Fatal error expecting <VAR>",
                     data->string_board[data->programme_cnt]);
      }

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

      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if(strcmp(data->string_board[data->programme_cnt],
                                 OPENING_BRACKET) != 0) {
         ERROR("do_loop function: Fatal error expecting an opening bracket {",
                                    data->string_board[data->programme_cnt]);
      }

      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if(!instrctlst(data)) {
         return error;
      }
      return pass;
   }
   return error;
}

state set(parse* data)
{
   if (strcmp(data->string_board[data->programme_cnt],
                              SET_INSTRUCTION) == 0) {
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if (!check_variable(data->string_board[data->programme_cnt])) {
         ERROR("set function: Fatal error expecting <VAR>",
                  data->string_board[data->programme_cnt]);
      }
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if(strcmp(data->string_board[data->programme_cnt], ":=") != 0) {
         ERROR("set function: Fatal error expecting :=",
               data->string_board[data->programme_cnt]);
      }
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if(!reverse_polish(data)) {
         return error;
      }
      return pass;
   }
   return error;
}

state reverse_polish(parse* data)
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
   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   return reverse_polish(data);
}

state rotate_right(parse* data)
{
   if (strcmp(data->string_board[data->programme_cnt], MOVE_RIGHT) == 0) {
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if (!varnum(data->string_board[data->programme_cnt])) {
         ERROR("rotate_right function: Fatal error expecting <VARNUM>",
                              data->string_board[data->programme_cnt]);
      }
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      return pass;
   }
   return error;
}

state rotate_left(parse* data)
{
   if (strcmp(data->string_board[data->programme_cnt], MOVE_LEFT) == 0) {
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if (!varnum(data->string_board[data->programme_cnt])) {
         ERROR("rotate_left function: Fatal error expecting <VARNUM>",
                              data->string_board[data->programme_cnt]);
      }
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      return pass;
   }
   return error;
}

state move_forward(parse* data)
{
   if(strcmp(data->string_board[data->programme_cnt], MOVE_FORWARD) == 0) {
      data->programme_cnt = data->programme_cnt + NEXT_LINE;
      if (!varnum(data->string_board[data->programme_cnt])) {
         ERROR("move_forward function: Fatal error expecting <VARNUM>",
                              data->string_board[data->programme_cnt]);
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

state check_operator(char* symbol)
{
   if(strcmp(symbol, "+") == 0 || strcmp(symbol, "-") == 0 ||
      strcmp(symbol, "*") == 0 || strcmp(symbol, "/") == 0) {
         return pass;
      }
   return error;
}

state check_variable(char* variable)
{
   if(isupper(variable[0]) && strlen(variable) == ONE_CHARACTER) {
      return pass;
   }
   return error;
}
/* ########## FUNCTION FOR DYNAMIC MEMORY ALLOCATION AND FREEING ########### */
parse* initialise_parse()
{
   int x;
   parse* data;

   data = (parse*) malloc(sizeof(parse));
   if (data == NULL) {
      ON_ERROR("Failed to create parse node\n");
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

   data->programme_cnt = INITIALISE_INTEGER;

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
