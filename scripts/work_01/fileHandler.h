#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "bookHandler.h"
#include "fileHandler.h"
#include <stdio.h>

#define ALLOCATION_ERROR 123;
#define FILE_NAME "book_registry.txt"

Book create_file(char file_name);

#endif