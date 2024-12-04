#define _POSIX_C_SOURCE 199309L // Pour activer les fonctionnalités POSIX
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h> // Pour clock_gettime et CLOCK_MONOTONIC

#define WELCOME_MSG "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define PROMPT "enseash % "
#define EXIT_MSG "Bye bye...\n"

void print_WELCOME_MSG() {
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));
}

// Function to print the prompt and exit status or signal if any
void print_PROMPT(int status, long exec_time_ms) {
    // We check if the child process ended normally
    if (WIFEXITED(status)) {
        char exit_msg[50]; // We declare an array to store a message about the exit status of the child process
        int exit_code = WEXITSTATUS(status); // We retrieve the exit code of the child process from the status variable

        snprintf(exit_msg, sizeof(exit_msg), "[exit:%d|%ldms]", exit_code, exec_time_ms); // We format the exit message with the exit code
        write(STDOUT_FILENO, exit_msg, strlen(exit_msg)); // We print the exit message

    // We check if the child process was terminated by a signal
    } else if (WIFSIGNALED(status)){
        char signal_msg[50]; 
        int signal_code = WTERMSIG(status); 

        snprintf(signal_msg, sizeof(signal_msg), "[sign:%d|%ldms]", signal_code, exec_time_ms); // We format the signal message with the signal code
        write(STDOUT_FILENO, signal_msg, strlen(signal_msg)); // We print the signal message
    }
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT)); // We print the prompt after showing the exit status or signal
}

int main() {
    char command[1024];
    int status = 0;

    print_WELCOME_MSG();

    while (1) {
        struct timespec start_time, end_time; // Pour stocker les heures de début et de fin
        long exec_time_ms = 0; // Temps d'exécution en millisecondes

        // Afficher le prompt avec le temps d'exécution
        print_PROMPT(status, exec_time_ms);

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

        // Mesurer le temps avant de fork
        clock_gettime(CLOCK_REALTIME, &start_time);

        if (fork() == 0) {
            execlp(command, command, (char *)NULL);
            exit(-1);
        } else {
            waitpid(-1, &status, 0);

            // Mesurer le temps après que le processus enfant ait fini
            clock_gettime(CLOCK_REALTIME, &end_time);

            // Calculer le temps d'exécution en millisecondes
            exec_time_ms = (end_time.tv_sec - start_time.tv_sec) * 1000 +
                           (end_time.tv_nsec - start_time.tv_nsec) / 1000000;
        }

        // Afficher le prompt avec le temps d'exécution après chaque commande
        print_PROMPT(status, exec_time_ms);
    }
    return 0;
}
