#include <stdio.h>
#include <unistd.h>

void rm_main(const char *filename) {
    if (unlink(filename) != 0) {
        perror("rm");
    }
}
