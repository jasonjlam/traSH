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
    char ** argv = calloc(sizeof(char *), size + 1);
    for (i; i < size; i++) {
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
