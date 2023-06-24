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
        // printf("%s\n", file->line[indLigne]->info[indCol]);
        indCol++;
        indChar = 0;
        // if we read a character we add it to the current column
      } else {
        file->line[indLigne]->info[indCol][indChar] = c;
        indChar++;
      }
    }
    line_array_print(file);
    fclose(f);
    return;
  }
}

void parser_pdc(char *path, line_array *file) {
  if ((fopen(path, "r"))) {
    int indLigne = 0;
    int indCol = 0;
    int indChar = 0;
    bool inBrackets = false;
    bool inParenthesis = false;
    char c;
    FILE *f = fopen(path, "r");
    while ((c = fgetc(f)) != EOF) {
      if (c == '\n') {
        indLigne++;
        indCol = 0;
        indChar = 0;
        inBrackets = false;
        inParenthesis = false;
      } else if (c == '[' && !inBrackets) {
        inBrackets = true;
      } else if (c == '(' && inBrackets && !inParenthesis) {
        inParenthesis = true;
      } else if (c == ',' && inParenthesis) {
        file->line[indLigne]->info[indCol][indChar] = '\0';
        indCol++;
        indChar = 0;
      } else if (c == ',' && !inParenthesis && inBrackets) {
        inParenthesis = false;
      } else if (c == ')' && inBrackets && inParenthesis) {
        inParenthesis = false;
        file->line[indLigne]->info[indCol][indChar] = '\0';
        indCol++;
        indChar = 0;
      } else if (c == ']') {
        inBrackets = false;
      } else {
        file->line[indLigne]->info[indCol][indChar] = c;
      }
    }
    fclose(f);
  }
}

int get_max_pdc_number(char *path) {
  FILE *file = fopen(path, "r");
  char c;
  char *number = malloc(10 * sizeof(char *));
  int i = 0;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      number[i]='\0';
      return atoi(number);
      
    }
    else {
      number[i]=c;
    }
    i++;
  }
  return 0;
}
