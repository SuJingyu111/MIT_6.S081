// User program that sleeps a given amount of time in seconds

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]){
    if (argc != 2) {
        char* errMsg = "Wrong arg num\n";
        write(2, errMsg, sizeof(errMsg));
        exit(1);
    }
    int seconds = atoi(argv[1]);
    sleep(seconds);
    exit(0);
}