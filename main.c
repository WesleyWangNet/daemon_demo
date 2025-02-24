#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

static int daemon_init() {
    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    } else if (pid > 0) {
        exit(0);
    }

    if (setsid() == -1) {
        return -1;
    }
    chdir("/");
    umask(0);

    int fd = open("/dev/null", O_RDWR);
    if (fd == -1) {
        return -1;
    }

    if (dup2(fd, STDIN_FILENO) == -1) {
        return -1;
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
        return -1;
    }

    if (dup2(fd, STDERR_FILENO) == -1) {
        return -1;
    }
    if(fd > STDERR_FILENO) {
        close(fd);
        fd = -1;
    }
    
    return 0;
}


int main() {
    if (daemon_init() != 0) {
        printf("daemon_init failed\n");
        return -1;
    }

    //do something
    while (1) {
        sleep(1);
    }
        
    return 0;
}
