#include <stdio.h>
#include <string.h>


void write_main(const char *PathTofile, const char *text) {
    char full_path[4096];
    FILE *fptr;
    
    strcpy(full_path, PathTofile);

    fptr = fopen(full_path, "w");
    fprintf(fptr, "%s\n", text);
    fclose(fptr);
}