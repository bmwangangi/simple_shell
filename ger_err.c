#include "main.h"

/**
 * get_error - used to get the error
 * @datash: the data containing the infomatuion
 * @eval: the value 
 * Return: error
 */
int get_error(data_shell *datash, int eval)
{
	char *problem;

	switch (eval)
	{
	case -1:
		problem = error_env(datash);
		break;
	case 126:
		problem = error_path_126(datash);
		break;
	case 127:
		problem = error_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			problem = error_exit_shell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			problem = error_get_cd(datash);
		break;
	}

	if (problem)
	{
		write(STDERR_FILENO, problem, _strlen(problem));
		free(problem);
	}

	datash->status = eval;
	return (eval);
}
