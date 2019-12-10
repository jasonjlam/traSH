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
    int f = 0;
    int result = 0;
    int size = 0;
    char input[256];
    char ** argc = NULL;
    char dir[512];
    while (1) {
        getcwd(dir, 512);
        printf("\n%s$ ", dir );
        fgets(input, 256, stdin);
        cleanInput(input);
        printf("\n%s", input);
        printf("\n# of args: %d \n", charFreq(input, " "));
        argc = parseArgs(input, ";");
        for (i = 0; argc[i] != NULL; i ++) {
            result = runCommand(argc[i]);
            if (result == 0) {
                return 0;
            }
            else if (result == -1) {
                return -1;
            }
        }
    }
    return 0;
}
