#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

int main() {

  setlocale(LC_ALL, "pt_BR.UTF-8");

  int books_counter = 0;
  FILE *file = fopen("books.bin", "rb+");
  if (file == NULL) {
    file = fopen("books.bin", "wb+");
  }
  PrimaryIndex primary_index[BOOKS_MAX_LEN];
  SecondaryIndex secondary_index[BOOKS_MAX_LEN];
  for (int i = 0; i < BOOKS_MAX_LEN; i++) {
    primary_index[i].id = -1;
    primary_index[i].offset = -1;
    secondary_index[i].offset = -1;
  }

  // Carregar os índices secundários
  rewind(file);
  while (fread(&primary_index[books_counter], sizeof(PrimaryIndex), 1, file) ==
         1) {
    if (primary_index[books_counter].id != -1) {
      fread(&secondary_index[books_counter], sizeof(SecondaryIndex), 1, file);
      books_counter++;
    }
  }

  while (1) {
    char buffer[150];
    Book b_buffer;
    scanf(" %[^(\r|\n)]", buffer);

    switch (buffer[0]) {
    case 'A':
      printf("----------------------------------------------------------\n");
      read_add(file, buffer, &b_buffer, primary_index, secondary_index,
               &books_counter);
      break;
    case 'R':
      printf("----------------------------------------------------------\n");
      read_search_remove(file, buffer, &b_buffer, primary_index,
                         secondary_index, &books_counter);
      break;
    case 'S':
      printf("----------------------------------------------------------\n");
      read_search_remove(file, buffer, &b_buffer, primary_index,
                         secondary_index, &books_counter);
      break;
    case 'E':
      // Salvar os índices secundários antes de sair
      rewind(file);
      for (int i = 0; i < books_counter; i++) {
        fwrite(&primary_index[i], sizeof(PrimaryIndex), 1, file);
        fwrite(&secondary_index[i], sizeof(SecondaryIndex), 1, file);
      }
      fclose(file);
      return 0;
    default:
      printf("----------------------------------------------------------\n");
      printf("Operacao Invalida");
    }
  }
  fclose(file);
  return 0;
}