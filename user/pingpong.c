//
// Created by Jingyu Su on 1/6/23.
//

//Pingpong a byte 1 round between child and parent process

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
    int p[2];
    pipe(p);
    if (fork() == 0) {
        char readBuff[10];
        if (read(p[0], readBuff, 1) < 0) {
            printf("child cannot read\n");
            exit(1);
        }
        printf("%d: received ping\n", getpid());
        if (write(p[1], "c", 1) < 0) {
            printf("child cannot write\n");
            exit(1);
        }
        close(p[1]);
        exit(0);
    } else {
        if (write(p[1], "c", 1) < 0) {
            printf("child cannot write\n");
            exit(1);
        }
        close(p[1]);
        char readBuff[10];
        read(p[0], readBuff, 1);
        printf("%d: received pong\n", getpid());
        exit(0);
    }
}
