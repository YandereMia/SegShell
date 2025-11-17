#include <stddef.h>
#include <stdio.h>
#include "../../inc/utils/input_cleaner.h"
#include "../../inc/utils/color.h"
#include "../../inc/core/dispatcher.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
void get_path();
char display_cwd[PATH_MAX];
int main() {
    char *env_user = getenv("USER");
    const char *username = env_user ? env_user : "unknown";
    char cmd[256];
    while (1) {
        get_path();
        printf(AC_PURPLE"%s | %s@SegLinux『>』"AC_RESET,display_cwd ,username);
        fgets(cmd, sizeof(cmd), stdin);
        input_cleaner(cmd);
        dispatch_command(cmd);
    }
}

void get_path() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    const char *home = getenv("HOME");
    
    if (home && strncmp(cwd, home, strlen(home)) == 0) {
        // Replace home prefix with ~
        snprintf(display_cwd, sizeof(display_cwd), "~%s", cwd + strlen(home));
    } else {
        strncpy(display_cwd, cwd, sizeof(display_cwd));
    }
}