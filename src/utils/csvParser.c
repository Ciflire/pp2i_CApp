#include "../include/csvParser.h"

// Use this function with a csv import with the right number of column
// and the right number of lines to skip
void csvParser(char *path, int linesToSkip, line_array *file) {
  // if we can open the file then we proceed
  if ((fopen(path, "r"))) {
    // printf("File opened\n");
    int indLigne = 0;
    int indCol = 0;
    int indChar = 0;
    char c;
    FILE *csv = fopen(path, "r");
    while ((c = fgetc(csv)) != EOF) {
      // The test of line is made after to avoid to increment the line until we
      // skip enough
      if (c == '\n') {
        // if we skipped enough line, we add the end of string character
        if (indLigne >= linesToSkip) {
          file->line[indLigne - linesToSkip]->info[indCol][indChar] = '\0';
        }
        // if we read a new line we increment the line
        indLigne++;
        indCol = 0;
        indChar = 0;
        // if we read a comma it mean we increment the column
      } else if (c == ',' && indLigne >= linesToSkip) {
        file->line[indLigne - linesToSkip]->info[indCol][indChar] = '\0';
        indCol++;
        indChar = 0;
        // if we read a character we add it to the current column
      } else if (indLigne >= linesToSkip) {
        file->line[indLigne - linesToSkip]->info[indCol][indChar] = c;
        indChar++;
      }
    }
    fclose(csv);
  };
  //csv_import_print(file);
  return;
}
