#include <unistd.h>
#include <stdio.h>

void cd_main(const char *path) {
    if (chdir(path) != 0) {
        perror("cd failed");
    }
}
