#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

int main() {

  FILE *arq = fopen(FILE_NAME, "wb+");
  if (arq == NULL) {
    exit(FILE_NOT_CREATED);
  }

  int n, m;
  
  scanf("%d", &n);

  Books records_list[n];
  for (int i = 0; i < n; i++) {
    Books *books = (Books *)malloc(sizeof(Books));
    if(books == NULL){
      exit(ALLOCATION_ERROR);
    }
    scanf("%d", &books->id);
    scanf(" %[^(\r|\n)]", books->title);
    scanf(" %[^(\r|\n)]", books->author);
    save_books_in_file(books, arq);
    free(books);
  }
  
  fclose(arq); // fechar o arquivo de escrita

  scanf("%d", &m);

  arq = fopen(FILE_NAME, "rb"); // reabrir o arquivo em modo de leitura
  if (arq == NULL) {
   exit(FILE_NOT_CREATED);
  }

  read_all_records(records_list, arq, n);

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
