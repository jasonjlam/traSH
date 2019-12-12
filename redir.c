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

// Runs commands dealing with pipes
int pipes(char argc[256]) {
    int i = 0;    
    // File descriptor we use for pipes
    FILE *pipe;
    char* arg = argc;
    // Opens a simple pipe using the arg
    pipe = popen(arg, "w");
    // String we write to
    char output[512];
    // Null safety check
    if (pipe == NULL){
        printf("Failed to pipe commands\n");
        return -1;
    }
    // Otherwise if everything is good we print out the output
    else if (fgets(output, 512, pipe)!= NULL){
        printf("%s", output);
    }
    // Don't forget to close the pipe
    pclose(pipe);
    return 1;
}

// Handle redirect stdin requests
int redirect(char args[256], char *redir_type){
    printf("Redir Type: %s\n", redir_type);
    char *argc = args;
    int size = charFreq(argc, " ");
    char **argv = parseArgs(argc, " ");
    char *command[size - 2];
    char *filename;
    int i = 0;
    int j = 0;
    for(; i < size; i++){
	printf("\t[%s]\n", argv[i]);	
    }

    printf("Command:\n");
    for(; strcmp(argv[j], redir_type) != 0; j++){
	command[j] = argv[j];
	printf("\t[%s]\n", command[j]);
    }
    command[j] = "\0";

    filename = argv[j+1];    
    printf("File Name:\n");    
    printf("\t[%s]", filename);
    //sleep(1);
    int f = fork();
    printf("%d\n", f);
    if (f == 0) {
	printf("child");
	int stdout = dup(1);
	printf("Temporary out: [%d]", stdout);
	int file = open(filename, O_TRUNC);
	dup2(file, 1);
	printf("file becomes stdout...");
	execvp(command[0], command);
	dup2(1, stdout);
	printf("making stdout stdout again...");
	close(file);
    } else if(f > 0){
	wait(NULL);
    }
    
    return 1;
}

