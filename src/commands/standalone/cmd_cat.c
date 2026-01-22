#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {printf("usage: cat <file>\n"); return 1;}
    FILE *f = fopen(argv[1], "r");
    if (!f) { perror("cat"); return 1; }

    char buf[1024];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
        fwrite(buf, 1, n, stdout);
    }

    fclose(f);
}
