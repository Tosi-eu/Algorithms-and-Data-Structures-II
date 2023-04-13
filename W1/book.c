#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

static int get_author_size(Books *book)
{
  return strlen(book->author);
}

static int get_title_size(Books *book)
{
    return strlen(book->title);
}

static int get_file_size()
{

  FILE *arq= fopen(FILE_NAME, "r");
  if(arq != NULL)
  {
    fseek(arq, 0, SEEK_END);
    long file_size = ftell(arq);
    rewind(arq);
    return file_size;
  }
  return 0;
}

void read_all_records(Books *record_list, FILE *arq, int n) {

  arq = fopen(FILE_NAME, "rb+");
  if (arq == NULL) {
    printf("Erro ao abrir file de leitura!\n");
    return;
  }

  // calcular tamanho do file
  long file_size = get_file_size();

  // limpar buffer do arquivo
  fflush(arq);

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

void save_books_in_file(Books *book, FILE *arq) 
{
  title_delimiter TD = '|';
  record_delimiter RD = -1;

  // id
  fwrite(&(book->id), sizeof(int), 1, arq);

  // title
  int title_len = get_title_size(book);
  fwrite(book->title, sizeof(char), title_len, arq);
  fwrite(&TD, sizeof(char), 1, arq);

  // comprimento author
  int autor_len = get_author_size(book);
  fwrite(&autor_len, sizeof(int), 1, arq);

  // author
  fwrite(book->author, sizeof(char), strlen(book->author), arq);

  // fim do registro
  fwrite(&RD, sizeof(char), 1, arq);
}