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
void handle_signal(int sgn_no);

/*
 * display_prompt - used  to displa the dollar sign
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
	char *insert_line = NULL;
	size_t the_buffer_size = 0;

	if (getline(&insert_line, &the_buffer_size, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(insert_line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(insert_line);
			perror("Error reading the line from stdin");
			exit(EXIT_FAILURE);
		}
	}

	return (insert_line);
}

/**
 * tokenize_input - used to tokenize input
 * @input_line: The line
 * Return: array
 */
char **tokenize_input(char *input_line)
{
	int the_buffer_size = MAX_ARGS, position = 0;
	char **tokenization = malloc(the_buffer_size * sizeof(char *));
	char *token;

	if (!tokenization)
	{
		perror("Allocation error in tokenize_input");
		exit(EXIT_FAILURE);
	}

	token = strtok(input_line, " \t\r\n\a");
	while (token != NULL)
	{
		tokenization[position] = token;
		position++;

		if (position >= the_buffer_size)
		{
			the_buffer_size += MAX_ARGS;
			tokenization = realloc(tokenization, the_buffer_size * sizeof(char *));
			if (!tokenization)
			{
				perror("Reallocation error in tokenize_input");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\r\n\a");
	}

	tokenization[position] = NULL;
	return (tokenization);
}

/**
 * execute_command - Execute a command with arguments
 *
 * @arguments: The arguments
 * @exit_code: Pointer to the exit
 */
void execute_command(char **arguments, int *exit_code)
{
	pid_t process_id;
	int the_process;

	if (strcmp(arguments[0], "exit") == 0)
	{
		*exit_code = 1;
		return;
	}

	process_id = fork();

	if (process_id == 0)
	{
		if (execvp(arguments[0], arguments) == -1)
		{
			perror("Error executing command");
			*exit_code = 1;
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else if (process_id < 0)
	{
		perror("Error forking");
		*exit_code = 1;
	}
	else
	{
		do {
			process_id = waitpid(process_id, &the_process, WUNTRACED);
		} while (!WIFEXITED(the_process) && !WIFSIGNALED(the_process));
	}
}

/**
 * is_builtin_command - Check if is a built in command
 *
 * @arg: The arguments
 * Return: 1
 */
int is_builtin_command(char **arg)
{
	const char *builtin_commands[] = {"cd", "pwd", "exit"};
	size_t sharon;
	size_t trab = sizeof(builtin_commands) / sizeof(builtin_commands[0]);

	for (sharon = 0; sharon < trab; sharon++)
	{
		if (strcmp(arg[0], builtin_commands[sharon]) == 0)
		{
			return (1);
		}
	}

	return (0);
}

/**
 * handle_signal - Handle signals
 *
 * @sgn_no: The signal number
 */
void handle_signal(int sgn_no)
{
	if (sgn_no == SIGINT)
	{
		printf("\n");
		display_prompt();
		fflush(stdout);
		exit(EXIT_SUCCESS);
	}
}

