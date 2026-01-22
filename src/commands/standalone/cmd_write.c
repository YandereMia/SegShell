#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {printf("usage: write <file> <content>\n"); return 1;}
    char full_path[4096];
    FILE *fptr;
    
    strcpy(full_path, argv[1]);

    fptr = fopen(full_path, "w");
    fprintf(fptr, "%s\n", argv[2]);
    fclose(fptr);
}