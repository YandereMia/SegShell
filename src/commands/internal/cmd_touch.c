#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>

void touch_main(const char *filename) {
    int fd = open(filename, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("touch");
        return;
    }
    close(fd);

    if (utime(filename, NULL) != 0) {
        perror("touch utime");
    }
}
