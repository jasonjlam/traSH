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
#include "shell.h"

int main(){
    int size = 0;
    char input[256];
    while (1) {
        char dir[512];
        getcwd(dir, 512);
        printf("\n%s$ ", dir );
        fgets(input, 256, stdin);
        cleanInput(input);
        printf("\n%s", input);
        printf("\n# of args: %d \n", charFreq(input, " "));
        char ** argv = parseArgs(input, " ");
        int f = fork();
        if (f == 0) {
            execvp(argv[0], argv);
        }
        else if (f==-1) {
            return -1;
        }
        else {
            wait(NULL);
        }
    }

    return 0;
}
