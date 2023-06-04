#ifndef C_H
#define C_H

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AUTHOR_MAX_LEN 1000
#define TITLE_MAX_LEN 1000
#define BOOKS_MAX_LEN 1000

typedef struct {
  int id;
  char author[AUTHOR_MAX_LEN];
  char title[TITLE_MAX_LEN];
} Book;

typedef struct {
  int id;
  int offset;
} PrimaryIndex;

typedef struct {
  char author[AUTHOR_MAX_LEN];
  int offset;
} SecondaryIndex;

void read_add(FILE *file, char buffer[150], Book *B_buffer,
              PrimaryIndex *primary_index, SecondaryIndex *secondary_index,
              int *books_counter);
void read_search_remove(FILE *file, char buffer[150], Book *B_buffer,
                        PrimaryIndex *primary_index,
                        SecondaryIndex *secondary_index, int *books_counter);

#endif