#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ALIASES 50
#define MAX_CMD_LEN 256

typedef struct {
    char name[64];
    char command[MAX_CMD_LEN];
} Alias;

static Alias aliases[MAX_ALIASES];
static int alias_count = 0;

int find_alias(const char *name) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(aliases[i].name, name) == 0)
            return i;
    }
    return -1;
}

int add_alias(const char *name, const char *command) {
    if (alias_count >= MAX_ALIASES) {
        printf("Alias limit reached!\n");
        return 1;
    }

    int idx = find_alias(name);
    if (idx != -1) {
        strncpy(aliases[idx].command, command, MAX_CMD_LEN-1);
        aliases[idx].command[MAX_CMD_LEN-1] = '\0';
        return 0;
    }

    strncpy(aliases[alias_count].name, name, sizeof(aliases[alias_count].name)-1);
    aliases[alias_count].name[sizeof(aliases[alias_count].name)-1] = '\0';

    strncpy(aliases[alias_count].command, command, MAX_CMD_LEN-1);
    aliases[alias_count].command[MAX_CMD_LEN-1] = '\0';

    alias_count++;
    return 0;
}

const char* get_alias_command(const char *name) {
    int idx = find_alias(name);
    if (idx != -1)
        return aliases[idx].command;
    return NULL;
}

int alias_cmd(char *line) {
    char *trimmed = line + 6;
    while (*trimmed == ' ') trimmed++;

    if (*trimmed == '\0') {
        return 0;
    }

    char *eq = strchr(trimmed, '=');
    if (!eq) {
        printf("Usage: alias <name>=<command>\n");
        return 1;
    }

    *eq = '\0';
    char *name = trimmed;
    char *command = eq + 1;

    add_alias(name, command);
    printf("Alias created: %s=%s\n", name, command);
    return 0;
}

