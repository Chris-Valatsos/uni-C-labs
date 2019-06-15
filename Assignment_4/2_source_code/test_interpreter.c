#include "../1_external_libraries/interpreter.h"
/* ######################################################################### */
void test_all();
void test_equal_float();
void test_push_stack();
void test_pop_stack();
void test_check_calculation();
void test_compute_operation();
void test_compute_reverse_polish();
void test_reverse_polish();
void test_set();
void test_set_variable();
void test_normal_and_reverse_loop();
void test_do_loop();
void test_move_forward();
void test_parse_main();

int main(void)
{
   printf("\nStart Tests\n\n");

   test_all();

   printf("Tests Completed\n");
   return EXIT_SUCCESS;
}

void test_all()
{
   test_equal_float();
   test_push_stack();
   test_pop_stack();
   test_check_calculation();
   test_compute_operation();
   test_reverse_polish();
   test_set();
   test_set_variable();
   test_normal_and_reverse_loop();
   test_do_loop();
   test_move_forward();
   test_parse_main();
}

void test_equal_float()
{
   assert(equal_float(3.2, 3.2) == pass);
   assert(equal_float(0.45, 0.46) == error);
   assert(equal_float(5.4, 5.4) == pass);
   assert(equal_float(7.4, 4.7) == error);
   assert(equal_float(8, 8.0) == pass);
   assert(equal_float(-5.2, -5.2) == pass);
   assert(equal_float(-2.1, -2.0) == error);
   assert(equal_float(49.8, 49.8) == pass);
   assert(equal_float(4.6, -4.6) == error);
   assert(equal_float(62.3 + (-2.3), 60.0) == pass);
   assert(equal_float(0.0, 0.1) == error);

   printf("test_equal_float() completed\n\n");
}

void test_push_stack()
{
   stack top = NULL;

   push_stack(&top, atof("50.0"));
   assert(equal_float(top->input, 50.0) == pass);

   push_stack(&top, atof("-32.5"));
   assert(equal_float(top->input, -32.5) == pass);

   push_stack(&top, atof("-90.8"));
   assert(equal_float(top->input, 90.8) == error);

   push_stack(&top, atof("-1.0"));
   assert(equal_float(top->input, -1.1) == error);

   free_stack(top);

   printf("test_push_stack() completed\n\n");
}

void test_pop_stack()
{
   stack top = NULL;

   push_stack(&top, atof("50.0"));
   assert(equal_float(top->input, 50.0) == pass);
   assert(top != NULL);
   assert(equal_float(pop_stack(&top), 50.0) == pass);
   assert(top == NULL);

   push_stack(&top, atof("36.8"));
   push_stack(&top, atof("-12.5"));
   assert(equal_float(pop_stack(&top), -12.5) == pass);
   assert(equal_float(pop_stack(&top), 36.8) == pass);
   assert(top == NULL);

   free_stack(top);

   printf("test_pop_stack() completed\n\n");
}

void test_check_calculation()
{
   assert(check_calculation('+') == TRUE_OPERAT);
   assert(check_calculation('%') == MAX_LIMIT);
   assert(check_calculation('-') == TRUE_OPERAT);
   assert(check_calculation('&') == MAX_LIMIT);
   assert(check_calculation('*') == TRUE_OPERAT);
   assert(check_calculation('~') == MAX_LIMIT);
   assert(check_calculation('/') == TRUE_OPERAT);
   assert(check_calculation('=') == MAX_LIMIT);

   printf("test_check_calculation() completed\n\n");
}

void test_compute_operation()
{
   stack top = NULL;
   /* Push the first two numbers into an empty stack and increase its size */
   push_stack(&top, atof("5.6"));
   push_stack(&top, atof("1.6"));
   /* Pop the given data and subtract them. Push the result back to the stack */
   push_stack(&top, compute_operation(&top, '-'));
   assert(equal_float(top->input, 4) == pass);
   push_stack(&top, atof("9.5"));
   /* Perform 4 + 9.5 and push result into the stack */
   push_stack(&top, compute_operation(&top, '+'));
   assert(equal_float(top->input, 13.5) == pass);
   push_stack(&top, atof("4.5"));
   /* Perform 13.5 / 4.5 and push result into the stack */
   push_stack(&top, compute_operation(&top, '/'));
   assert(equal_float(top->input, 3) == pass);
   push_stack(&top, atof("5"));
   /* Perform 3 * 5 and push result into the stack */
   push_stack(&top, compute_operation(&top, '*'));
   assert(equal_float(top->input, 15) == pass);
   push_stack(&top, atof("15"));
   /* Perform 15 - 15 and push result into the stack */
   push_stack(&top, compute_operation(&top, '-'));
   assert(equal_float(top->input, 0) == pass);

   push_stack(&top, atof("14"));
   push_stack(&top, atof("5"));
   push_stack(&top, atof("10"));
   push_stack(&top, compute_operation(&top, '+'));
   push_stack(&top, compute_operation(&top, '*'));
   assert(equal_float(top->input, 210) == pass);
   push_stack(&top, atof("16"));
   push_stack(&top, atof("2"));
   push_stack(&top, atof("7"));
   push_stack(&top, compute_operation(&top, '*'));
   push_stack(&top, compute_operation(&top, '+'));
   push_stack(&top, compute_operation(&top, '/'));
   assert(equal_float(top->input, 7) == pass);
   push_stack(&top, atof("7"));
   push_stack(&top, compute_operation(&top, '-'));
   assert(equal_float(top->input, 0) == pass);

   free_stack(top);

   printf("test_compute_operation() completed\n\n");
}

void test_compute_reverse_polish()
{
   parse* data;
   stack top;

   data = initialise_parse();
   top = NULL;
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "5");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 5) == pass);
   assert(data->stack_size == 1);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[1], "4");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 4) == pass);
   assert(data->stack_size == 2);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[2], "+");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 9) == pass);
   assert(data->stack_size == 1);
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   data->variables[0] = 2;
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "A");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 2) == pass);
   assert(data->stack_size == 1);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[1], "5");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 5) == pass);
   assert(data->stack_size == 2);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[2], "+");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 7) == pass);
   assert(data->stack_size == 1);
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   data->variables[4] = 3;        /* E = 3 */
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "1");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 1) == pass);
   assert(data->stack_size == 1);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[1], "E");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 3) == pass);
   assert(data->stack_size == 2);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[2], "+");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 4) == pass);
   assert(data->stack_size == 1);
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   data->variables[3] = 20;        /* D = 20 */
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "D");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 20) == pass);
   assert(data->stack_size == 1);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[1], "10");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 10) == pass);
   assert(data->stack_size == 2);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[2], "*");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 200) == pass);
   assert(data->stack_size == 1);
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "B");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 0) == pass);
   assert(data->stack_size == 1);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[1], "3");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 3) == pass);
   assert(data->stack_size == 2);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[2], "+");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 3) == pass);
   assert(data->stack_size == 1);
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   data->variables[3] = 12;        /* D = 12 */
   data->variables[23] = 4;        /* X = 4 */
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "D");
   assert(compute_reverse_polish(data, &top));
   assert(equal_float(top->input, 12) == pass);
   assert(data->stack_size == 1);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[1], "8");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 8) == pass);
   assert(data->stack_size == 2);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[2], "-");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 4) == pass);
   assert(data->stack_size == 1);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[3], "X");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 4) == pass);
   assert(data->stack_size == 2);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[4], "/");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 1) == pass);
   assert(data->stack_size == 1);
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "10");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 10) == pass);
   assert(data->stack_size == 1);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[1], "50");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 50) == pass);
   assert(data->stack_size == 2);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[2], "!");
   assert(compute_reverse_polish(data, &top) == error);
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "5");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 5) == pass);
   assert(data->stack_size == 1);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[1], "5");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 5) == pass);
   assert(data->stack_size == 2);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[2], "&");
   assert(compute_reverse_polish(data, &top) == error);
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "24");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 24) == pass);
   assert(data->stack_size == 1);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[1], "8");
   assert(compute_reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 8) == pass);
   assert(data->stack_size == 2);

   data->programme_cnt = data->programme_cnt + NEXT_LINE;
   replicate_to_str(data->string_board[2], "~");
   assert(compute_reverse_polish(data, &top) == error);
   free(top);
   free_parse(data);

   printf("test_compute_reverse_polish() completed\n\n");
}

void test_reverse_polish()
{
   parse* data;
   stack top;

   data = initialise_parse();
   top = NULL;
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], ";");
   assert(reverse_polish(data, &top) == pass);
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "5");
   replicate_to_str(data->string_board[1], ";");
   assert(reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 5) == pass);
   assert(data->stack_size == 1);
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "4");
   replicate_to_str(data->string_board[1], "8");
   replicate_to_str(data->string_board[2], "*");
   replicate_to_str(data->string_board[3], ";");
   assert(reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 32) == pass);
   assert(data->stack_size == 1);
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   data->variables[5] = 6;         /* F = 6 */
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "2.5");
   replicate_to_str(data->string_board[1], "F");
   replicate_to_str(data->string_board[2], "-");
   replicate_to_str(data->string_board[3], ";");
   assert(reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, -3.5) == pass);
   assert(data->stack_size == 1);
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   data->variables[7] = 50;        /* H = 50 */
   data->variables[8] = 10;         /* I = 10 */
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "H");
   replicate_to_str(data->string_board[1], "I");
   replicate_to_str(data->string_board[2], "/");
   replicate_to_str(data->string_board[3], ";");
   assert(reverse_polish(data, &top) == pass);
   assert(equal_float(top->input, 5) == pass);
   assert(data->stack_size == 1);
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   data->variables[9] = 2;        /* J = 2 */
   data->variables[10] = 3;         /* K = 3 */
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "J");
   replicate_to_str(data->string_board[1], "k");
   replicate_to_str(data->string_board[2], "*");
   replicate_to_str(data->string_board[3], ";");
   assert(reverse_polish(data, &top) == error);;
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   data->variables[11] = 4;        /* L = 4 */
   data->variables[12] = 6;         /* M = 6 */
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "L");
   replicate_to_str(data->string_board[1], "-");
   replicate_to_str(data->string_board[2], "M");
   replicate_to_str(data->string_board[3], ";");
   assert(reverse_polish(data, &top) == error);;
   free(top);
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "-");
   replicate_to_str(data->string_board[1], "5");
   replicate_to_str(data->string_board[2], "2");
   replicate_to_str(data->string_board[3], ";");
   assert(reverse_polish(data, &top) == error);;
   free_parse(data);

   data = initialise_parse();
   top = NULL;
   assert(data->stack_size == 0);
   replicate_to_str(data->string_board[0], "6");
   replicate_to_str(data->string_board[1], "8");
   replicate_to_str(data->string_board[2], "%");
   replicate_to_str(data->string_board[3], ";");
   assert(reverse_polish(data, &top) == error);;
   free_parse(data);
   free_stack(top);

   printf("test_reverse_polish() completed\n\n");
}

void test_set()
{
   parse* data;

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "A");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "5");
   replicate_to_str(data->string_board[4], "9");
   replicate_to_str(data->string_board[5], "-");
   replicate_to_str(data->string_board[6], ";");
   assert(set(data) == pass);
   assert(data->stack_size == 1);
   assert(equal_float(data->variables[0], -4) == pass);
   free_parse(data);

   data = initialise_parse();
   data->variables[14] = 26;           /* O = 26 */
   data->variables[15] = 13;           /* Q = 13 */
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "D");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "O");
   replicate_to_str(data->string_board[4], "P");
   replicate_to_str(data->string_board[5], "/");
   replicate_to_str(data->string_board[6], ";");
   assert(set(data) == pass);
   assert(data->stack_size == 1);
   assert(equal_float(data->variables[3], 2) == pass);
   free_parse(data);

   data = initialise_parse();
   data->variables[5] = 24;            /* F = 24 */
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "F");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "F");
   replicate_to_str(data->string_board[4], "5");
   replicate_to_str(data->string_board[5], "-");
   replicate_to_str(data->string_board[6], ";");
   assert(set(data) == pass);
   assert(data->stack_size == 1);
   assert(equal_float(data->variables[5], 19) == pass);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "N");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "26");
   replicate_to_str(data->string_board[4], "32");
   replicate_to_str(data->string_board[5], "+");
   replicate_to_str(data->string_board[6], ";");
   assert(set(data) == pass);
   assert(data->stack_size == 1);
   assert(equal_float(data->variables[13], 58) == pass);
   free_parse(data);

   data = initialise_parse();
   data->variables[23] = 2;            /* X = 2 */
   data->variables[24] = 3;            /* Y = 3 */
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "X");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "X");
   replicate_to_str(data->string_board[4], "Y");
   replicate_to_str(data->string_board[5], "2");
   replicate_to_str(data->string_board[6], "-");
   replicate_to_str(data->string_board[7], "/");
   replicate_to_str(data->string_board[8], "1");
   replicate_to_str(data->string_board[9], "3");
   replicate_to_str(data->string_board[10], "Y");
   replicate_to_str(data->string_board[11], "+");
   replicate_to_str(data->string_board[12], "*");
   replicate_to_str(data->string_board[13], "-");
   replicate_to_str(data->string_board[14], ";");
   assert(set(data) == pass);
   assert(data->stack_size == 1);
   assert(equal_float(data->variables[23], -4) == pass);   /* X = -4 */
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "A");
   replicate_to_str(data->string_board[2], "=");
   assert(set(data) == error);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "F5");
   assert(set(data) == error);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "F");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "5");
   replicate_to_str(data->string_board[4], "/");;
   replicate_to_str(data->string_board[5], ";");
   assert(set(data) == error);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "X");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "-");
   assert(set(data) == error);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "J");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "6");
   replicate_to_str(data->string_board[4], "9");
   replicate_to_str(data->string_board[5], "*");
   replicate_to_str(data->string_board[6], ":");
   assert(set(data) == error);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "G");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "4");
   replicate_to_str(data->string_board[4], "/");
   replicate_to_str(data->string_board[5], "7");
   replicate_to_str(data->string_board[6], ";");
   assert(set(data) == error);
   free_parse(data);

   printf("test_set() completed\n\n");
}

void test_set_variable()
{
   parse* data;

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "-22");
   assert((set_variable(data) == -22) == pass);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "65");
   assert((set_variable(data) == 65) == pass);
   free_parse(data);

   data = initialise_parse();
   data->variables[25] = 41;           /* Z = 41 */
   replicate_to_str(data->string_board[0], "Z");
   assert((set_variable(data) == 41) == pass);
   free_parse(data);

   data = initialise_parse();
   data->variables[5] = -37;           /* F = -37 */
   replicate_to_str(data->string_board[0], "F");
   assert((set_variable(data) == -37) == pass);
   free_parse(data);

   data = initialise_parse();
   data->variables[6] = 67;           /* G = 67 */
   replicate_to_str(data->string_board[2], "B");
   assert((set_variable(data) == 67) == error);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "22");
   assert((set_variable(data) == -22) == error);
   free_parse(data);

   printf("test_set_variable() completed\n\n");
}

void test_normal_and_reverse_loop()
{
   parse* data;

   data = initialise_parse();
   data->variables[7] = 2;   /* G = 2 */
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "V");
   replicate_to_str(data->string_board[2], "}");
   assert(normal_and_reverse_loop(data, 7, 2) == pass); /* G (data->variables[7]) from 7 to 2 */
   assert(equal_float(data->variables[7], 2) == pass); /* G == 2 */
   free_parse(data);

   data = initialise_parse();
   data->variables[2] = 6;   /* C = 6 */
   replicate_to_str(data->string_board[0], "LT");
   replicate_to_str(data->string_board[1], "35");
   replicate_to_str(data->string_board[2], "}");
   assert(normal_and_reverse_loop(data, 2, 6) == pass);  /* B (data->variables[1]) from 2 up to 6 */
   assert(equal_float(data->variables[2], 6) == pass);  /* B == 5 */
   free_parse(data);

   data = initialise_parse();
   data->variables[4] = 6;   /* E = 6 */
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "20");
   replicate_to_str(data->string_board[2], "}");
   assert(normal_and_reverse_loop(data, 4, 1) == pass); /* E (data->variables[4]) from 6 to 1 */
   assert(equal_float(data->variables[4], 1) == pass); /* E == 1 */
   free_parse(data);

   data = initialise_parse();
   data->variables[18] = 21;   /* S = 21 */
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "20");
   replicate_to_str(data->string_board[2], "}");
   assert(normal_and_reverse_loop(data, 18, 53) == pass); /* S (data->variables[18]) from 21 to 53 */
   assert(equal_float(data->variables[18], 53) == pass); /* S == 3 */
   free_parse(data);

   data = initialise_parse();
   data->variables[20] = -15;   /* U = -15 */
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "25");
   replicate_to_str(data->string_board[2], "FD");
   replicate_to_str(data->string_board[3], "65");
   replicate_to_str(data->string_board[4], "}");
   assert(normal_and_reverse_loop(data, 20, -50) == pass); /* U (data->variables[20]) from -15 to -50 */
   assert(equal_float(data->variables[20], -50) == pass); /* U == -15 */
   free_parse(data);

   data = initialise_parse();
   data->variables[3] = 4;   /* D = 4 */
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "55");
   replicate_to_str(data->string_board[2], "{");
   assert(normal_and_reverse_loop(data, 3, 6) == error); /* D (data->variables[3]) from41 to 6 */
   assert(equal_float(data->variables[3], 4));           /* D == 4 */
   free_parse(data);

   data = initialise_parse();
   data->variables[15] = -2;   /* P = -2 */
   replicate_to_str(data->string_board[0], "LT");
   replicate_to_str(data->string_board[1], "20");
   replicate_to_str(data->string_board[2], ";");
   assert(normal_and_reverse_loop(data, 15, -24) == error); /* P (data->variables[15]) from -2 to -24 */
   assert(equal_float(data->variables[15], -2));            /* P == -2 */
   free_parse(data);

   data = initialise_parse();
   data->variables[13] = 5;   /* N = 5 */
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "0");
   replicate_to_str(data->string_board[2], "{");
   assert(normal_and_reverse_loop(data, 13, -12) == error); /* N (data->variables[13]) from 5 to -12 */
   assert(equal_float(data->variables[13], 5));              /* N == 1 */
   free_parse(data);

   printf("test_normal_and_reverse_loop() completed\n\n");
}

void test_do_loop()
{
   parse* data;

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "B");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "10");
   replicate_to_str(data->string_board[6], "{");
   replicate_to_str(data->string_board[7], "}");
   assert(do_loop(data) == pass);
   assert(equal_float(data->variables[1], 10) == pass);
   free_parse(data);

   data = initialise_parse();
   data->variables[2] = 0;      /* C = 1 */
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "C");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "C");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "12");
   replicate_to_str(data->string_board[6], "{");
   replicate_to_str(data->string_board[7], "FD");
   replicate_to_str(data->string_board[8], "30");
   replicate_to_str(data->string_board[9], "}");
   assert(do_loop(data) == pass);
   assert(equal_float(data->variables[2], 12) == pass);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "D");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "10");
   replicate_to_str(data->string_board[6], "{");
   replicate_to_str(data->string_board[7], "SET");
   replicate_to_str(data->string_board[8], "E");
   replicate_to_str(data->string_board[9], ":=");
   replicate_to_str(data->string_board[10], "D");
   replicate_to_str(data->string_board[11], "5.5");
   replicate_to_str(data->string_board[12], "*");
   replicate_to_str(data->string_board[13], ";");
   replicate_to_str(data->string_board[14], "}");
   assert(do_loop(data) == pass);
   assert(equal_float(data->variables[3], 10) == pass);
   assert(equal_float(data->variables[4], 55) == pass);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "F");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "8");
   replicate_to_str(data->string_board[6], "{");
   replicate_to_str(data->string_board[7], "RT");
   replicate_to_str(data->string_board[8], "35");
   replicate_to_str(data->string_board[9], "DO");
   replicate_to_str(data->string_board[10], "G");
   replicate_to_str(data->string_board[11], "FROM");
   replicate_to_str(data->string_board[12], "0");
   replicate_to_str(data->string_board[13], "TO");
   replicate_to_str(data->string_board[14], "20");
   replicate_to_str(data->string_board[15], "{");
   replicate_to_str(data->string_board[16], "FD");
   replicate_to_str(data->string_board[17], "10");
   replicate_to_str(data->string_board[18], "}");
   replicate_to_str(data->string_board[19], "}");
   assert(do_loop(data));
   assert(equal_float(data->variables[5], 8) == pass);
   assert(equal_float(data->variables[6], 20) == pass);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "5");
   assert(do_loop(data) == error);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "g");
   replicate_to_str(data->string_board[2], "FROM");
   assert(do_loop(data) == error);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "Y");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "r");
   assert(do_loop(data) == error);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "V");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "5");
   replicate_to_str(data->string_board[4], "to");
   assert(do_loop(data) == error);
   assert(equal_float(data->variables[21] , 5) == pass);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "C");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "4");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "k");
   assert(do_loop(data) == error);
   assert(equal_float(data->variables[2] , 4));
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "F");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "4");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "9");
   replicate_to_str(data->string_board[6], "}");
   assert(do_loop(data) == error);
   assert(equal_float(data->variables[5] , 4));
   free_parse(data);

   printf("test_do_loop() completed\n\n");
}

void test_move_forward()
{
   parse* data;

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "15.0");
   assert(move_forward(data) == pass);
   assert(equal_float(data->coords.x_coord[new][1],
   STARTING_HORIZONTAL_COORDINATES + (15 * cos(data->coords.rotation))) == pass);
   assert(equal_float(data->coords.y_coord[new][1],
   STARTING_VERTICAL_COORDINATES + (15 * sin(data->coords.rotation))) == pass);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "C");
   assert(move_forward(data) == pass);
   assert(equal_float(data->coords.x_coord[new][1],
   STARTING_HORIZONTAL_COORDINATES + (0 * cos(data->coords.rotation))) == pass);
   assert(equal_float(data->coords.y_coord[new][1],
   STARTING_VERTICAL_COORDINATES + (0 * sin(data->coords.rotation))) == pass);
   free_parse(data);

   data = initialise_parse();
   data->variables[5] = 35;
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "F");
   assert(move_forward(data) == pass);
   assert(equal_float(data->coords.x_coord[new][1],
   STARTING_HORIZONTAL_COORDINATES + (35 * cos(data->coords.rotation))) == pass);
   assert(equal_float(data->coords.y_coord[new][1],
   STARTING_VERTICAL_COORDINATES + (35 * sin(data->coords.rotation))) == pass);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "r");
   assert(move_forward(data) == error);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "FWS");
   assert(move_forward(data) == error);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "10");
   assert(move_forward(data) == error);
   free_parse(data);

   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "-96-");
   assert(move_forward(data) == error);
   free_parse(data);

   printf("test_move_forward completed\n\n");
}

void test_parse_main()
{
   parse* data;

   /* Testing a correct input */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "{");
   replicate_to_str(data->string_board[1], "LT");
   replicate_to_str(data->string_board[2], "10");
   replicate_to_str(data->string_board[3], "}");
   assert(parse_main(data) == pass);
   free_parse(data);

   /* Testing correct inputs */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "{");
   replicate_to_str(data->string_board[1], "RT");
   replicate_to_str(data->string_board[2], "15");
   replicate_to_str(data->string_board[3], "FD");
   replicate_to_str(data->string_board[4], "30");
   replicate_to_str(data->string_board[5], "}");
   assert(parse_main(data) == pass);
   free_parse(data);

   /* Testing correct inputs */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "{");
   replicate_to_str(data->string_board[1], "DO");
   replicate_to_str(data->string_board[2], "X");
   replicate_to_str(data->string_board[3], "FROM");
   replicate_to_str(data->string_board[4], "0");
   replicate_to_str(data->string_board[5], "TO");
   replicate_to_str(data->string_board[6], "5");
   replicate_to_str(data->string_board[7], "{");
   replicate_to_str(data->string_board[8], "SET");
   replicate_to_str(data->string_board[9], "A");
   replicate_to_str(data->string_board[10], ":=");
   replicate_to_str(data->string_board[11], "B");
   replicate_to_str(data->string_board[12], "6.5");
   replicate_to_str(data->string_board[13], "+");
   replicate_to_str(data->string_board[14], ";");
   replicate_to_str(data->string_board[15], "RT");
   replicate_to_str(data->string_board[16], "15");
   replicate_to_str(data->string_board[17], "FD");
   replicate_to_str(data->string_board[18], "30");
   replicate_to_str(data->string_board[19], "}");
   replicate_to_str(data->string_board[20], "}");
   assert(parse_main(data) == pass);
   free_parse(data);

   /* Testing correct inputs */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "{");
   replicate_to_str(data->string_board[1], "DO");
   replicate_to_str(data->string_board[2], "X");
   replicate_to_str(data->string_board[3], "FROM");
   replicate_to_str(data->string_board[4], "0");
   replicate_to_str(data->string_board[5], "TO");
   replicate_to_str(data->string_board[6], "5");
   replicate_to_str(data->string_board[7], "{");
   replicate_to_str(data->string_board[8], "RT");
   replicate_to_str(data->string_board[9], "15");
   replicate_to_str(data->string_board[10], "FD");
   replicate_to_str(data->string_board[11], "30");
   replicate_to_str(data->string_board[12], "}");
   replicate_to_str(data->string_board[13], "}");
   assert(parse_main(data) == pass);
   free_parse(data);

   /* Testing correct inputs */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "{");
   replicate_to_str(data->string_board[1], "DO");
   replicate_to_str(data->string_board[2], "X");
   replicate_to_str(data->string_board[3], "FROM");
   replicate_to_str(data->string_board[4], "0");
   replicate_to_str(data->string_board[5], "TO");
   replicate_to_str(data->string_board[6], "15");
   replicate_to_str(data->string_board[7], "{");
   replicate_to_str(data->string_board[8], "RT");
   replicate_to_str(data->string_board[9], "10");
   replicate_to_str(data->string_board[10], "LT");
   replicate_to_str(data->string_board[11], "15");
   replicate_to_str(data->string_board[12], "DO");
   replicate_to_str(data->string_board[13], "Y");
   replicate_to_str(data->string_board[14], "FROM");
   replicate_to_str(data->string_board[15], "0");
   replicate_to_str(data->string_board[16], "TO");
   replicate_to_str(data->string_board[17], "5");
   replicate_to_str(data->string_board[18], "{");
   replicate_to_str(data->string_board[19], "SET");
   replicate_to_str(data->string_board[20], "Z");
   replicate_to_str(data->string_board[21], ":=");
   replicate_to_str(data->string_board[22], "F");
   replicate_to_str(data->string_board[23], "3.5");
   replicate_to_str(data->string_board[24], "-");
   replicate_to_str(data->string_board[25], ";");
   replicate_to_str(data->string_board[26], "RT");
   replicate_to_str(data->string_board[27], "15");
   replicate_to_str(data->string_board[28], "FD");
   replicate_to_str(data->string_board[29], "30");
   replicate_to_str(data->string_board[30], "}");
   replicate_to_str(data->string_board[31], "}");
   replicate_to_str(data->string_board[32], "}");
   assert(parse_main(data) == pass);
   free_parse(data);

   /* Testing an input with an unbalanced SET */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "{");
   replicate_to_str(data->string_board[1], "SET");
   replicate_to_str(data->string_board[2], "X");
   replicate_to_str(data->string_board[3], ":=");
   replicate_to_str(data->string_board[4], "X");
   replicate_to_str(data->string_board[5], "*");
   replicate_to_str(data->string_board[6], "4");
   replicate_to_str(data->string_board[7], "g");
   replicate_to_str(data->string_board[8], "}");
   assert(parse_main(data) == error);
   free_parse(data);

   /* Testing an input with a error varnum */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "{");
   replicate_to_str(data->string_board[1], "RT");
   replicate_to_str(data->string_board[2], "f");
   replicate_to_str(data->string_board[3], "}");
   assert(parse_main(data) == error);
   free_parse(data);

   /* Testing an input without an opening bracket */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "X");
   replicate_to_str(data->string_board[2], "}");
   assert(parse_main(data) == error);
   free_parse(data);

   /* Testing an input with an extra opening bracket */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "{");
   replicate_to_str(data->string_board[1], "RT");
   replicate_to_str(data->string_board[2], "10");
   replicate_to_str(data->string_board[3], "{");
   replicate_to_str(data->string_board[4], "}");
   assert(parse_main(data) == error);
   free_parse(data);

   /* Testing an input with a error varnum in the DO loop */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "{");
   replicate_to_str(data->string_board[1], "DO");
   replicate_to_str(data->string_board[2], "X");
   replicate_to_str(data->string_board[3], "FROM");
   replicate_to_str(data->string_board[4], "0");
   replicate_to_str(data->string_board[5], "TO");
   replicate_to_str(data->string_board[6], "t");
   replicate_to_str(data->string_board[7], "{");
   replicate_to_str(data->string_board[8], "RT");
   replicate_to_str(data->string_board[9], "10");
   replicate_to_str(data->string_board[10], "FD");
   replicate_to_str(data->string_board[11], "30");
   replicate_to_str(data->string_board[12], "}");
   replicate_to_str(data->string_board[13], "}");
   assert(parse_main(data) == error);
   free_parse(data);

   /* Testing an input without a closing bracket */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "{");
   replicate_to_str(data->string_board[1], "FD");
   replicate_to_str(data->string_board[2], "50");
   assert(parse_main(data) == error);
   free_parse(data);

   /* Testing an input with an unbalanced SET */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "{");
   replicate_to_str(data->string_board[1], "DO");
   replicate_to_str(data->string_board[2], "X");
   replicate_to_str(data->string_board[3], "FROM");
   replicate_to_str(data->string_board[4], "0");
   replicate_to_str(data->string_board[5], "TO");
   replicate_to_str(data->string_board[6], "5");
   replicate_to_str(data->string_board[7], "{");
   replicate_to_str(data->string_board[8], "RT");
   replicate_to_str(data->string_board[9], "25");
   replicate_to_str(data->string_board[10], "SET");
   replicate_to_str(data->string_board[11], ";");
   replicate_to_str(data->string_board[12], "}");
   replicate_to_str(data->string_board[13], "}");
   assert(parse_main(data) == error);
   free_parse(data);

   /* Testing an input without a semicolon at the end */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "{");
   replicate_to_str(data->string_board[1], "SET");
   replicate_to_str(data->string_board[2], "X");
   replicate_to_str(data->string_board[3], ":=");
   replicate_to_str(data->string_board[4], "5");
   replicate_to_str(data->string_board[5], "{");
   replicate_to_str(data->string_board[6], "}");
   assert(parse_main(data) == error);
   free_parse(data);

   printf("test_parse_main() completed\n\n");
}
/* ######################################################################### */
