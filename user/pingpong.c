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
    //printf("here\n");
    pipe(p);
    //printf("created pipe\n");
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
        //printf("%d: after write\n", getpid());
        close(p[1]);
        exit(0);
    } else {
        //printf("parent: 1\n");
        if (write(p[1], "c", 1) < 0) {
            printf("child cannot write\n");
            exit(1);
        }
        close(p[1]);
        //printf("parent wrote to pipe\n");
        char readBuff[10];
        read(p[0], readBuff, 1);
        printf("%d: received pong\n", getpid());
        exit(0);
    }
    //printf("%d: about to exit\n", getpid());
    //exit(0);
    //return 0;
}
