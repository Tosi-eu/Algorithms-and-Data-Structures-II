#include "bookHandler.h"
#include "fileHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_in_file_and_save(Book *book_name, char *file_name, int bite_offset)
 {

    fwrite(&(book_name->id), sizeof(int), 1, arq);
    fwrite(&(book_name->book_title), sizeof(char), strlen(book_name->book_title), arq);
    fwrite(&(book_name->author), sizeof(char), strlen(book_name->author), arq);
    fwrite(&bite_offset, sizeof(int), 1, arq); // posição no file_name
    bite_offset += sizeof(Book);
}

Book* readlines() 
{
    Book* book = (Book*) malloc(sizeof(Book));

    setbuf(stdin, NULL);
    scanf("%d", &book->id);
    fgets(book->book_title, MAX_BOOK_TITTLE, stdin);
    fgets(book->author, MAX_AUTHOR_NAME, stdin);

    return book;
}