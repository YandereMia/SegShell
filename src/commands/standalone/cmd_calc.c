#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//./arg0 arg1 arg2 arg3
int main(int argc, char *argv[]) {
    if (argc != 4) {printf("usage: calc <X> <operator> <Y>\n"); return 1;}
    int x = atoi(argv[1]);
    int y = atoi(argv[3]);
    int z;
    char *op = argv[2];
    if (strcmp(op, "+") == 0) {z = x + y; printf("%d %s %d = %d\n", x, op, y, z);}
    if (strcmp(op, "-") == 0) {z = x - y; printf("%d %s %d = %d\n", x, op, y, z);}
    if (strcmp(op, "x") == 0) {z = x * y; printf("%d * %d = %d\n", x, y, z);}
    if (strcmp(op, "/") == 0) {
        if (x == 0 || y == 0) {printf("division by zero!\n"); return 1;}
        z = x / y; printf("%d %s %d = %d\n", x, op, y, z);}
}