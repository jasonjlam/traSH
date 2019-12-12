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

int redirect_in(char args[256]){
    printf("Redir Type: <\n");
    char *argc = args;
    char **argv = parseArgs(argc, " ");
    int i = 0;
    for(; argv[i] != NULL; i++){
	printf("\t[%s]\n", argv[i]);	
    }
    return 1;
}

int redirect_out(char args[256]){
    printf("Redir Type: >\n");
    char *argc = args;
    char **argv = parseArgs(argc, " ");
    int i = 0;
    for(; argv[i] != NULL; i++){
	printf("\t[%s]\n", argv[i]);
    }
    return 1;
}

