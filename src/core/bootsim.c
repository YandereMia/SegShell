#include <stdio.h>
#include <unistd.h>

void bootsim() {
    printf("Booting into the system\n");
    printf("-------------------- 0%%\r");
    fflush(stdout);
    sleep(1);
    printf("=====>-------------- 25%%\r");
    fflush(stdout);
    sleep(1);
    printf("==========>--------- 50%%\r");
    fflush(stdout);
    sleep(1);
    printf("===============>---- 75%%\r");
    fflush(stdout);
    sleep(1);
    printf("===================> 100%%\n");
    fflush(stdout);
    sleep(1);
    return;
}