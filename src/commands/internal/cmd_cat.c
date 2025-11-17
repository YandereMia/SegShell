#include <stdio.h>

void cat_main(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) { perror("cat"); return; }

    char buf[1024];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
        fwrite(buf, 1, n, stdout);
    }

    fclose(f);
}
