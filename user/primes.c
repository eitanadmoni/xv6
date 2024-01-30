#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <sys/types.h>

void rec_prime(int* lpipe, int prime){
    if(prime == 0){
        return;
    }
    printf("\nprime %d\n", prime);
    int buf;
    pid_t pid;
    int secprime;
    int rp[2];
    if (pipe(rp) < 0){ 
        exit(1);
    }
    read(lpipe[0], &buf, sizeof(buf));
    secprime = buf;
    pid = fork();
    if(pid<0){
        exit(1);
    }
    else if (pid == 0){
        close(rp[1]);
        rec_prime(rp, secprime);
        exit(0);
    }
    else{
        close(rp[0]);
        while (read(lpipe[0], &buf, sizeof(buf)) != 0){
            //printf("\nprime is: %d, num is: %d\n", prime, buf);
            if((buf % prime) != 0){
                write(rp[1], &buf, sizeof(buf));
            }
        }
        close(rp[1]);
        close(lpipe[0]);
        exit(0);
    }
}

int main(){
    int buf;
    pid_t pid;
    int p[2];
    int i;
    if (pipe(p) < 0){ 
        exit(1);
    }
    pid = fork();
    if(pid<0){
        exit(1);
    }
    buf = 2;
    if(pid == 0){
        close(p[1]);
        rec_prime(p, 2);
        exit(0);
    }
    else{
        close(p[0]);
    for(i = 3; i<= 35; i++){
        //printf("i is %d\n", i);
        buf = i;
        write(p[1], &buf, sizeof(buf));
    }
    close(p[1]);
    exit(0);
    }
}