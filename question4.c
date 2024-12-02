#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h> // We include this to use the "snprintf" function

#define WELCOME_MSG "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define PROMPT "enseash % "
#define EXIT_MSG "Bye bye...\n"

void print_WELCOME_MSG() {
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
}

// Function to print the prompt and exit status or signal if any
void print_PROMPT(int status) {
    // We check if the child process ended normally
    if (WIFEXITED(status)) {
        char exit_msg[50]; // We declare an array to store a message about the exit status of the child process
        int exit_code = WEXITSTATUS(status); // We retrieve the exit code of the child process from the status variable

        snprintf(exit_msg, sizeof(exit_msg), "[exit:%d] ", exit_code); // We format the exit message with the exit code
        write(STDOUT_FILENO, exit_msg, strlen(exit_msg)); // We print the exit message

    // We check if the child process was terminated by a signal
    } else if (WIFSIGNALED(status)){
        char signal_msg[50]; 
        int signal_code = WTERMSIG(status); 

        snprintf(signal_msg, sizeof(signal_msg), "[sign:%d] ", signal_code); // We format the signal message with the signal code
        write(STDOUT_FILENO, signal_msg, strlen(signal_msg)); // We print the signal message
    }
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT)); // We print the prompt after showing the exit status or signal
}

int main() {
    char command[1024];
    int status = 0;

    print_WELCOME_MSG();

    while (1) {

        print_PROMPT(status); // We print the prompt at the beginning of each loop iteration
        ssize_t number_characters = read(STDIN_FILENO, command, sizeof(command) - 1);

        if (number_characters == 0) {
            write(STDOUT_FILENO, EXIT_MSG, strlen(EXIT_MSG));
            break; 
        }

        command[number_characters - 1] = '\0';

        if (strcmp(command, "exit") == 0) {
            write(STDOUT_FILENO, EXIT_MSG, strlen(EXIT_MSG));
            break;
        }

        if (fork() == 0) {
            execlp(command, command, (char *)NULL);
            exit(-1);
        } else {
            waitpid(-1, &status, 0);
        }
    }
    return 0;
}