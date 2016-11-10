#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void sighandler (int signo) {
    if (signo == SIGUSR1) {
        printf("Parent PID:%d\n",getppid());
    }
    if (signo == SIGINT) {
        int fd = open("test", O_CREAT|O_RDWR|O_APPEND, 0644);
        char txt[] = "WE MADE IT WORK BOYS, PROGRAM EXITED DUE TO SIGINT\n";
        write(fd, txt, sizeof(txt));
        close(fd);
        printf("Recieved SIGINT! :D\n");
        exit(SIGINT);
    }
}

int main () {
    umask(0);
    while (42) { //wasn't working when I put it on 1 for whatever reason, changed it to first number that came to mind
        printf("PID: %d\n", getpid()); 
        signal(SIGINT, sighandler); //kill -2 <PID> or ^C to trigger
        signal(SIGUSR1,sighandler); //kill -10 <PID> to trigger
        sleep(1);
    }
    return 0; 
}