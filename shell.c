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

// Counts number of spaces in an input
int charFreq(char *input, char *delim){
    int i = 0;
    int count = 0;
    for(; input[i] == *delim; i++){
    };
    for(; input[i] != '\0'; i++){
	       if(*delim == input[i] ){
               for (i; input[i] == *delim; i ++) {
               }
	           count++;
	    }
      }
    return count + 1;
}

// takes an input string, returns an argv of all arguments in a char **
char **parseArgs(char *input, char *separator){
    printf("calling parseArgs:%s, %s\n", input, separator);
    char *line = input;
    char *token = strsep(&line, separator);
    int i = 0;
    int size = charFreq(input, separator);
    printf("charFreq:%d\n", size);
    printf("size:%d\n", size);
    char ** argv = calloc(sizeof(char *), size + 1);
    for (i = 0; token != NULL; i++) {
        printf("token: %s \n",token);
        printf("line: %s \n", line);
        if (strcmp(token, "") != 0) {
            printf("Malloc:\n");
            argv[i] = malloc(sizeof(char[strlen(token)]));
            argv[i] = token;
            printf("%s\n", argv[i]);
        }
        token = strsep(&line, separator);
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
    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }
    else if (strcmp(args[0],"cd") == 0) {
        printf("cd check: %d", strcmp(args[0], "cd"));
        cd(args[1]);
    }
    int f = fork();
    printf("int: %d\n", f);
    int i = 0;

    if (f == 0) {
        printf("ARGUMENTS:\n");
        for (int i = 0; args[i] != NULL; i ++) {
            printf("Arg: %s\n", args[i]);
        }
        execvp(args[0], args);
    }
    else if (f ==-1) {
        return -1;
    }
    else {
        wait(NULL);
    }
    // for (i; args[i]!=NULL; i++) {
    //     free(args[i]);
    // }
    // free(args);
}
