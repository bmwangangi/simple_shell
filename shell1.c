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
 * main - This is the entry point for the shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *insert_line;
	char **arguments;
	int exit_sts = 0;

	signal(SIGINT, handle_signal);
	signal(SIGTSTP, SIG_IGN);

	while (!exit_sts)
	{
		display_prompt();
		insert_line = read_input();
		arguments = tokenize_input(insert_line);

		if (arguments[0] != NULL)
		{
			if (is_builtin_command(arguments))
			{
				execute_command(arguments, &exit_sts);
			}
			else
			{
				execute_command(arguments, &exit_sts);
			}
		}

		free(insert_line);
		free(arguments);
	}

	return (0);
}

/**
 * display_prompt - used to displa the dollar sign
 */
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}

/**
 * read_input - used to read line from stdin
 *
 * Return: the line read
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
 * tokenize_input - used to tokenize input
 * @input_line: The line 
 * Return: array
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
 * @arguments: The arguments
 * @exit_status: Pointer to the exit
 */
void execute_command(char **arguments, int *exit_status)
{
	pid_t process_id;
	int process_status;

	if (strcmp(arguments[0], "exit") == 0)
	{
		*exit_status = 1;
		return;
	}

	process_id = fork();

	if (process_id == 0)
	{
		if (execvp(arguments[0], arguments) == -1)
		{
			perror("Error executing command");
			*exit_status = 1;
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else if (process_id < 0)
	{
		perror("Error forking");
		*exit_status = 1;
	}
	else
	{
		do {
			process_id = waitpid(process_id, &process_status, WUNTRACED);
		} while (!WIFEXITED(process_status) && !WIFSIGNALED(process_status));
	}
}

/**
 * is_builtin_command - Check if is a built in command
 *
 * @arguments: The arguments 
 * Return: 1
 */
int is_builtin_command(char **arguments)
{
	const char *builtin_commands[] = {"cd", "pwd", "exit"};
	size_t index;
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
		printf("\n");
		display_prompt();
		fflush(stdout);
		exit(EXIT_SUCCESS);
	}
}

