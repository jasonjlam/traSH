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

// Counts number of delims + 1 -> accurate number of terms for strsep();
int charFreq(char *input, char *delim){
    int i = 0;
    int count = 0;
    // Ignores all preceding delimiters
    for(; input[i] == *delim; i++){
    };
    // printf("current index start: %d\n", i);
    // printf("length: %ld \n", strlen(input));
    for(;  i < strlen(input); i++){
        // printf("current index: %d - %d - %c\n", i, *delim == input[i], input[i] );
	    if(*delim == input[i] ){
            // Consecutive repeated delimiters do not count
            for (i; input[i] == *delim; i ++) {
            }
            // printf("current index count: %d\n", i);
            count++;
       }
    }
    // printf("current index: %d - %d - \"%c\"\n", i, *delim == input[i], input[i] );
    // printf("exit index: %d\n", i);
    // Returns the number of terms rather than the number of delimiters
    return count + 1;
}

// takes an input string, returns an argv of all arguments in a char **
char **parseArgs(char *input, char *separator){
    // printf("calling parseArgs:%s, \"%s\"\n", input, separator);
    // Our input
    char line2[512];
    strcpy(line2, input);
    char *line = line2;
    // Initializes token with first call to strsep()
    char *token = strsep(&line, separator);
    int i = 0;
    // Counts the number of terms required
    int size = charFreq(input, separator);
    // printf("charFreq:%d\n", size);
    // printf("size:%d\n", size);
    // Creates an array of strings and allocates size for it in the memory
    char ** argv = calloc(sizeof(char *), size + 1);
    // If token is not null then tries to add it to command array
    while (token != NULL) {
        // printf("token: %s \n",token);
        // printf("line: %s \n", line);
        // Makes sure to ignore white space
        if (strcmp(token, "") != 0) {
            // printf("Malloc:\n");
            argv[i] = malloc(sizeof(strlen(token)+1));
            strcpy(argv[i], token);
            // printf("%s\n", argv[i]);
            // Increments i only if it works
            i ++;
        }
        token = strsep(&line, separator);
    }
    // argv[size] = '\0';
    // Returns the array ready to be called with execvp
    return argv;
    // printf("\nSize: %d", size)
}

// Gets rid of \n in stdin
char *cleanInput(char input[512]){
    int i = 0;
    for (i; input[i] != '\0'; i++) {
        if (input[i] == '\n') {
            input[i] = '\0';
        }
    }
    return input;
}

// This runs the command given that there is no piping
int runCommand(char argc[512]) {
    // Parses it
    char ** args = parseArgs(argc, " ");
    // printf("arg0:%s\n", args[1]);
    // Creates a child process
    int f = fork();
    // printf("int: %d\n", f);
    // int i = 0;
    // Checks if cd or exit are explicitly called, and if so runs the command
    exitcdCheck(args);
    // Only executes for one of the forked processes
    if (f == 0) {
        // printf("ARGUMENTS:\n");
        // for (int i = 0; args[i] != NULL; i ++) {
        //     printf("Arg: %s\n", args[i]);
        // }

	// Parsing arguments for a redirect character
	execvp(args[0], args);
    }
    else if (f ==-1) {
        return -1;
    }
    // Parent must wait to continue
    else {
        wait(NULL);
        freeMem(args);
    }
    if (errno != 0) {
        printf("Error: %s \n", strerror(errno));
        errno = 0;
    }
    // for (i; args[i]!=NULL; i++) {
    //     free(args[i]);
    // }
    // free(args);
}

// yay!
