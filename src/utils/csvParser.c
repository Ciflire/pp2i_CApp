#include "../include/csv_import.h"

// Use this function with a csv import with the right number of column
// and the right number of lines to skip
void csvParser(char *path, int linesToSkip, csv_import *file) {
  FILE *csv = fopen(path, "r");
  // define value to skip lines
  /*  While !(EOF)
        while !("\n")
          lire caractère
          Si "," décale l'indice de la liste
          Sinon ajouter le caractère à l'emplacement mémoire suivant
        fin tant que
      fin tant que */
  // skip first line
  int indLigne = 0;
  int indCol = 0;
  int indChar = 0;
  char c;
  while ((c = fgetc(csv)) != EOF) {
    if (c == '\n' && indLigne >= linesToSkip) {
      file->line[indLigne]->info[indCol][indChar] = '\0';
      indLigne++;
      indCol = 0;
      indChar = 0;
    } else if (c == ',' && indLigne >= linesToSkip) {
      file->line[indLigne]->info[indCol][indChar] = '\0';
      indCol++;
      indChar = 0;
    } else if (indLigne >= linesToSkip) {
      file->line[indLigne]->info[indCol][indChar] = c;
      indChar++;
    }
  }
}
