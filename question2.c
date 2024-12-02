#include <unistd.h> 
#include <string.h>
#include <stdlib.h> // We include this to use functions like "exit"
#include <sys/wait.h> // We include this to use the "wait" function

#define WELCOME_MSG "Bienvenue dans le Shell ENSEA.\n"
#define PROMPT "enseash % "

void print_WELCOME_MSG() {
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
}

void print_PROMPT() {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

int main() {
    char command[1024]; // We use this array to store the user command input
    print_WELCOME_MSG(); // We print the initial welcome message when the shell starts

    // We create a loop to read and run user commands
    while (1) {
        print_PROMPT(); // We print the prompt to show that the shell is ready for input
        ssize_t number_characters = read(STDIN_FILENO, command, sizeof(command) - 1); // We read the user command from input

        command[number_characters - 1] = '\0'; // We change the last character from a new line to null

// We create a new process with fork()
        if (fork() == 0) {
            // In the child process, we run the command using "execlp"
            execlp(command, command, (char *)NULL);
            exit(-1); // If execlp fails, we exit the child process with error code -1
        } else {
            // In the parent process, we wait for the child to finish
            wait(NULL);
        }
    }
    return 0;
}