#include <stdio.h>
#include <stdlib.h>
void whoami_main() {
    char *env_user = getenv("USER");
    const char *username = env_user ? env_user : "unknown";
    printf("%s\n", username);
}