#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {printf("usage: touch <filename>\n"); return 1;}
    int fd = open(argv[1], O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("touch");
        return 1;
    }
    close(fd);

    if (utime(argv[1], NULL) != 0) {
        perror("touch utime");
    }
}
