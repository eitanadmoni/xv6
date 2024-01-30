#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
  int len;
  if(argc !=2){
    printf("invalid number of arguments");
    exit(0);
  }
  len = atoi(argv[1]);
  sleep(len);
  exit(0);
}


