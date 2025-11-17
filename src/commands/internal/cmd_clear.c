#include <stdio.h>

void clear_main() {
    printf("\033[2J\033[H");  // \033 = ASCII ESC (27)
    fflush(stdout);           // okamžité vykreslení
}