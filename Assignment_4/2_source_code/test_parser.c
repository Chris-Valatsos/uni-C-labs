#include "../1_external_libraries/parser.h"
/* ######################################################################### */
void test_all();
void test_check_operator();
void test_check_variable();
void test_varnum();
void test_move_forward();
void test_rotate_left();
void test_rotate_right();
void test_reverse_polish();
void test_set();
void test_do_loop();
void test_instruction();
void test_instrctlst();
void test_parse_main();

int main(void) {
   printf("\nStart Tests\n\n");

   test_all();

   printf("Tests Completed\n");
   return EXIT_SUCCESS;
}

void test_all()
{
   test_check_operator();
   test_check_variable();
   test_varnum();
   test_move_forward();
   test_rotate_left();
   test_rotate_right();
   test_reverse_polish();
   test_set();
   test_do_loop();
   test_instruction();
   test_instrctlst();
   test_parse_main();
}

void test_check_operator()
{
   assert(check_operator("+") == pass);
   assert(check_operator("&") == error);
   assert(check_operator("-") == pass);
   assert(check_operator("'") == error);
   assert(check_operator("R") == error);
   assert(check_operator("*") == pass);
   assert(check_operator("|") == error);
   assert(check_operator("/") == pass);


   printf("test_check_operator() completed\n\n");
}

void test_check_variable()
{
   assert(check_variable("Z") == pass);
   assert(check_variable("b") == error);
   assert(check_variable("D") == pass);
   assert(check_variable("DD") == error);
   assert(check_variable("F") == pass);
   assert(check_variable("4") == error);
   assert(check_variable("W") == pass);
   assert(check_variable("4d") == error);
   assert(check_variable("V") == pass);
   assert(check_variable("s9") == error);

   printf("test_check_variable() completed\n\n");
}

void test_varnum()
{
   assert(varnum("1") == pass);
   assert(varnum("+") == error);
   assert(varnum("45") == pass);
   assert(varnum("-") == error);
   assert(varnum("52.3") == pass);
   assert(varnum("*") == error);
   assert(varnum("6.5") == pass);
   assert(varnum("/") == error);
   assert(varnum("-85") == pass);
   assert(varnum("&") == error);
   assert(varnum("-36.5") == pass);
   assert(varnum("DF") == error);
   assert(varnum("F") == pass);
   assert(varnum("n") == error);
   assert(varnum("S") == pass);
   assert(varnum("4R") == error);
   assert(varnum("-0.5") == pass);
   assert(varnum("F5") == error);
   assert(varnum("5.4") == pass);
   assert(varnum("vv") == error);
   assert(varnum("7.0") == pass);
   assert(varnum("5.3.4.8") == error);
   assert(varnum("25.8") == pass);
   assert(varnum("--25") == error);
   assert(varnum("D") == pass);
   assert(varnum("50--") == error);
   assert(varnum("Z") == pass);
   assert(varnum("-25-") == error);

   printf("test_varnum() completed\n\n");
}

void test_move_forward()
{
   parse* data;

   /* Testing a correct FD instruction input with a number */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "35.4");
   assert(move_forward(data) == pass);
   free_parse(data);

   /* Testing a error varnum input */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "e3");
   assert(move_forward(data) == error);
   free_parse(data);

   /* Testing a correct FD instruction input with a character */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "V");
   assert(move_forward(data) == pass);
   free_parse(data);

   /* Testing a error varnum input */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "EWQD");
   assert(move_forward(data) == error);
   free_parse(data);

   /* Testing a error varnum input */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "f");
   assert(move_forward(data) == error);
   free_parse(data);

   /* Testing a error varnum input */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "3.2.");
   assert(move_forward(data) == error);
   free_parse(data);

   /* Testing a error instruction and varnum input */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "LT");
   replicate_to_str(data->string_board[1], "d3");
   assert(move_forward(data) == error);
   free_parse(data);

   printf("test_move_forward() completed\n\n");
}

void test_rotate_left()
{
   parse* data;

   /* Testing a correct FD instruction input with a number */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "LT");
   replicate_to_str(data->string_board[1], "-20");
   assert(rotate_left(data) == pass);
   free_parse(data);

   /* Testing a error varnum input */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "LT");
   replicate_to_str(data->string_board[1], "DEQS");
   assert(rotate_left(data) == error);
   free_parse(data);

   /* Testing a correct FD instruction input with a character */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "LT");
   replicate_to_str(data->string_board[1], "X");
   assert(rotate_left(data) == pass);
   free_parse(data);

   /* Testing a error varnum input */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "LT");
   replicate_to_str(data->string_board[1], "f");
   assert(rotate_left(data) == error);
   free_parse(data);

   /* Testing a error instruction input */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], " ");
   replicate_to_str(data->string_board[1], "10");
   assert(rotate_left(data) == error);
   free_parse(data);

   /* Testing a error varnum input */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "d");
   assert(rotate_left(data) == error);
   free_parse(data);

   printf("test_rotate_left() completed\n\n");
}

void test_rotate_right()
{
   parse* data;

   /* Testing a correct FD instruction input with a number */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "20.5");
   assert(rotate_right(data) == pass);
   free_parse(data);

   /* Testing a correct FD instruction input with a character */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "X");
   assert(rotate_right(data) == pass);
   free_parse(data);

   /* Testing a correct FD instruction input with a number */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "-14");
   assert(rotate_right(data) == pass);
   free_parse(data);
   /* Testing a error varnum input */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "e");
   assert(rotate_right(data) == error);
   free_parse(data);


   /* Testing a error varnum input */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "DQW");
   assert(rotate_right(data) == error);
   free_parse(data);

   /* Testing a error instruction input */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "80");
   assert(rotate_right(data) == error);
   free_parse(data);

   printf("test_rotate_right() completed\n\n");
}

void test_reverse_polish()
{
   parse* data;

   /* Testing a correct POLISH instruction input with just a semicolon */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], ";");
   assert(reverse_polish(data) == pass);
   free_parse(data);

   /* Testing a correct POLISH instruction input with a number and a semicolon */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "35");
   replicate_to_str(data->string_board[1], ";");
   assert(reverse_polish(data) == pass);
   free_parse(data);

   /* Testing a correct POLISH instruction input with a operand and a semicolon */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "-");
   replicate_to_str(data->string_board[1], ";");
   assert(reverse_polish(data) == pass);
   free_parse(data);

   /* Testing a correct POLISH instruction */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "F");
   replicate_to_str(data->string_board[1], "-");
   replicate_to_str(data->string_board[2], "5");
   replicate_to_str(data->string_board[3], "+");
   replicate_to_str(data->string_board[4], "2");
   replicate_to_str(data->string_board[5], ";");
   assert(reverse_polish(data) == pass);
   free_parse(data);

   /* Testing a correct POLISH instruction */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "C");
   replicate_to_str(data->string_board[1], "6");
   replicate_to_str(data->string_board[2], "+");
   replicate_to_str(data->string_board[3], ";");
   assert(reverse_polish(data) == pass);
   free_parse(data);

   /* Testing an input with an unbalanced reverse polish expression */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "D");
   replicate_to_str(data->string_board[1], "f");
   replicate_to_str(data->string_board[2], ";");
   assert(reverse_polish(data) == error);
   free_parse(data);

   /* Testing an input with a reverse polish expression that misses the
   semicolon at the end */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "C");
   replicate_to_str(data->string_board[1], "+");
   replicate_to_str(data->string_board[2], "4");
   replicate_to_str(data->string_board[3], "}");
   assert(reverse_polish(data) == error);
   free_parse(data);

   /* Testing an input with a error operator */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "B");
   replicate_to_str(data->string_board[1], "*");
   replicate_to_str(data->string_board[2], "4");
   replicate_to_str(data->string_board[3], "-");
   replicate_to_str(data->string_board[4], "&");
   replicate_to_str(data->string_board[5], ";");
   assert(reverse_polish(data) == error);
   free_parse(data);

   printf("test_reverse_polish() completed\n\n");
}

void test_set()
{
   parse* data;

   /* Testing a correct SET instruction */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "D");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "B");
   replicate_to_str(data->string_board[4], "+");
   replicate_to_str(data->string_board[5], "3");
   replicate_to_str(data->string_board[6], "*");
   replicate_to_str(data->string_board[7], "8");
   replicate_to_str(data->string_board[8], ";");
   assert(set(data) == pass);
   free_parse(data);

   /* Testing a correct SET instruction */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "A");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "B");
   replicate_to_str(data->string_board[4], "5.5");
   replicate_to_str(data->string_board[5], "+");
   replicate_to_str(data->string_board[6], ";");
   assert(set(data) == pass);
   free_parse(data);

   /* Testing an input with a error argument number */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "12");
   assert(set(data) == error);
   free_parse(data);

   /* Testing an input with a error argument number */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "z");
   assert(set(data) == error);
   free_parse(data);

   /* Testing an input with a error varnum */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "X");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "f");
   assert(set(data) == error);
   free_parse(data);

   /* Testing an input with a error reverse polish expression */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "X");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "Y");
   replicate_to_str(data->string_board[4], "+");
   replicate_to_str(data->string_board[5], " ");
   assert(set(data) == error);
   free_parse(data);

   /* Testing an input without an equal sign */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "B");
   replicate_to_str(data->string_board[2], "5");
   assert(set(data) == error);
   free_parse(data);

   printf("test_set() completed\n\n");
}

void test_do_loop()
{
   parse* data;

   /* Testing a correct DO instruction */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "A");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "5");
   replicate_to_str(data->string_board[6], "{");
   replicate_to_str(data->string_board[7], "RT");
   replicate_to_str(data->string_board[8], "X");
   replicate_to_str(data->string_board[9], "LT");
   replicate_to_str(data->string_board[10], "10");
   replicate_to_str(data->string_board[11], "}");
   assert(do_loop(data) == pass);
   free_parse(data);

   /* Testing a correct DO instruction */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "A");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "5");
   replicate_to_str(data->string_board[6], "{");
   replicate_to_str(data->string_board[7], "FD");
   replicate_to_str(data->string_board[8], "30");
   replicate_to_str(data->string_board[9], "}");
   assert(do_loop(data) == pass);
   free_parse(data);

   /* Testing a correct nested DO instruction */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "X");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "8");
   replicate_to_str(data->string_board[6], "{");
   replicate_to_str(data->string_board[7], "DO");
   replicate_to_str(data->string_board[8], "Y");
   replicate_to_str(data->string_board[9], "FROM");
   replicate_to_str(data->string_board[10], "0");
   replicate_to_str(data->string_board[11], "TO");
   replicate_to_str(data->string_board[12], "5");
   replicate_to_str(data->string_board[13], "{");
   replicate_to_str(data->string_board[14], "RT");
   replicate_to_str(data->string_board[15], "10");
   replicate_to_str(data->string_board[16], "}");
   replicate_to_str(data->string_board[17], "}");
   assert(do_loop(data) == pass);
   free_parse(data);

   /* Testing a correct nested DO instruction */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "X");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "8");
   replicate_to_str(data->string_board[6], "{");
   replicate_to_str(data->string_board[7], "SET");
   replicate_to_str(data->string_board[8], "A");
   replicate_to_str(data->string_board[9], ":=");
   replicate_to_str(data->string_board[10], "3");
   replicate_to_str(data->string_board[11], ";");
   replicate_to_str(data->string_board[12], "}");
   assert(do_loop(data) == pass);
   free_parse(data);

   /* Testing an input with a error argument number */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "X");
   replicate_to_str(data->string_board[2], "3");
   assert(do_loop(data) == error);
   free_parse(data);

   /* Testing an input with a error argument number */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "5");
   assert(do_loop(data) == error);
   free_parse(data);

   /* Testing an input with a error argument number */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "A");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "B");
   replicate_to_str(data->string_board[4], "4");
   assert(do_loop(data) == error);
   free_parse(data);

   /* Testing an input with a error argument number */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "A");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "r");
   assert(do_loop(data) == error);
   free_parse(data);

   /* Testing an input with a error argument number */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "A");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "5");
   replicate_to_str(data->string_board[6], ";");
   assert(do_loop(data) == error);
   free_parse(data);

   /* Testing an input with a error argument number */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "A");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "r");
   assert(do_loop(data) == error);
   free_parse(data);

   /* Testing an input with a error varnum input */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "A");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "5");
   replicate_to_str(data->string_board[6], "{");
   replicate_to_str(data->string_board[7], "LT");
   replicate_to_str(data->string_board[8], "s");
   assert(do_loop(data) == error);
   free_parse(data);

   /* Testing an input with a error closing bracket */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "L");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "5");
   replicate_to_str(data->string_board[6], "{");
   replicate_to_str(data->string_board[7], ";");
   assert(do_loop(data) == error);
   free_parse(data);

   /* Testing an input with a error instrcution */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "A");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "5");
   replicate_to_str(data->string_board[6], "{");
   replicate_to_str(data->string_board[7], "FD");
   replicate_to_str(data->string_board[8], "50");
   replicate_to_str(data->string_board[9], "30");
   replicate_to_str(data->string_board[10], "}");
   assert(do_loop(data) == error);
   free_parse(data);

   /* Testing an input with a error closing bracket */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "A");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "5");
   replicate_to_str(data->string_board[6], "{");
   replicate_to_str(data->string_board[7], "RT");
   replicate_to_str(data->string_board[8], "10");
   replicate_to_str(data->string_board[9], ";");
   assert(do_loop(data) == error);
   free_parse(data);

   printf("test_do_loop() completed\n\n");
}

void test_instruction()
{
   parse* data;

   /* Testing a correct INSTRUCTION */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "50");
   assert(instruction(data) == pass);
   free_parse(data);

   /* Testing a correct INSTRUCTION */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "LT");
   replicate_to_str(data->string_board[1], "15.5");
   assert(instruction(data) == pass);
   free_parse(data);

   /* Testing a correct INSTRUCTION */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "LT");
   replicate_to_str(data->string_board[1], "-25");
   assert(instruction(data) == pass);
   free_parse(data);

   /* Testing a correct INSTRUCTION */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "A");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "5");
   replicate_to_str(data->string_board[4], "+");
   replicate_to_str(data->string_board[5], "2");
   replicate_to_str(data->string_board[6], ";");
   assert(instruction(data) == pass);
   free_parse(data);

   /* Testing a correct INSTRUCTION */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "64.8");
   assert(instruction(data) == pass);
   free_parse(data);

   /* Testing an INSTRUCTION with a error varnum */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "FD");
   replicate_to_str(data->string_board[1], "VF");
   assert(instruction(data) == error);
   free_parse(data);

   /* Testing an INSTRUCTION with a error varnum */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "x");
   assert(instruction(data) == error);
   free_parse(data);

   /* Testing a error INSTRUCTION */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "f");
   assert(instruction(data) == error);
   free_parse(data);

   /* Testing an INSTRUCTION with a error varnum */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "LT");
   replicate_to_str(data->string_board[1], "5r");
   assert(instruction(data) == error);
   free_parse(data);

   /* Testing a error INSTRUCTION */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "A");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "5");
   replicate_to_str(data->string_board[4], "{");
   assert(instruction(data) == error);
   free_parse(data);

   printf("test_instruction() completed\n\n");
}

void test_instrctlst()
{
   parse* data;

   /* Testing a correct INSTRCTLST */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "X");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "5");
   replicate_to_str(data->string_board[4], ";");
   replicate_to_str(data->string_board[5], "}");
   assert(instrctlst(data) == pass);
   free_parse(data);

   /* Testing a correct INSTRCTLST */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "B");
   replicate_to_str(data->string_board[2], "LT");
   replicate_to_str(data->string_board[3], "-10");
   replicate_to_str(data->string_board[4], "FD");
   replicate_to_str(data->string_board[5], "-35");
   replicate_to_str(data->string_board[6], "}");
   assert(instrctlst(data) == pass);
   free_parse(data);

   /* Testing a correct INSTRCTLST */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "X");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "5");
   replicate_to_str(data->string_board[6], "{");
   replicate_to_str(data->string_board[7], "}");
   replicate_to_str(data->string_board[8], "}");
   assert(instrctlst(data) == pass);
   free_parse(data);

   /* Testing a correct INSTRCTLST */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "LT");
   replicate_to_str(data->string_board[1], "10");
   replicate_to_str(data->string_board[2], "}");
   assert(instrctlst(data) == pass);
   free_parse(data);

   /* Testing an INSTRCTLST with an unbalanced SET */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "X");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "}");
   assert(instrctlst(data) == error);
   free_parse(data);

   /* Testing an INSTRCTLST with a error varnum */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "RT");
   replicate_to_str(data->string_board[1], "4R");
   assert(instrctlst(data) == error);
   free_parse(data);

   /* Testing an INSTRCTLST with an unbalanced DO */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "DO");
   replicate_to_str(data->string_board[1], "X");
   replicate_to_str(data->string_board[2], "FROM");
   replicate_to_str(data->string_board[3], "0");
   replicate_to_str(data->string_board[4], "TO");
   replicate_to_str(data->string_board[5], "5");
   replicate_to_str(data->string_board[6], "{");
   replicate_to_str(data->string_board[7], "}");
   assert(instrctlst(data) == error);
   free_parse(data);

   /* Testing an INSTRCTLST with an unbalanced SET */
   data = initialise_parse();
   replicate_to_str(data->string_board[0], "SET");
   replicate_to_str(data->string_board[1], "X");
   replicate_to_str(data->string_board[2], ":=");
   replicate_to_str(data->string_board[3], "T");
   replicate_to_str(data->string_board[4], ";");
   assert(instrctlst(data) == error);
   free_parse(data);

   printf("test_instrctlst() completed\n\n");
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
