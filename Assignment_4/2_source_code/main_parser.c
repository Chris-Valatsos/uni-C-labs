#include "../1_external_libraries/parser.h"
/* ######################################################################### */
int main(int argc, char* argv[])
{
   parse* data;
   FILE* file_ptr;
   char inputfile[SIZE_OF_FILENAME];

   if(!read_inputfile(argc, argv, inputfile)){
      ON_ERROR("Failed to read and open the inputfile\n");
   }

   file_ptr = fopen(inputfile, "r");
   if (file_ptr == NULL) {
      ON_ERROR("Failed to open inputfile pointer\n");
   }
   data = initialise_parse();

   /* scan file */
   while((fscanf(file_ptr, "%s", data->string_board[data->programme_cnt++]) ==
                     ONE_ITEM_SCANNED) && data->programme_cnt < TOKEN_NUMBER);

   if(TOKEN_NUMBER <= data->programme_cnt) {
      free_parse(data);
      ON_ERROR("Please incease the #define TOKEN_NUMBER\n");
   }

   data->programme_cnt = INITIALISE_INTEGER;
   if(!parse_main(data)) {
      free_parse(data);
      fprintf(stderr, "Failed to perform parsing correctly for the"\
                                          " file %s\n", inputfile);
      exit(EXIT_FAILURE);
   }

   free_parse(data);
   fclose(file_ptr);

   printf("Successfully parsed the file: %s\n", inputfile);
   return EXIT_SUCCESS;
}
/* ######################################################################### */
