/* ############################## #INCLUDES ################################ */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <assert.h>
/* ############################### #DEFINES ################################ */
#define TOKEN_NUMBER 128
#define SIZE_OF_TOKEN 7
#define TRUE_OPERAT 2
#define SIZE_OF_FILENAME 128
#define TWO_ARGUMENTS 2
#define ONE_ITEM_SCANNED 1
#define DOT_CHAR '.'
#define MINUS_SIGN '-'
#define MAX_LIMIT 2879
#define STARTING_HORIZONTAL_COORDINATES 400
#define STARTING_VERTICAL_COORDINATES 300
#define STARTING_DIRECTION 270
#define SIZE_OF_VARIABLE_ARRAY 26/* Storing all variable letters from A to Z */
#define MAX_COORDS_STORED 2547
#define TURN_ANGLE 90
#define ANGLE_STEP 0.1
#define TWO_COORDS 2
#define M_ANGLE 180
#define OPENING_BRACKET "{"
#define CLOSING_BRACKET "}"
#define NEXT_LINE 1
#define ONE_CHARACTER 1
#define PREVIOUS_POSITION 1
#define RECTANGLE_SIDES 4
#define INITIALISE_INTEGER 0
#define MOVE_FORWARD "FD"       /* String used for the <FD> instruction */
#define MOVE_LEFT "LT"          /* String used for the <LT> instruction */
#define MOVE_RIGHT "RT"         /* String used for the <RT> instruction */
#define SEMICOLON ";"           /* String used for the <POLISH> instruction */
#define SET_INSTRUCTION "SET"   /* String used for the <SET> instruction */
#define DO_INSTRUCTION "DO"     /* String used for the <DO> instruction */
#define FROM_INSTRUCTION "FROM" /* String used for the <FROM> instruction */
#define TO_INSTRUCTION "TO"     /* String used for the <TO> instruction */
#define CHAR_A 'A'
#define replicate_to_str(A, B) strcpy(A, B)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)
#define ERROR(STR, RESULT) {fprintf(stderr,"%s but got %s\n", \
                                 STR, RESULT); return error; }

#define RECT "RECT"             /* String used for the <RECT> instruction */
#define ARC "ARC"               /* String used for the <ARC> instruction */
/* ############################# ENUMERATIONS ############################## */
enum state {error, pass};
typedef enum state state;

enum location {old, new};
typedef enum location loc;
/* ############################# #STRUCTURES ############################### */
struct thestack {
	float input;
	struct thestack* next;
};
typedef struct thestack* stack;

struct coordinates {
	float x_coord[TWO_COORDS][MAX_COORDS_STORED];
	float y_coord[TWO_COORDS][MAX_COORDS_STORED];
	float rotation;
	int coord_cnt;
};
typedef struct coordinates Coords;

struct parse {
	char** string_board;
	float variables[SIZE_OF_VARIABLE_ARRAY];
	int programme_cnt;
	int stack_size;
	Coords coords;
};
typedef struct parse parse;
/* ############################## #FUNCTIONS ############################### */
/* Ensures that the arguments in the command line will be read correctly.
   return pass if successfull or returns fail if an error is encountered */
state read_inputfile(int argc, char* argv[], char* inputfile);

/* Parsing the instruction <MAIN> and return pass if
   successfull or returns fail if an error is encountered */
state parse_main(parse *data);

/* Parsing the instruction <INSTRCTLST> and return pass if
   successfull or returns fail if an error is encountered */
state instrctlst(parse *data);

/* Parsing the instruction <INSTRUCTION> and return pass if
   successfull or returns fail if an error is encountered */
state instruction(parse* data);

/* Parsing the instruction <DO> and return pass if successfull
   or returns fail if an error is encountered */
state do_loop(parse* data);

/* Parsing the instruction <SET> and return pass if successfull
   or returns fail if an error is encountered */
state set(parse* data);

/* Parsing the instruction <POLISH> and return pass if successfull
   or returns fail if an error is encountered */
state reverse_polish(parse *data, stack *top);

/* Parsing the instruction <ARC> and return pass if successfull
or returns fail if an error is encountered */
state draw_arc(parse* data);

/* Set all the required coordinates for a rectangle */
void set_arc(parse* data, float angle, float radius);

/* Parsing the instruction <RECT> and return pass if successfull
   or returns fail if an error is encountered */
state draw_rectangle(parse* data);

/* Set all the required coordinates for an arc */
void set_rectagle(parse* data, float value);

/* Parsing the instruction <RT> and return pass if successfull
   or returns fail if an error is encountered */
state rotate_right(parse* data);

/* Parsing the instruction <LT> and return pass if successfull
   or returns fail if an error is encountered */
state rotate_left(parse* data);

/* Parsing the instruction <FD> and return pass if successfull
   or returns fail if an error is encountered */
state move_forward(parse* data);

/* Sets the next set of coordinates */
void get_next_coord(parse* data, float value);

/* Checks the variable and returns pass when the symbol confronts with the
   formal grammar or returns fail if an error is encountered */
state varnum(char* symbol);

/* Checks the variable and returns pass when the symbol confronts with the
   formal grammar or returns fail if an error is encountered */
state check_variable(char* variable);

/* Checks the operator and returns pass when the symbol confronts with the
   formal grammar or returns fail if an error is encountered */
state check_operator(char* symbol);

/* Checks which operand is used and returns the appropriate value */
int check_calculation(char operat);

/* Check the operand used and performs the respective calculation */
float compute_operation(stack *top, char operat);

/* Used to compare if two floats are equal */
state equal_float(float x, float y);

int compute_reverse_polish(parse *data, stack *top);

int set_variable(parse* data);
state normal_and_reverse_loop(parse* data, int initial_coords, int final_coords);

/* Functions to push and pop data from a stack */
void push_stack(stack* top, float result);
float pop_stack(stack* top);

/* Creates dynamically allocated memory */
parse* initialise_parse();

/* Frees dynamically allocated memory */
void free_parse(parse* data);
void free_stack(stack top);
/* ############################ FORMAL GRAMMAR ############################# */
/*
   <MAIN> ::= "{" <INSTRCTLST>
   <INSTRCTLST> ::= <INSTRUCTION><INSTRCTLST> |
                  "}"
   <INSTRUCTION> ::= <FD> |
                     <LT> |
                     <RT> |
                     <DO> |
                     <SET>
   <FD> ::= "FD" <VARNUM>
   <LT> ::= "LT" <VARNUM>
   <RT> ::= "RT" <VARNUM>
   <DO> ::= "DO" <VAR> "FROM" <VARNUM> "TO"
                  <VARNUM> "{" <INSTRCTLST>
   <VAR> ::= [A−Z]
   <VARNUM> ::= number | <VAR>
   <SET> ::= "SET" <VAR> ":=" <POLISH>
   <POLISH> ::= <OP> <POLISH> | <VARNUM> <POLISH> | ";"
   <OP> ::= "+" | "−" | "*" | "/"
*/
/* ######################################################################### */
