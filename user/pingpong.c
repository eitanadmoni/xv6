#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <sys/types.h>
int main(int argc, char *argv){
    char buf[1];
    int p[2];
    pid_t pid;
    if(pipe(p) < 0){
        printf("error while piping");
        exit(1);
    }
    pid = fork();
    if(pid < 0){
        printf("error while forking");
        exit(1);
    }
    else if(pid == 0){
        read(p[0], buf, 1);
        printf("%d: received ping\n", getpid());
        write(p[1], buf, 1);
        exit(0);
    }
    if(pid > 0){
    write(p[1], buf, 1);
    sleep(1);
    read(p[0], buf, 1);
    printf("%d: received pong\n", getpid());
    close(p[0]);
    close(p[1]);
    exit(0);
    }
}