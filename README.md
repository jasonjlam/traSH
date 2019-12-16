
```
    /$$                          /$$$$$$  /$$   /$$
   | $$                         /$$__  $$| $$  | $$
  /$$$$$$    /$$$$$$   /$$$$$$ | $$  \__/| $$  | $$
 |_  $$_/   /$$__  $$ |____  $$|  $$$$$$ | $$$$$$$$
   | $$    | $$  \__/  /$$$$$$$ \____  $$| $$__  $$
   | $$ /$$| $$       /$$__  $$ /$$  \ $$| $$  | $$
   |  $$$$/| $$      |  $$$$$$$|  $$$$$$/| $$  | $$
    \___/  |__/       \_______/ \______/ |__/  |__/
```
## **traSH** - the really awesome Shell
by Jason Lam and Joseph Yusufov
***

### Features
- Forks and exectues commands, as expected.
- Changes working directory with `cd`
- Parses multiple commands on one line with a `;`
- Redirects input with `<`
- Redirects output with `>`
- Whitespace-blind: leave as many spaces as you'd like
- Pipes information between processes with `|`
- Exits with the `exit` command.

### Attempted, but not fully functional
- Redirection without truncation (e.g. `<<` and `>>`)
- Arrow key navigation
- Double redirection (e.g. `tr a-z A-Z < wholist > foo`)
- Negotiations with Microsoft **did not ultimately lead to the sale** of traSH

### Bugs
- Changing directory into a named directory, rather than using `.` or `..`, will give an error, however will still change the working directory as expected. 
- The last argument in a double redirection command gets truncated 2 characters short of where it should be (as a result, double redirection is in the *Attempted* category).

### Files and Function Headers
##### **main.c** -- The file containing main. Runs the shell, recieves input, and redirects it to the relevant handler processes  
- `int main();`
    - Prints awesome ASCII Art 
    - Accepts input using 'fgets()'
    - Calls 'parseArgs()' to parse commands seperated by a ';'
    - Checks to see whether or not input includes a special operator (e.g. <, >, |), and invokes proper functions
    - Otherwise, invokes the 'runCommand()' function 
##### **shell.c** -- Helper functions, special conditions, and parser functions that make *main.c* look pretty
- `int charFreq(char *input, char *delim);`
    - Takes a string to be parsed, and a string containing delimeters to parse by.
    - Returns the number of *delim*s present in *input*
    - Helper function for *parseArgs()*
- `char **parseArgs(char *input, char *separator);`
    - Takes a string to be parsed, and a string containing delimeters to parse by
    - Returns an array of strings - *a char double pointer* - containing the the string broken up into sections by the provided delimeter.
    - When a *space* is passed as the delimeter, *parseArgs()* returns an array of strings with all whitespace removed.
    - Used twice: once to parse by semicolons, and once to parse whitespace
- `char *cleanInput(char input[512]);`
    - Replaces any newline - *\n* - characters at the end of a string with null - *\0* -  characters.
    - Overall useful function for making sure all strings are null-terminated.
- `int runCommand(char argc[512]);`
    - Returns 1 if things went well, otherwise returns -1.
    - When passed a string, runCommand uses *parseArgs()* to distill the *argc* into an array of arguments.
    - Forks, and executes the command as parsed by *parseArgs()* using *execvp()*.
    - Checks for special commands, like *cd* and *exit*, for which *execvp()* is not used. Invokes special functions in *cmds.c* to handle these cases.
##### **redir.c** -- Handle all redirection and data transfer between process, including pipes and input / output redirection.
- `int pipes(char argc[256]);`
    - Returns 1 if all is good, otherwise returns -1.
    - When passed a string with a vertical bar, opens an unnamed pipe between the argument on the left of the pipe and on the right of the pipe using *popen()* and *pclose()*.
    - Checks for a null pipe.
- `int redirect(char args[256], char *redir_type);`
    - Takes a string containing **ONE** redirection character, and a string containing the type of redirection (< or >).   
    - Splits command into two parts, then parses args using *parseArgs()* as is standard in our shell.
    - Manipulates file table to redirect input / output, forks, executes the command, and then replaces STDIN and STDOUT in their rightful places.
    - Creates files if they do not already exist, and overwrites them if they do.
- `int redirect_both(char args[512]);`
    - Very similar to *redirect()*, except takes a string with two redirects ( foo < loo > shoe), and ideally, does the proper redirection.
    - Currently **not working** because of a string truncation error, but regarding file table manipulation, the developers are aware of the proper steps to be taken.
##### **cmds.c** -- A small file with functions to handle a few commands, such as cd and exit.
- `void cd(char *dir);`
    - Changes working directory to the one provided in the string parameter.
    - Uses the *chdir()* system call.
    - Helper function for *exitcdCheck()*.
- `void exitcdCheck(char ** args);`
    - Checks if the argument array's first element is either 'exit', or 'cd'
    - Exits the shell when appropriate, and calls the *cd()* function when appropriate.






