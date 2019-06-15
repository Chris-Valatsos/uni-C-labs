/* ############################## #INCLUDES ################################ */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
/* ############################### #DEFINES ################################ */
#define TOKEN_NUMBER 128
#define SIZE_OF_TOKEN 7
#define SIZE_OF_FILENAME 128
#define TWO_ARGUMENTS 2
#define ONE_ITEM_SCANNED 1
#define DOT_CHAR '.'
#define MINUS_SIGN '-'
#define OPENING_BRACKET "{"
#define CLOSING_BRACKET "}"
#define NEXT_LINE 1
#define ONE_CHARACTER 1
#define INITIALISE_INTEGER 0
#define MOVE_FORWARD "FD"       /* String used for the <FD> instruction */
#define MOVE_LEFT "LT"          /* String used for the <LT> instruction */
#define MOVE_RIGHT "RT"         /* String used for the <RT> instruction */
#define SEMICOLON ";"           /* String used for the <POLISH> instruction */
#define SET_INSTRUCTION "SET"   /* String used for the <SET> instruction */
#define DO_INSTRUCTION "DO"     /* String used for the <DO> instruction */
#define FROM_INSTRUCTION "FROM" /* String used for the <FROM> instruction */
#define TO_INSTRUCTION "TO"     /* String used for the <TO> instruction */
#define replicate_to_str(A, B) strcpy(A, B)

#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)
#define ERROR(STR, RESULT) {fprintf(stderr,"%s but got %s\n", \
                                 STR, RESULT); return error; }
/* ############################# ENUMERATIONS ############################## */
enum state {error, pass};
typedef enum state state;
/* ############################# #STRUCTURES ############################### */
struct parse {
   char** string_board;
   int programme_cnt;
};
typedef struct parse parse;
/* ############################## #FUNCTIONS ############################### */
/* Ensures that the arguments in the command line will be read correctly.
   return pass if successfull or returns fail if an error is encountered */
state read_inputfile(int argc, char* argv[], char* fname);

/* Parsing the instruction <MAIN> and return pass if
   successfull or returns fail if an error is encountered */
state parse_main(parse* data);

/* Parsing the instruction <INSTRCTLST> and return pass if
   successfull or returns fail if an error is encountered */
state instrctlst(parse* data);

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
state reverse_polish(parse* data);

/* Parsing the instruction <RT> and return pass if successfull
   or returns fail if an error is encountered */
state rotate_right(parse* data);

/* Parsing the instruction <LT> and return pass if successfull
   or returns fail if an error is encountered */
state rotate_left(parse* data);

/* Parsing the instruction <FD> and return pass if successfull
   or returns fail if an error is encountered */
state move_forward(parse* data);

/* Checks the variable and returns pass when the symbol confronts with the
   formal grammar or returns fail if an error is encountered */
state varnum(char* symbol);

/* Checks the variable and returns pass when the symbol confronts with the
   formal grammar or returns fail if an error is encountered */
state check_variable(char* variable);

/* Checks the operator and returns pass when the symbol confronts with the
   formal grammar or returns fail if an error is encountered */
state check_operator(char* symbol);

/* Creates dynamically allocated memory */
parse* initialise_parse();

/* Frees dynamically allocated memory */
void free_parse(parse* data);
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
