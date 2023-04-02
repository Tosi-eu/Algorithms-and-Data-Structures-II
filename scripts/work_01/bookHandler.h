#ifndef BOOKHANDLER_H
#define BOOKHANDLER_H

typedef char typeBookName;
typedef char typeBookAuthor;

#define MAX_BOOK_TITTLE 100;
#define MAX_AUTHOR_NAME 100;

typedef struct Book 
{
    short int id;
    typeBookName *book_title;
    typeBookAuthor *author;
} Book;

Book* readlines(); 
void write_in_file_and_save(Book *book_name, char *file_name, int byte_offset);

#endif