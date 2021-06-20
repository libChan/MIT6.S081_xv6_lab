#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p1[2]; //p -> s
    int p2[2]; //s -> p
    pipe(p1);
    pipe(p2);
    char buf[2];

    if(fork() == 0){
        read(p1[0], buf, 1);
        fprintf(2, "%d: received ping\n",getpid());
        write(p2[1], "b", 1);
    }
    else{
        write(p1[1], "b", 1);
        read(p2[0], buf, 1);
        fprintf(2, "%d: received pong\n",getpid());
    }

    exit(0);
}