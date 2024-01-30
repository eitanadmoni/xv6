#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
#include <sys/types.h>




int main(int argc, char* argv[]){
    //printf("argc: %d\n", argc);
    char ch;
    pid_t pid;
    char buf[MAXARG];
    char* new_arg[argc + 1];
    int i = 0;
    int k;
    size_t length = argc;
    for(k = 0; k < argc; ++k)
    {
        length = strlen(argv[k])+1;
        new_arg[k] = malloc(length);
        memcpy(new_arg[k], argv[k], length);
    }
    /*for(k =0; k < argc; k++){
        printf("argv[%d]: %s\n", k, argv[k]);
    }*/
    memcpy(new_arg, argv, length);
    while(read(0, &ch, 1) > 0){
        if(ch != '\n'){
            buf[i] = ch;
            i += 1;
        }
        else{
            buf[i] = '\0';
            i = 0;
            //printf(" buf: %s\n", buf);
            new_arg[argc] = buf;
            /*for(k = 0; k<= argc; k++){
                printf("new arg[%d]: %s\n", k, new_arg[k]);
            }*/
            //printf("bla%s\n", (new_arg + 1)[0]);
            pid = fork();
            if(pid == 0){
                if(exec(new_arg[1], new_arg + 1) == -1){
                    printf("error while exec");
                    exit(1);
                }
            }
            else if(pid > 0){
                wait(0);
            }
        }
    }
    exit(0);
}
