#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    DIR *d;
    struct dirent *dir;
    int count = 0;

    d = opendir(".");
    if (!d) {
        perror("opendir");
        return 1;
    }

    while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            printf("%-20s", dir->d_name);
            count++;
            if (count % 3 == 0) {
                printf("\n");
            }
        }
    }

    if (count % 3 != 0) printf("\n");

    closedir(d);
    return 0;
}
