#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>

// Readline Library
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

// This game will be part of my super secret challenge :) !!!

// Set If Using Library with Command Line Argument: -DREADLINE_LIBRARY
/*#ifndef READLINE_LIBRARY
  #define READLINE_LIBRARY
#endif*/

/* Colors: http://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
Black: \u001b[30m
Red: \u001b[31m
Green: \u001b[32m
Yellow: \u001b[33m
Blue: \u001b[34m
Magenta: \u001b[35m
Cyan: \u001b[36m
White: \u001b[37m
Reset: \u001b[0m
*/

// https://stackoverflow.com/a/3219471/6828099
bool colors = true;
#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void signalCatch(int);
int execute(char*);

int execute(char* command) {
  if(!strcmp(command, "date")) {
    // Mon Mar 18 02:03:53 UTC 2019
    // https://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm
    time_t t = time(NULL);
    struct tm tm = *gmtime(&t); // localtime for computer's local time

    char date[50];
    strftime(date, sizeof(date), "%a %b %d %I:%M:%S %Z %Y", &tm);

    //printf("%d", colors); // https://stackoverflow.com/a/17307307/6828099
    if(colors) {
      printf(ANSI_COLOR_CYAN "%s\n" ANSI_COLOR_RESET, date);
    } else {
      printf("%s\n", date);
    }
    return 0;
  }

  if(!strcmp(command, "help")) {
    if(colors) {
      printf(ANSI_COLOR_RED "The Help Command Does Not Exist Yet!!!\n" ANSI_COLOR_RESET);
    } else {
      printf("The Help Command Does Not Exist Yet!!!\n");
    }
    return 0;
  }

  return 1;
}

int main(int argc, char *argv[])
{
  signal(SIGINT, signalCatch);
  if (argc < 2) {
    if(colors) {
      printf(ANSI_COLOR_RED "You need to specify the IP Address!!!\n" ANSI_COLOR_RESET);
    } else {
      printf("You need to specify the IP Address!!!\n");
    }
    return 1;
  }

  if(argc == 3) {
    if(!strcmp(argv[2], "--nocolor")) {
      colors = false;
    }
  }

  if(colors) {
    printf(ANSI_COLOR_CYAN "Welcome to the game %s!!!\n" ANSI_COLOR_RESET, argv[1]);
  } else {
    printf("Welcome to the game %s!!!\n", argv[1]);
  }

  // Setup Command Character
  #if defined (READLINE_LIBRARY)
    char* command;
  #else
    char command[50];
  #endif

  char* prompt = NULL;
  if(colors) {
    prompt = ANSI_COLOR_RED "-> " ANSI_COLOR_RESET;
  } else {
    prompt = "-> ";
  }

  char* result = NULL;
  while(result == NULL) { //for(;;) {
    // Read User Input
    #if defined (READLINE_LIBRARY)
      // https://en.wikipedia.org/wiki/GNU_Readline
      // Display prompt and read input
      command = readline(prompt);

      // Check for EOF.
      if(!command)
        break;

      // Add input to history.
      add_history(command);
    #else
      printf("%s", prompt);
      result = fgets(command, sizeof(command), stdin);

      result = NULL;
      if(command[strlen(command) - 1] != '\n') {
        // https://www.geeksforgeeks.org/why-to-use-fgets-over-scanf-in-c/
        fseek(stdin, 0, SEEK_END);

        if(colors) {
          fprintf(stderr, ANSI_COLOR_RED "Sorry, but you are limited to %lu characters!!!\n" ANSI_COLOR_RESET, strlen(command));
        } else {
          fprintf(stderr, "Sorry, but you are limited to %lu characters!!!\n", strlen(command));
        }
        //printf("Result: %s", result);
        result = NULL;
        command[0] = 0;
        //break;
      }

      // "Remove" Newline from command
      command[strlen(command) - 1] = 0;
    #endif

    // Process Command
    if(colors) {
      printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET, command);
    } else {
      printf("%s\n", command);
    }

    if(!strcmp(command, "exit")) { // May add custom error codes here
      return 0;
    }

    if(execute(command)) {
      if(colors) {
        fprintf(stderr, ANSI_COLOR_RED "Command Not Found!!!\n" ANSI_COLOR_RESET);
      } else {
        fprintf(stderr, "Command Not Found!!!\n");
      }
    }
    // End Process Command

    // Clean Up Input
    #if defined (READLINE_LIBRARY)
      // Free input.
      free(command);
    #else
      fseek(stdin, 0, SEEK_END);
    #endif
  }

  return -1;
}

// https://stackoverflow.com/a/4217070/6828099
void signalCatch(int sig) {
  printf("\n");

  if(colors) {
    printf(ANSI_COLOR_YELLOW "Signal Interrupt\n" ANSI_COLOR_RESET);
  } else {
    printf("Signal Interrupt\n");
  }

  exit(0);
}