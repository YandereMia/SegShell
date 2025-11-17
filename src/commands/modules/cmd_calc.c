#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Existing functions
#include <math.h>
int y;
int x;
char BufferX[256];
char BufferY[256];
void input_cleaner(char *buf);
void calc_help() {
    printf("usage example: 'calc sub'\n");
    printf("available options: add, sub, multi, div\n");
}
void calc_main() {
    printf("Set X Value: ");
    fgets(BufferX, sizeof(BufferX), stdin);
    printf("Set Y Value: ");
    fgets(BufferY, sizeof(BufferY), stdin);

    input_cleaner(BufferX);
    input_cleaner(BufferY);
    x = atoi(BufferX);
    y = atoi(BufferY);
}
void calc_sub() { int z = x - y; printf("%d - %d = %d\n", x, y , z); }
void calc_add() { int z = x + y; printf("%d + %d = %d\n", x, y , z); }
void calc_div() { int z = x / y; printf("%d / %d = %d\n", x, y , z); }
void calc_multi() { int z = x * y; printf("%d * %d = %d\n", x, y , z); }
void calc_square() {double result = sqrt(x); printf("√%d = %.2lf\n", x, result);}

void input_cleaner(char *buf) {
    size_t len = strlen(buf);
    if(len > 0 && buf[len-1] == '\n') {
        buf[len-1] = '\0';
    }
}


int main() {
    calc_help();
    calc_main();
    
    char op[16];
    printf("Choose operation (add, sub, multi, div, square): ");
    fgets(op, sizeof(op), stdin);
    input_cleaner(op);

    if (strcmp(op, "add") == 0) calc_add();
    else if (strcmp(op, "sub") == 0) calc_sub();
    else if (strcmp(op, "multi") == 0) calc_multi();
    else if (strcmp(op, "div") == 0) calc_div();
    else if (strcmp(op, "square") == 0) calc_square();
    else printf("Unknown operation: %s\n", op);

    return 0;
}