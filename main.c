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
#include "redir.h"

// Main part of the shell
int main(){
    int i = 0;
    int result = 0;
    char input[256];
    char ** argc = NULL;
    char dir[512];
    while (1) {
        // This gets the current directory we are in and prints it
        getcwd(dir, 512);
        printf("\n%s$ ", dir );
        // Takes commandline input
        fgets(input, 256, stdin);
        // Gets rid of the \n at the end
        cleanInput(input);
        printf("\n%s", input);
        printf("\n# of args: %d \n", charFreq(input, " ")); 
        // Parse by semicolons
        argc = parseArgs(input, ";");
        // For each parsed command separated by semicolons, run it
        for (i = 0; argc[i] != NULL; i++) {
            if (charFreq(argc[i], "|") > 1) {
                // If the command involves pipes, invoke the pipe method
                result = pipes(argc[i]);
            } else if (charFreq(argc[i], ">") > 1) {
		result = redirect_out(argc[i]);
	    } else if (charFreq(argc[i], "<") > 1) {
		result = redirect_in(argc[i]);
	    } else {
                // Otherwise, run the command normally
                result = runCommand(argc[i]);
            }
            // Handle cases in which we quit/ something breaks
            if (result == 0 || result == -1) {
                return result;
            }
        }
    }
    return 0;
}
