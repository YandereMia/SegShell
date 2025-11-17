#include <string.h>
void input_cleaner(char *buf) {
    size_t len = strlen(buf);
    if(len > 0 && buf[len-1] == '\n') {
        buf[len-1] = '\0';
    }
}