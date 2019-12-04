#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>




int charFreq(char *input, char *delim){
  int i = 0;
  int count = 0;
  for(; input[i] != '\0'; i++){
	if( *delim == input[i] ){
	  count++;
	}
  }
  return count;
}


int main(){
  printf("\n& ");
  char input[256];
  fgets(input, 256, stdin);
  printf("\n%s", input);
  printf("\n# of args: %d", charFreq(input, " "));
  return 0;
}

// char **parseArgs(char *input){
//  char *line = input;
// char *token;
  // int size = 0;
  // while( token != NULL ){
  // token = stresep(&line, " ");
  // size++;
  // }
  // printf("\nSize: %d", size)
// }

