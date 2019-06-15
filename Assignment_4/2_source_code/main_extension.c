#include "../1_external_libraries/neillsdl2.h"
#include "../1_external_libraries/extension.h"
/* ######################################################################### */
int main(int argc, char* argv[])
{
   parse* data;
   FILE* file_ptr;
   char inputfile[SIZE_OF_FILENAME];
   SDL_Simplewin sw;
   int location;

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
   fclose(file_ptr);

   Neill_SDL_Init(&sw);
   for(location = 0; location <= data->coords.coord_cnt; location++) {
      SDL_Delay(2);
      /* Selecting random colours for each line that is printed using SDL */
      Neill_SDL_SetDrawColour(&sw, rand()%SDL_8BITCOLOUR,
                                   rand()%SDL_8BITCOLOUR,
                                   rand()%SDL_8BITCOLOUR);
      /* Drawing a line on the following coordinates using the rendering
         features of SDL*/
      SDL_RenderDrawLine(sw.renderer, data->coords.x_coord[old][location],
                                      data->coords.y_coord[old][location],
                                      data->coords.x_coord[new][location],
                                      data->coords.y_coord[new][location]);
      /* After a line is succesfully printed, update the SDL window */
      Neill_SDL_UpdateScreen(&sw);
   }

   do {
      /* This enables the SDL window to continue to appear even after the
         programme has executed all given instructions. The SDL window will
         only be closed by using clicking the mouse, any keyboard button
         or the escape button on the top right of the SDL window*/
      Neill_SDL_Events(&sw);
   } while(!sw.finished);
   /* Quits all sub-systems used by the graphical user interface */
   SDL_Quit();
   atexit(SDL_Quit);

   free_parse(data);
   printf("Successfully parsed and interpreted the file: %s\n", inputfile);

   return EXIT_SUCCESS;
}
/* ######################################################################### */
