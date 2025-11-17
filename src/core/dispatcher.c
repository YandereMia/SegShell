#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../inc/commands/commands.h"
const char *paths[] = {
    "~/.myshellos/packages/%s/%s/bin/main",
    "~/Desktop/Projects/SegLinux_Shell/bin/%s",
    "~/.myshellos/bin/%s"
};
extern char cmd[256];

void dispatch_command(const char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        help_main();
        return;
    }
    if (strcmp(cmd, "clear") == 0) {
        clear_main();
        return;
    }
    if (strcmp(cmd, "exit") == 0) {
        exit_main();
        return;
    }
    if (strncmp(cmd, "echo ", 5) == 0) {
        echo_main(cmd + 5);
        return;
    }
    if (strncmp(cmd, "touch ", 6) == 0) {
        touch_main(cmd + 6);
        return;
    }
    if (strcmp(cmd, "whoami") == 0) {
        whoami_main();
        return;
    }
    if (strncmp(cmd, "write ", 6) == 0) {
        char buffer[1024];
        strncpy(buffer, cmd + 6, sizeof(buffer));
        buffer[sizeof(buffer)-1] = '\0';
        char *file = strtok(buffer, " ");
        char *text = strtok(NULL, "");
        if (file && text) {
            write_main(file, text);
            return;
        } else {
            printf("Usage: write <file> <text>\n");
            return;
        }
    }
    if (strncmp(cmd, "rm ", 3) == 0) {
        rm_main(cmd + 3);
        return;
    }
    if (strncmp(cmd, "apx -I ", 7) == 0) {
        const char *package_name = cmd + 7;
        apx_install(package_name);
        apx_sync_metadata();
        return;
    }
    if (strcmp(cmd, "apx -l") == 0) {
        apx_list();
        return;
    }
    if (strncmp(cmd, "apx -Ui ", 8) == 0) {
        const char *package_name = cmd + 8;
        apx_update(package_name);
        apx_sync_metadata();
        return;
    }
    if (strcmp(cmd, "apx -Ua") == 0) {
        apx_update_all_packages();
        apx_update_system();
        return;
    }
    if (strcmp(cmd, "apx -Up") == 0) {
        apx_update_all_packages();
        apx_sync_metadata();
        return;
    }
    if (strcmp(cmd, "apx -Us") == 0) {
        apx_update_system();
        return;
    }
    if (strcmp(cmd, "apx -S") == 0) {
        apx_sync_metadata();
        return;
    }
    if (strncmp(cmd, "cat ", 4) == 0) {
        const char *filename = cmd + 4;
        cat_main(filename);
        return;
    }
    if (strcmp(cmd, "pwd") == 0) {
        pwd_main();
        return;
    }
    if (strncmp(cmd, "cd ", 3) == 0) {
        const char *path = cmd + 3;
        cd_main(path);
        return;
    }
    if (strncmp(cmd, "cd", 2) == 0) {
        const char *cd = cmd + 2;
        while (*cd == ' ') cd++;
    
        if (strlen(cd) == 0)
            cd = getenv("HOME");
    
        if (chdir(cd) != 0)
            perror("cd");
        return;
    }
    if (strncmp(cmd, "nano ", 5) == 0) {
        const char *filename = NULL;

        if (strlen(cmd) > 5) {
            filename = cmd + 5;
            while (*filename == ' ') filename++;
        }

        char resolved_path[512];
        snprintf(resolved_path, sizeof(resolved_path), "%s/.myshellos/bin/nano", getenv("HOME"));

        if (access(resolved_path, X_OK) == 0) {
            if (filename && strlen(filename) > 0) {
                char cmdline[1024];
                snprintf(cmdline, sizeof(cmdline), "\"%s\" \"%s\"", resolved_path, filename);
                system(cmdline);
            } else {
                system(resolved_path);
            }
        } else {
            printf("nano binary not found at %s\n", resolved_path);
        }
        return;
    }
    char resolved_path[512];
    for (int i = 0; i < sizeof(paths)/sizeof(paths[0]); i++) {
        if (i == 0) {
            snprintf(resolved_path, sizeof(resolved_path), paths[i], cmd, cmd);
        } else {
            snprintf(resolved_path, sizeof(resolved_path), paths[i], cmd);
        }
        if (resolved_path[0] == '~') {
            char tmp[512];
            snprintf(tmp, sizeof(tmp), "%s%s", getenv("HOME"), resolved_path + 1);
            strcpy(resolved_path, tmp);
        }

        if (access(resolved_path, X_OK) == 0) {
            char cmdline[1024];
            snprintf(cmdline, sizeof(cmdline), "\"%s\"", resolved_path);
            system(cmdline);
            return;
        }
    }

    if (strcmp(cmd, "") == 0) {return;}

    printf("Unknown command: %s\n", cmd);
}