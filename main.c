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
    int i = 0;
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
        char ** argc = parseArgs(input, ";");
        for (i; argc[i] != NULL; i ++) {
            char** args = parseArgs(argc[i], " ");
            int f = fork();
            printf("%d\n", f);
            if (f == 0) {
                execvp(args[0], args);
            }
            else if (f==-1) {
                printf("yadungoofed\n");
                return -1;
            }
            else {
                printf("ahshitherewegoagain\n");
                wait(NULL);
            }
        }
    }

    return 0;
}
