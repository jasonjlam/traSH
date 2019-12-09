#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>

void cd(char *dir) {
    printf("dir: %s", dir);
    if (chdir(dir) != 0) {
        printf("Error changing current directory\n");
    }
}

void exit() {
        exit(0;)
}
