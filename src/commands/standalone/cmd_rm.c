#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {printf("usage: rm <file>\n"); return 0;}
    if (unlink(argv[1]) != 0) {
        perror("rm");
    }
}
