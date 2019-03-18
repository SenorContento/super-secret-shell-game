#include <stdio.h>
#include <string.h>

// This game will be part of my super secret challenge :) !!!

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("You need to specify the IP Address!!!\n");
    return 1;
  }

  printf("Welcome to the game %s!!!\n", argv[1]);

  char command[50];
  char* result = NULL;
  while(result == NULL) { //for(;;) {
    printf("-> ");
    result = fgets(command, sizeof(command), stdin);

    result = NULL;
    if (command[strlen(command) - 1] != '\n') {
      // https://www.geeksforgeeks.org/why-to-use-fgets-over-scanf-in-c/
      fseek(stdin, 0, SEEK_END);
      fprintf(stderr, "Sorry, but you are limited to %lu characters!!!\n", strlen(command));
      //printf("Result: %s", result);
      result = NULL;
      command[0] = 0;
      //break;
    }

    if(!strcmp(command, "exit")) {
      return 0;
    }

    if(command[strlen(command) - 1] != 0) {
      printf("Command: %s", command);
      fseek(stdin, 0, SEEK_END);
    }
  }

  return -1;
}