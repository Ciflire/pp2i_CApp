#include "../include/csvParser.h"
#include <stdbool.h>

// Use this function with a csv import with the right number of column
// and the right number of lines to skip
void csvParser(char *path, int linesToSkip, line_array *file) {
  // if we can open the file then we proceed
  if ((fopen(path, "r"))) {
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
  }
  return;
}

// Use this function with a csv import with the right number of column
// and the right number of lines to skip
void parser_pdcList(char *path, line_array *file) {
  // if we can open the file then we proceed
  if ((fopen(path, "r"))) {
    int indLigne = 0;
    int indCol = 0;
    int indChar = 0;
    bool inBigBrackets = false;
    bool inBrackets = false;
    char c;
    FILE *f = fopen(path, "r");
    while ((c = fgetc(f)) != EOF) {
      // The test of line is made after to avoid to increment the line until we
      // skip enough
      if (c == '\n') {
        // if we skipped enough line, we add the end of string character

        file->line[indLigne]->info[indCol][indChar] = '\0';

        // if we read a new line we increment the line
        indLigne++;
        indCol = 0;
        indChar = 0;
      } else if (c == '[' && !inBigBrackets) {
        inBigBrackets = true;
      } else if (c == ']' && inBigBrackets && !inBrackets) {
        inBigBrackets = false;
      } else if (c == '[' && !inBrackets && inBigBrackets) {
        inBrackets = true;
        file->line[indLigne]->info[indCol][indChar] = c;

        indChar++;
      } else if (c == ']' && inBrackets && inBigBrackets) {
        inBrackets = false;
        file->line[indLigne]->info[indCol][indChar] = c;

        indChar++;
        // if we read a comma it mean we increment the column
      } else if (c == ',' && !inBrackets && inBigBrackets) {
        file->line[indLigne]->info[indCol][indChar] = '\0';
        indCol++;
        indChar = 0;
        // if we read a character we add it to the current column
      } else {
        file->line[indLigne]->info[indCol][indChar] = c;
        indChar++;
      }
    }
    fclose(f);
    return;
  }
}
/* 
void parser_pdcList2(char *path, line_array *file) {
  int indLigne = 0;
  int indCol = 0;
  int indChar = 0;
  bool inBrackets = false;
  bool inBigBracket = false;
  bool before = true;
  char *word = malloc(sizeof(char) * 1000);
  char c;
  FILE *f = fopen(path, "r");
  while ((c = fgetc(f)) != EOF) {
    if (c == '\n') {
      file->line[indLigne]->info[indCol][indChar] = '\0';
      indLigne++;
      indChar = 0;
      indCol = 0;
    } else if (c == '[' && indCol != 0) {
      inBrackets = true;
    } else if (c == '[' && indCol == 0) {
      inBigBracket = true;
    } else if (c == ',' && inBrackets) {
      before = false;
    } else if (c == ']' && inBigBracket) {
      word[indChar] = '\0';
      inBrackets = false;
      file->line[indLigne]->info[indCol] = word;
    } else if (c == ',' && !inBrackets) {
    } else if (c == ']' && !inBrackets) {
      inBigBracket = false;
    } else
      ()
  }
} */
