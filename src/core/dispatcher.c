#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include "../../inc/commands/commands.h"
#include "../../inc/utils/input_cleaner.h"
void run_script(const char *filename);

void dispatch_command(char *line) {
    // skip empty lines
    if (!line || !*line) return;

    // ---- split line into argv ----
    char *argv[64];
    int argc = 0;
    char *p = line;
    while (*p) {
        while (*p == ' ') p++; // skip spaces
        if (*p == '\0') break;

        if (*p == '"') { // handle quoted strings
            p++;
            argv[argc++] = p;
            while (*p && *p != '"') p++;
            if (*p) *p++ = '\0';
        } else {
            argv[argc++] = p;
            while (*p && *p != ' ') p++;
            if (*p) *p++ = '\0';
        }
    }
    argv[argc] = NULL;

    // ---- check builtins ----
    if (strcmp(argv[0], "exit") == 0) { exit(0); }
    if (strcmp(argv[0], "cd") == 0) {
        if (argc > 1) chdir(argv[1]);
        else chdir(getenv("HOME"));
        return;
    }
    if (strcmp(argv[0], "pwd") == 0) {
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
        return;
    }
    if (strcmp(argv[0], "source") == 0 || strcmp(argv[0], "run") == 0) {
        if (argc != 2) {printf("usage: source <file.sg> OR run <file.sg>\n"); return;}
        run_script(argv[1]);
        return;
    }

    // ---- execute binary ----
    char path[512];
    snprintf(path, sizeof(path), "/home/yanderemia/segshell/bin/%s", argv[0]);
    if (access(path, X_OK) != 0) {
        printf("Unknown command: %s\n", argv[0]);
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {
        execv(path, argv);
        perror("execv");
        exit(1);
    } else {
        waitpid(pid, NULL, 0);
    }
}

void run_script(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening script file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        input_cleaner(line);

        if (strlen(line) == 0) continue;
        if (strncmp(line, "#", 1) == 0) continue;

        dispatch_command(line);
    }

    fclose(file);
}