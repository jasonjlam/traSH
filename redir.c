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
    command[j] = NULL;

    filename = argv[j+1];
    printf("File Name:\n");
    printf("\t[%s]\n", filename);
    int pid = fork();
    printf("%d\n", pid);
    if (pid == 0) {
	if(strcmp(redir_type, ">") == 0){
	    // printf("child\n");
	    int stdout = dup(1);
	    // printf("Temporary out: [%d]\n", stdout);
	    int file = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 00644);
	    // printf("File: [%d]\n", file);
	    dup2(file, 1);
	    int s = execvp(command[0], command);
	    dup2(stdout, 1);

	    close(file);
	} else if (strcmp(redir_type, "<") == 0) {
	    // printf("child\n");
	    int stdin = dup(0);
	    // printf("Temporary out: [%d]\n", stdout);
	    int file = open(filename, O_RDONLY | O_EXCL);
	    // printf("File: [%d]\n", file);
	    dup2(file, 0);
	    execvp(command[0], command);
	    dup2(stdin, 0);

	    close(file);

	} else {
	    // Return an error
	}
    } else if(pid > 0){
	wait(NULL);
    }

    return 1;
}
// Checks if < or > occurs in the double redirect first.
// Returns 0 if > occurs first, 1 if < occurs first, or -1 if neither are found.
int redirCheck (char arg[256]) {
    int i = 0;
    for (i; i < strlen(arg); i ++) {
        if (strcmp(&arg[i], ">")) {
            return 0;
        }
        if (strcmp(&arg[i], "<")) {
            return 1;
        }
        else {
            return -1;
        }
    }
}
void redirect_both (char args[256]){
    int i = 0;
    char *argc = args;
    char *cmds[3];
    char *token = "";
    for (i; argc != NULL; i++) {
    	cmds[i] = strsep(&argc, "<>");
    }
    for (i = 0; i < 3; i ++) {
        printf("redir test: %d, %s \n", i, cmds[i]);
    }
    char **command = parseArgs(cmds[0], " ");
    cmds[1] +=1;
    cmds[2] +=1;
    for (i = 0; i < 3; i ++) {
        printf("args: %d, %s \n", i, command[i]);
    }
    char* fileIn = NULL;
    char* fileOut = NULL;
    if (redirCheck) {
        fileIn = cmds[1];
        fileOut = cmds[2];
    }
    else {
        fileIn = cmds[2];
        fileOut = cmds[1];
    }
    printf("Filein%s\n", fileIn);
    printf("Fileout%s \n", fileOut);
    int pid = fork();
    printf("%d\n", pid);
    int stdin = dup(0);
    int stdout = dup(1);
    int redirOut = open(fileOut, O_CREAT|O_WRONLY|O_TRUNC, 0755);
    if (redirOut == -1) {
            redirOut = open(fileOut, O_WRONLY|O_TRUNC);
    }
    int redirIn = open(fileIn, O_RDONLY);
    if (pid = 0) {
        // printf("Temporary out: [%d]\ntr a-z A-Z < wholist > foo", stdout);
        // printf("File: [%d]\n", file);
        dup2(redirIn, 0);
		dup2(redirOut, 1);
        close(redirIn);
        close(redirOut);
        // printf("Temporary out: [%d]\n", stdout);
        // printf("File: [%d]\n", file);
        execvp(command[0], command);
        if (errno != 0) {
            printf("Error: %s \n", strerror(errno));
            errno = 0;
        }
        dup2(stdin, 0);
        dup2(stdout, 1);
    }
    else {
        wait(NULL);
    }

}
