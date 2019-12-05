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

char **parseArgs(char *input){
    char *line = input;
    char *token;
    int i = 0;
    int size = charFreq(input, " ");
    char ** argv = calloc(sizeof(char *), size + 1);
    for (i; i < size; i++) {
        token = strsep(&line, " ");
        argv[i] = malloc(sizeof(char[strlen(token)]));
        argv[i] = token;
        printf("%s\n", argv[i]);
    }
    argv[size] = NULL;
    return argv;
    // printf("\nSize: %d", size)
}

int main(){
    int i = 0;
    int size = 0;
    char input[256];
    while (1) {
        printf("\n& ");
        fgets(input, 256, stdin);
        for (i; input[i] != '\0'; i++) {
            if (input[i] == '\n') {
                input[i] = '\0';
            }
        }
        printf("\n%s", input);
        printf("\n# of args: %d \n", charFreq(input, " "));
        char ** argv = parseArgs(input);
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
