#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

void read_add(FILE *file, char buffer[150], Book *B_buffer,
              PrimaryIndex *primary_index, SecondaryIndex *secondary_index,
              int *books_counter) {
  char *inicio;
  char *fim;

  char id[100];

  // Encontra o primeiro caractere de aspas simples
  inicio = strchr(buffer, '\'');

  // Encontra o próximo caractere de aspas simples
  fim = strchr(inicio + 1, '\'');

  strncpy(id, inicio + 1, fim - inicio - 1);
  id[fim - inicio - 1] = '\0';

  inicio = strchr(fim + 1, '\'');
  fim = strchr(inicio + 1, '\'');
  strncpy(B_buffer->title, inicio + 1, fim - inicio - 1);
  B_buffer->title[fim - inicio - 1] = '\0';

  inicio = strchr(fim + 1, '\'');
  fim = strchr(inicio + 1, '\'');
  strncpy(B_buffer->author, inicio + 1, fim - inicio - 1);
  B_buffer->author[fim - inicio - 1] = '\0';

  B_buffer->id = atoi(id);

  // Verificar se o ID já existe
  for (int i = 0; i < *books_counter; i++) {
    if (primary_index[i].id == B_buffer->id) {
      printf("Erro ao inserir registro, chave primária duplicada\n");
      return;
    }
  }

  // Adicionar livro no final do arquivo
  fseek(file, 0, SEEK_END);
  int offset = ftell(file);
  fwrite(B_buffer, sizeof(Book), 1, file);
  printf("Registro inserido\n");

  // Atualizar os índices secundários
  primary_index[*books_counter].id = B_buffer->id;
  primary_index[*books_counter].offset = offset;
  strncpy(secondary_index[*books_counter].author, B_buffer->author,
          AUTHOR_MAX_LEN);
  secondary_index[*books_counter].offset = offset;

  (*books_counter)++;
}

void read_search_remove(FILE *file, char buffer[150], Book *B_buffer,
                        PrimaryIndex *primary_index,
                        SecondaryIndex *secondary_index, int *books_counter) {
  char *inicio;
  char *fim;

  if (buffer[7] == 'i') {
    // Buscar ou remover por ID
    inicio = strchr(buffer, '\'');
    fim = strchr(inicio + 1, '\'');
    char id[100];
    strncpy(id, inicio + 1, fim - inicio - 1);
    id[fim - inicio - 1] = '\0';
    int search_id = atoi(id);

    if (buffer[0] == 'S') {
      // Buscar por ID
      int found = 0;
      for (int i = 0; i < *books_counter; i++) {
        if (primary_index[i].id == search_id && primary_index[i].id != -1) {
          fseek(file, primary_index[i].offset, SEEK_SET);
          fread(B_buffer, sizeof(Book), 1, file);
          printf("%d -", B_buffer->id);
          printf(" %s -", B_buffer->title);
          printf(" %s\n", B_buffer->author);
          found = 1;
          break;
        }
      }

      if (!found) {
        printf("Não encontrado\n");
      }
    } else if (buffer[0] == 'R') {
  // Remover por ID
  int removed = 0;
  for (int i = 0; i < *books_counter; i++) {
    if (primary_index[i].id == search_id && primary_index[i].id != -1) {
      // Remover livro do arquivo
      fseek(file, primary_index[i].offset, SEEK_SET);
      fread(B_buffer, sizeof(Book), 1, file);
      B_buffer->id = -1;
      fseek(file, primary_index[i].offset, SEEK_SET);
      fwrite(B_buffer, sizeof(Book), 1, file);

      // Remover índices
      primary_index[i].id = -1;
      primary_index[i].offset = -1;
      secondary_index[i].offset = -1;

      printf("Registro removido\n");
      removed = 1;
      break; // Adiciona o break aqui para interromper o loop após a remoção
    }
  }

  if (!removed) {
    printf("Erro ao remover\n");
  }

    }
  } else if (buffer[7] == 'a') {
    // Buscar ou remover por Autor
    inicio = strchr(buffer, '\'');
    fim = strchr(inicio + 1, '\'');
    char author[AUTHOR_MAX_LEN];
    strncpy(author, inicio + 1, fim - inicio - 1);
    author[fim - inicio - 1] = '\0';

    if (buffer[0] == 'S') {
      // Buscar por Autor
      int found = 0;
      for (int i = 0; i < *books_counter; i++) {
        if (strcmp(secondary_index[i].author, author) == 0 &&
            primary_index[i].id != -1) {
          fseek(file, secondary_index[i].offset, SEEK_SET);
          fread(B_buffer, sizeof(Book), 1, file);
          printf("%d - ", B_buffer->id);
          printf("%s - ", B_buffer->title);
          printf("%s\n", B_buffer->author);
          found = 1;
        }
      }

      if (!found) {
        printf("Não encontrado\n");
      }
    } else if (buffer[0] == 'R') {
  // Remover por Autor
  int removed = 0;
  for (int i = 0; i < *books_counter; i++) {
    if (strcmp(secondary_index[i].author, author) == 0 && primary_index[i].id != -1) {
      // Remover livro do arquivo
      fseek(file, primary_index[i].offset, SEEK_SET);
      fread(B_buffer, sizeof(Book), 1, file);
      B_buffer->id = -1;
      fseek(file, primary_index[i].offset, SEEK_SET);
      fwrite(B_buffer, sizeof(Book), 1, file);

      // Remover índices
      primary_index[i].id = -1;
      primary_index[i].offset = -1;
      secondary_index[i].offset = -1;
      printf("Registro removido\n");
      removed = 1;
    }
  }

  if (!removed) {
    printf("Erro ao remover\n");
    }
  }
}
                        }
