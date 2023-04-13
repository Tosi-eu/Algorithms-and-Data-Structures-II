#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM 100
#define FILE_NOT_CREATED 123   
#define ALLOCATION_ERROR 321 

#define FILE_NAME "books_records.bin"

typedef char title_delimiter;
typedef char record_delimiter;

typedef struct Books {
  int id;
  char title[MAX_TAM];
  char author[MAX_TAM];
  long int byte_offset;
} Books;

void save_books_in_file(Books *book, FILE *arq);
void read_all_records(Books *record_list, FILE *arq, int n);

#endif

