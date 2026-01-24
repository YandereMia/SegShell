#include <stddef.h>
#include <stdio.h>
#include "utils/input_cleaner.h"
#include "utils/color.h"
#include "core/dispatcher.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
void get_path();
char display_cwd[PATH_MAX];
const char *username;
int main(int argc, char *argv[]) {
    if (argc > 1) {
        run_script(argv[1]);
        return 0;
    }

    char *env_user = getenv("USER");
    username = env_user ? env_user : "unknown";
    char line[256];
    while (1) {
        get_path();
        printf(AC_PURPLE"%s | %s@SegLinux『>』"AC_RESET,display_cwd ,username);
        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        input_cleaner(line);
        dispatch_command(line);
    }
}

void get_path() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    const char *home = getenv("HOME");
    
    if (home && strncmp(cwd, home, strlen(home)) == 0) {
        
        snprintf(display_cwd, sizeof(display_cwd), "~%s", cwd + strlen(home));
    } else {
        strncpy(display_cwd, cwd, sizeof(display_cwd));
    }
}