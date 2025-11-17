#include <bits/time.h>
#include <time.h>
#include <stdio.h>

int main() {
    time_t currentTime;
    time(&currentTime);
    printf("%s", ctime(&currentTime));
}