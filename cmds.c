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

// Very simple cd command; changes directory and checks for failure
void cd(char *dir) {
    printf("dir: %s", dir);
    if (chdir(dir) != 0) {
        printf("Error changing current directory\n");
    }
}
// Checks if the first argument is either cd or exit which are hardcoded
void exitcdCheck(char ** args) {
    // If the first argument is exit, exits shell and reports a successful exit
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }
    else if (strcmp(args[0], "cd") == 0) {
        // If the first argument is cd, changes directory by running cd() command
        // printf("cd check: %d", strcmp(args[0], "cd"));
        cd(args[1]);
    }
}
