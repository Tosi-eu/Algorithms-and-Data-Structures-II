#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

void read_all_records(Books *record_list, FILE *arq, int n, int m);
void save_books_in_file(Books *book, FILE *arq);

int main() {

  int n, m;
  
  scanf("%d", &n);

  FILE *arq = fopen(FILE_NAME, "ab+");
  if (arq == NULL) {
    printf("Erro ao abrir file de escrita!\n");
    return FILE_NOT_CREATED;
  }

  Books records_list[n];
  for (int i = 0; i < n; i++) {
    Books *books = (Books *)malloc(sizeof(Books));
    scanf("%d", &books->id);
    scanf(" %[^(\r|\n)]", books->title);
    scanf(" %[^(\r|\n)]", books->author);
    save_books_in_file(books, arq);
    free(books);
  }

  scanf("%d", &m);
  read_all_records(records_list, arq, n, m);

  for (int i = n - m; i < n; i++) {
    printf("Id: %d\n", records_list[i].id);
    printf("Titulo: %s\n", records_list[i].title);
    printf("Autor: %s\n", records_list[i].author);
    printf("Byte offset: %ld\n", records_list[i].byte_offset);
    if(i != n - 1)
      printf("\n");
  }

  fclose(arq);

  return 0;
}



void read_all_records(Books *record_list, FILE *arq, int n, int m) {

  // calcular tamanho do file
  fseek(arq, 0, SEEK_END);
  long file_size = ftell(arq);
  rewind(arq);

  // posicionar o ponteiro para ler do início
  if (file_size > 0) {
    fseek(arq, 0, SEEK_SET);
  }

  // ler todos os registros
  int i = 0;
  long byte_offset = 0;
  while (ftell(arq) < file_size && i < n) {

    // byte offset
    record_list[i].byte_offset = byte_offset;

    // id
    fread(&(record_list[i].id), sizeof(int), 1, arq);

    // title
    int j = 0;
    char c = fgetc(arq);
    while (c != '|') {
      record_list[i].title[j] = c;
      j++;
      c = fgetc(arq);
    }
    record_list[i].title[j] = '\0';

    // author
    int author_size;
    fread(&author_size, sizeof(int), 1, arq);
    fread(record_list[i].author, sizeof(char), author_size, arq);
    record_list[i].author[author_size] = '\0';

    fgetc(arq); // ler e descartar o caractere "#"

    // atualizar byte offset
    byte_offset = ftell(arq);

    i++;
  }
}

void save_books_in_file(Books *book, FILE *arq) {

  // escrever o ID
fwrite(&(book->id), sizeof(int), 1, arq);

// escrever o título
fwrite(book->title, sizeof(char), strlen(book->title), arq);
fwrite("|", sizeof(char), 1, arq);

// escrever o autor
int author_size = strlen(book->author);
fwrite(&author_size, sizeof(int), 1, arq);
fwrite(book->author, sizeof(char), author_size, arq);

// escrever o caractere "#"
fwrite("#", sizeof(char), 1, arq);
}
