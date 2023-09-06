//Dan Saada 208968560
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_NUM_HISTORY_COMMANDS 100
#define MAX_COMMAND_LENGTH 100

//A struct for to store the data of the command's history and their PID
typedef struct {
    int pid;
    char* command;
} history;

/**
 * Reads a line of input from the user.
 *
 * @return A pointer to a string containing the user's input.
 */
char* getInput() {
    // Print a prompt to the user
    printf("$ ");
    fflush(stdout);

    //get input from the user
    char input[MAX_COMMAND_LENGTH];
    fgets(input, MAX_COMMAND_LENGTH, stdin);

    // Remove the trailing newline character
    input[strcspn(input, "\n")] = '\0';

    char *result = malloc((strlen(input) + 1) * sizeof(char));
    strcpy(result, input);
    return result;
}

/**
 * Tokenizes a command string into an array of strings.
 *
 * @param command the command string to tokenize
 * @param tokens an array of strings to hold the resulting tokens
 * @return the number of tokens
 */
int tokenize(char* command, char** tokens) {
    int numTokens = 0;
    char* token = strtok(command, " ");

    while (token != NULL && numTokens < MAX_COMMAND_LENGTH) {
        tokens[numTokens++] = token;
        token = strtok(NULL, " ");
    }
    tokens[numTokens] = NULL;
    return numTokens;
}

/**
 * Prints an error message for a failed command and exits the program.
 *
 * @param command A string representing the failed command.
 */
void commandFail(char* command) {
    char errorString[MAX_COMMAND_LENGTH];
    strcpy(errorString, command);
    strcat(errorString, " failed");
    perror(errorString);
    exit(1);
}

/**
 * Executes a command by searching for it in the given directory paths
 * and then creating a child process to execute the command.
 *
 * @param args An array of strings containing the command and its arguments.
 * @param history A pointer to the history struct.
 * @param historyCount A pointer to the history count variable.
 */
void execute_command(char** args, history* history, int* historyCount) {
    char command[MAX_COMMAND_LENGTH];
    strcpy(command, args[0]);

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        history[*historyCount].pid = getpid();
        execvp(args[0], args);

        //let the user know which command failed
        commandFail(command);
    } else if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else {
        // Parent process
        waitpid(pid, NULL, 0);
    }
}

/**
 * Executes a change directory command.
 *
 * @param command An array of strings containing the command and its arguments.
 */
void execute_cd(char** command) {
    if (command[1] == NULL) {
        printf("cd: missing argument\n");
    } else if (chdir(command[1]) != 0) {
        perror("chdir failed");
    }
}

/**
 * Prints the history of executed commands.
 *
 * @param history A pointer to the history struct.
 * @param historyCount A pointer to the history count variable.
 */
void execute_history(history *history, int* historyCount) {
    for (int i = 0; i <= *historyCount; i++) {
        printf("%d %s\n", history[i].pid, history[i].command);
    }
}

/**
 * Handles a command by either executing it or calling a built-in command.
 *
 * @param command An array of strings containing the command and its arguments.
 * @param history A pointer to the history struct.
 * @param historyCount A pointer to the history count variable.
 */
void handle_command(char **command, history* history, int *historyCount) {
    // Check if command is a built-in command
    if (strcmp(command[0], "cd") == 0) {
        history[*historyCount].pid = getpid();
        execute_cd(command);
    } else if (strcmp(command[0], "history") == 0) {
        history[*historyCount].pid = getpid();
        execute_history(history, historyCount);
    } else if (strcmp(command[0], "exit") == 0) {
        history[*historyCount].pid = getpid();
        exit(0);
    } else {
        execute_command(command, history, historyCount);
    }
    (*historyCount)++;
}

/**
 * Construct and set the updated PATH environment variable with directories containing the executables.
 */
void constructPath() {
    char* path_env = getenv("PATH");
    // Construct the updated PATH environment variable with directories containing the executables.
    char* new_path = "./";
    char* updated_path = malloc(strlen(path_env) + strlen(new_path) + 2);
    sprintf(updated_path, "%s:%s", new_path, path_env);

    // Set the updated PATH environment variable
    setenv("PATH", updated_path, 1);
    free(updated_path);
}

/**
 * Implements the main logic of the shell, repeatedly taking input from the user,
 * tokenizing it into an array of strings, and handling the command accordingly.
 *
 * @param history A pointer to the history struct.
 * @param historyCount A pointer to the history count variable.
 */
void shellLogic(history* history, int *historyCount) {
    constructPath();

    while (1) {
        // get command from the user.
        char* input = getInput();
        // add command to history.
        history[*historyCount].command = strdup(input);

        char* tokens[MAX_COMMAND_LENGTH];
        // the tokenize function returns the number of tokens the command is build of.
        if (tokenize(input, tokens) == 0) {
            continue;
        }
        handle_command(tokens, history, historyCount);
    }
}

int main(int argc, char const *argv[]) {
    history history[MAX_NUM_HISTORY_COMMANDS];
    int historyCount = 0;

    shellLogic(history, &historyCount);

    return 0;
}