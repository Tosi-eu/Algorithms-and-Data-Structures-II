#include "bookHandler.h"
#include "fileHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bookHandler.h"
#include "fileHandler.h"

Book create_file(char file_name)
{
    FILE* arq = fopen(file_name, "rw+");
    if(arq == NULL) {
        exit(ALLOCATION_ERROR);
    }
    fclose(arq);
}