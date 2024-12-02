#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h> 

#define WELCOME_MSG "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define PROMPT "enseash % \n"
#define EXIT_MSG "Bye bye...\n" // We define the exit message.

void print_WELCOME_MSG() {
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
}

void print_PROMPT() {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

int main() {
    char command[1024];
    print_WELCOME_MSG();

    while (1) {
        print_PROMPT();
        ssize_t number_characters = read(STDIN_FILENO, command, sizeof(command) - 1);

        if (number_characters == 0) {
            write(STDOUT_FILENO, EXIT_MSG, strlen(EXIT_MSG)); // We print the exit message when the user exits with Ctrl+D.
            break; // We break out of the loop to end the shell.
        }

        command[number_characters - 1] = '\0';

        if (strcmp(command, "exit") == 0) {
            write(STDOUT_FILENO, EXIT_MSG, strlen(EXIT_MSG)); // We print the exit message when the user exits with "exit"
            break; // We break out of the loop to end the shell.
        }

        if (fork() == 0) {
            execlp(command, command, (char *)NULL);
            exit(-1);
        } else {
            wait(NULL);
        }
    }
    return 0;
}