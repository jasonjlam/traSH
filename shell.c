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
    printf("current index start: %d\n", i);
    printf("length: %ld \n", strlen(input));
    for(;  i < strlen(input); i++){
        printf("current index: %d - %d - %c\n", i, *delim == input[i], input[i] );
	    if(*delim == input[i] ){
            for (i; input[i] == *delim; i ++) {
            }
            printf("current index count: %d\n", i);
            count++;
       }
    }
    printf("current index: %d - %d - \"%c\"\n", i, *delim == input[i], input[i] );
    printf("exit index: %d\n", i);
    return count + 1;
}

// takes an input string, returns an argv of all arguments in a char **
char **parseArgs(char *input, char *separator){
    printf("calling parseArgs:%s, \"%s\"\n", input, separator);
    char line2[256];
    strcpy(line2, input);
    char *line = line2;
    char *token = strsep(&line, separator);
    int i = 0;
    int size = charFreq(input, separator);
    printf("charFreq:%d\n", size);
    printf("size:%d\n", size);
    char ** argv = calloc(sizeof(char *), size + 1);
    while (token != NULL) {
        printf("token: %s \n",token);
        printf("line: %s \n", line);
        if (strcmp(token, "") != 0) {
            printf("Malloc:\n");
            argv[i] = malloc(sizeof(strlen(token)+1));
            strcpy(argv[i], token);
            printf("%s\n", argv[i]);
            i ++;
        }
        token = strsep(&line, separator);
    }
    // argv[size] = '\0';
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
    printf("arg0:%s\n", args[1]);
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
