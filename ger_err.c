#include "main.h"

/**
 * get_error - used to get the error
 * @datashel: the data containing the infomatuion
 * @evaluate: the value
 * Return: error
 */
int get_error(d_shell *datashel, int evaluate)
{
	char *problem;

	switch (evaluate)
	{
	case -1:
		problem = error_env(datashel);
		break;
	case 126:
		problem = error_path_126(datashel);
		break;
	case 127:
		problem = error_not_found(datashel);
		break;
	case 2:
		if (_strcmp("exit", datashel->args[0]) == 0)
			problem = error_exit_shell(datashel);
		else if (_strcmp("cd", datashel->args[0]) == 0)
			problem = error_get_cd(datashel);
		break;
	}

	if (problem)
	{
		write(STDERR_FILENO, problem, _strlen(problem));
		free(problem);
	}

	datashel->status = evaluate;
	return (evaluate);
}
