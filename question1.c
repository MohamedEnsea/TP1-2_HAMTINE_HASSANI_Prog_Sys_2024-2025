#include <string.h>
#include <unistd.h> // We include this to use the write function

#define WELCOME_MSG "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n" // We define the message that will welcome the user
#define PROMPT "enseash % \n" // We define what the shell prompt 

// Function to display the welcome message
void print_WELCOME_MSG() {
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG)); // We use write function to send the welcome message to the terminal
// STDOUT_FILENO is the standard output. He is in the <unistd.h> library.
}

// Function to display the prompt
void print_prompt(){
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}
// The program starts in the main function
int main(){
    print_WELCOME_MSG(); // We call the function to print the welcome message
    print_prompt(); // Then we call the function to print the prompt
    return 0;
}
