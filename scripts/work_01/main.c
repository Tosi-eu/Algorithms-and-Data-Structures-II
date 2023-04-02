#include <stdio.h>
#include <stdlib.h>
#include "bookHandler.h"
#include "fileHandler.h"

int main()
{
    int n, m;

    int byteoffset = 0;

    scanf("%d", &n);
    for(int i = 0; i < n; i++)
     {
        Book* l = readlines();
        write_in_file_and_save(l, FILE_NAME, byteoffset);
     }

    while(scanf("%d", &m) >= n)
    {
        scanf("%d", &m);
    }

    return 0;
}