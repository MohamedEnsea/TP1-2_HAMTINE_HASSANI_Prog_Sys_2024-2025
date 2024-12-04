#define _POSIX_C_SOURCE 199309L 
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>

#define WELCOME_MSG "Welcome to the ENSEA Shell.\nTo exit, type 'exit'.\n"
#define PROMPT "enseash % "
#define EXIT_MSG "Bye bye...\n"

void print_WELCOME_MSG() {
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG)); 
}

void print_PROMPT(int status, long exec_time_ms) {

    if (WIFEXITED(status)) { 
        char exit_msg[50];
        int exit_code = WEXITSTATUS(status);
        snprintf(exit_msg, sizeof(exit_msg), "[exit:%d|%ldms]", exit_code, exec_time_ms);
        write(STDOUT_FILENO, exit_msg, strlen(exit_msg)); 
    } else if (WIFSIGNALED(status)) { 
        char signal_msg[50];
        int signal_code = WTERMSIG(status); 
        snprintf(signal_msg, sizeof(signal_msg), "[sign:%d|%ldms]", signal_code, exec_time_ms);
        write(STDOUT_FILENO, signal_msg, strlen(signal_msg)); 
    }

    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

void split_command_into_args(char *input, char **argv) {
    char *token = strtok(input, " ");
    int index = 0;

    while (token != NULL) {
        argv[index++] = token; 
        token = strtok(NULL, " ");
    }
    argv[index] = NULL; 
}

int main() {
    char command[1024]; 
    char *argv[100];    
    int status = 0;     
    long exec_time_ms = 0; 

    print_WELCOME_MSG(); 

    while (1) { 
        struct timespec start_time, end_time; 

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

        clock_gettime(CLOCK_REALTIME, &start_time);

        split_command_into_args(command, argv);

        pid_t pid = fork(); 

        if (pid == 0) { 

            for (int i = 0; argv[i] != NULL; i++) {
                if (strcmp(argv[i], ">") == 0) { 
                    char *file_name = argv[i + 1]; 
                    int file_size = 0;
                    char buffer[1024];

                    while ((file_size = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
                        write(STDOUT_FILENO, buffer, file_size);
                    }
                    break;
                }
                if (strcmp(argv[i], "<") == 0) { 
                    char *file_name = argv[i + 1]; 
                    int file_size = 0;
                    char buffer[1024];
                    
                    while ((file_size = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
                        write(STDOUT_FILENO, buffer, file_size);
                    }
                    break;
                }
            }

            if (execvp(argv[0], argv) == -1) {
                perror("Command execution failed"); 
                exit(-1); 
            }
        } else if (pid > 0) { 
            waitpid(pid, &status, 0);

            clock_gettime(CLOCK_REALTIME, &end_time);

            exec_time_ms = (end_time.tv_sec - start_time.tv_sec) * 1000 +
                           (end_time.tv_nsec - start_time.tv_nsec) / 1000000;
        }
    }
    return 0; 
}