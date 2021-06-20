#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define LOW 2
#define HIGH 35
void newProcess(int *p)
{
    int* q = malloc(2*sizeof(int));
    int buf[1];
    int prime;
    // first read, if failed exit.
    if(read(p[0], buf, 4) == 0){
        exit(0);
    }

    pipe(q);
    prime = buf[0];
    fprintf(2, "prime %d\n", prime);
    
    while(read(p[0], buf, 4) != 0){
        if(buf[0] % prime != 0){
            write(q[1], buf, 4);
        }
    }
    close(p[0]);
    close(q[1]);
    free(p);
    if(fork() == 0){
        newProcess(q);
    }else{
        wait(0);
    }
    exit(0);
}


int main(int argc, char *argv[])
{
    int* p = malloc(2*sizeof(int));
    pipe(p);

    for(int i = LOW;i<=HIGH;i++){
        write(p[1], &i, sizeof(int));
    }
    close(p[1]);

    if(fork() == 0){
        newProcess(p);
    }else{
        wait(0);
    }
    
    exit(0);
}