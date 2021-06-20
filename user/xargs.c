#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
#define MAX_LINE 10
#define MAX_LEN 32


int main(int argc, char *argv[])
{
    char tmp[1];

    char* cmd[MAXARG];

    int i;
    cmd[0] = argv[1];
    for(i = 2;i<argc;i++){
        cmd[i-1] = argv[i];
    }

    char p[MAX_LINE][MAX_LEN];
    
    int j = 0;
    int k = 0;

    while(read(0, tmp, 1) != 0){
        if(tmp[0] == '\n'){
            if(fork() == 0){
                cmd[i-1] = p[j];
                exec(argv[1], cmd);
            }else{
                wait(0);
            }
            ++j;
            k = 0;
            
        }else{
            p[j][k] = tmp[0];
            k++;
        }
    }
    exit(0);
}