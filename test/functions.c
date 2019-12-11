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

int main(){
    return 0;
}


// WARNING: RETURNS A TRIPLE CHAR POINTER (A POINTER TO AN ARRAY OF ARRAYS OF STRINGS)
// THIS FUNCTION USES DYNAMICALLY ALLOCATED MEMORY (MUST BE FREED)
char ***cmds_to_run(char *line){
    // Making to_return triple array
    char ***to_return = malloc(sizeof(char***));
    
}
