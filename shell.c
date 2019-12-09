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
#include "cmds.h"

int charFreq(char *input, char *delim){
    int i = 0;
    int count = 0;
    for(; input[i] != '\0'; i++){
	       if(*delim == input[i] ){
	          count++;
	    }
      }
    return count + 1;
}

char **parseArgs(char *input, char *separator){
    char *line = input;
    char *token;
    int i = 0;
    int size = charFreq(input, separator);
    printf("charFreq:%d\n", size);
    char ** argv = calloc(sizeof(char *), size + 1);
    for (i = 0; i < size; i++) {
        token = strsep(&line, separator);
        argv[i] = malloc(sizeof(char[strlen(token)]));
        argv[i] = token;
        printf("%s\n", argv[i]);
    }
    argv[size] = NULL;
    return argv;
    // printf("\nSize: %d", size)
}

char *cleanInput(char input[256]){
    int i = 0;
    for (i; input[i] != '\0'; i++) {
        if (input[i] == '\n') {
            input[i] = '\0';
        }
    }
    return input;
}

int runCommand(char argc[256]) {
    char ** args = parseArgs(argc, " ");
    int f = fork();
    printf("int: %d\n", f);
    printf("check: %d", args[0] == "cd");
    if (f == 0) {
        if (strcmp(args[0],"cd") == 0) {
            cd(args[1]);
        }
        else if (strcmp(args[0], "exit") == 0) {
            exit();
        }
    for (i; argv[i]!=NULL; i++) {
        free(argv[i])
    }
    free(argv);rgs[])
        }
        else {
            execvp(args[0], args);
        }
    }
    else if (f==-1) {
        return -1;
    }
    else {
        wait(NULL);
    }
    int i = 0;
    for (i; args[i]!=NULL; i++) {
        free(args[i])
    }
    free(args);
}
