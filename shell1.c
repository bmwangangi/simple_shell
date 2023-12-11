#include "shell.h"

#define MAX_INPUT_LEN 1024
#define MAX_ARGS 64

/**
 *The  Function prototypes
 */
void display_prompt(void);
char *read_input();
char **tokenize_input(char *input_line);
void execute_command(char **arguments, int *exit_status);
int is_builtin_command(char **arguments);
void handle_signal(int signal_number);

/**
 * main - Is the main entry point for the shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *input_line;
	char **arguments;
	int exit_status = 0;  /* Add an exit status variable */

	/* Register signal handlers for Ctrl+C and Ctrl+Z */
	signal(SIGINT, handle_signal);
	signal(SIGTSTP, SIG_IGN);  /* Ignore Ctrl+Z for now */

	while (!exit_status)  /* Change the exit condition */
	{
		display_prompt();
		input_line = read_input();
		arguments = tokenize_input(input_line);

		if (arguments[0] != NULL)
		{
			if (is_builtin_command(arguments))
			{
				/* Execute built-in command */
				execute_command(arguments, &exit_status);  /* Pass the exit_statu */
			}
			else
			{
				/* Execute external command */
				execute_command(arguments, &exit_status);  /* Pass the exit_status */
			}
		}

		free(input_line);
		free(arguments);
	}

	return (0);
}

/**
 * display_prompt - Display the shell prompt
 */
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);  /* Flush the output to ensure it's displayed immediately */
}

/**
 * read_input - Read a line from standard input
 *
 * Return: The line read from stdin
 */
char *read_input()
{
	char *input_line = NULL;
	size_t buffer_size = 0;

	if (getline(&input_line, &buffer_size, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(input_line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(input_line);
			perror("Error reading the line from stdin");
			exit(EXIT_FAILURE);
		}
	}

	return (input_line);
}

/**
 * tokenize_input - Tokenize a line into arguments
 *
 * @input_line: The line to be tokenized
 * Return: An array of tokens
 */
char **tokenize_input(char *input_line)
{
	int buffer_size = MAX_ARGS, position = 0;
	char **tokens = malloc(buffer_size * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("Allocation error in tokenize_input");
		exit(EXIT_FAILURE);
	}

	token = strtok(input_line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= buffer_size)
		{
			buffer_size += MAX_ARGS;
			tokens = realloc(tokens, buffer_size * sizeof(char *));
			if (!tokens)
			{
				perror("Reallocation error in tokenize_input");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\r\n\a");
	}

	tokens[position] = NULL;
	return (tokens);
}

/**
 * execute_command - Execute a command with arguments
 *
 * @arguments: The arguments of the command
 * @exit_status: Pointer to the exit status variable
 */
void execute_command(char **arguments, int *exit_status)
{
	pid_t process_id;  /* Remove unused variable wait_process_id */
	int process_status;

	if (strcmp(arguments[0], "exit") == 0)
	{
		*exit_status = 1;  /* Set exit status*/
		return;
	}

	process_id = fork();

	if (process_id == 0)
	{
		/* Child process */
		if (execvp(arguments[0], arguments) == -1)
		{
			perror("Error executing command");
			*exit_status = 1;  /* Set exit status to indicate an error */
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);  /* Indicate a successful exit */
	}
	else if (process_id < 0)
	{
		/* Forking error */
		perror("Error forking");
		*exit_status = 1;  /* Set exit status to indicate an error */
	}
	else
	{
		/* Parent process */
		do {
			process_id = waitpid(process_id, &process_status, WUNTRACED);
		} while (!WIFEXITED(process_status) && !WIFSIGNALED(process_status));
	}
}

/**
 * is_builtin_command - Check if the command is a built-in command
 *
 * @arguments: The arguments of the command
 * Return: 1 if the command is built-in, 0 otherwise
 */
int is_builtin_command(char **arguments)
{
	const char *builtin_commands[] = {"cd", "pwd", "exit"};
	size_t index;  /* Change the type to size_t */
	size_t trab = sizeof(builtin_commands) / sizeof(builtin_commands[0]);

	for (index = 0; index < trab; index++)
	{
		if (strcmp(arguments[0], builtin_commands[index]) == 0)
		{
			return (1);
		}
	}

	return (0);
}

/**
 * handle_signal - Handle signals
 *
 * @signal_number: The signal number
 */
void handle_signal(int signal_number)
{
	if (signal_number == SIGINT)
	{
		/* Handle Ctrl+C signal */
		printf("\n");
		display_prompt();
		fflush(stdout);
		exit(EXIT_SUCCESS);  /* Exit the shell on Ctrl+C */
	}
}

