#include "main.h"

/**
 * swap_char - | and & swaps for non-prnted char
 * @input: string inp
 * @bool: swap type
 * Return: str swapped
 */
char *swap_char(char *input, int bool)
{
	int j;

	if (bool == 0)
	{
		for (j = 0; input[j]; j++)
		{
			if (input[j] == '|')
			{
				if (input[j + 1] != '|')
					input[j] = 16;
				else
					j++;
			}

			if (input[j] == '&')
			{
				if (input[j + 1] != '&')
					input[j] = 12;
				else
					j++;
			}
		}
	}
	else
	{
		for (j = 0; input[j]; j++)
		{
			input[j] = (input[j] == 16 ? '|' : input[j]);
			input[j] = (input[j] == 12 ? '&' : input[j]);
		}
	}
	return (input);
}

/**
 * add_nodes - add separators $ command lines
 * @head_s: sep list head
 * @head_l: cmd lines inp head
 * @input: str inp
 * Return: return 0
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int j;
	char *lin;

	input = swap_char(input, 0);

	for (j = 0; input[j]; j++)
	{
		if (input[j] == ';')
			add_sep_node_end(head_s, input[j]);

		if (input[j] == '|' || input[j] == '&')
		{
			add_sep_node_end(head_s, input[j]);
			j++;
		}
	}

	lin = _strtok(input, ";|&");
	do {
		lin = swap_char(lin, 1);
		add_line_node_end(head_l, lin);
		lin = _strtok(NULL, ";|&");
	} while (lin != NULL);

}

/**
 * go_next - go to stored next cmd line
 * @list_s: sep list
 * @list_l: cmd line lst
 * @datash: data struc
 * Return: return 0
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loopsep;
	sep_list *lss;
	line_list *lsl;

	loopsep = 1;
	lss = *list_s;
	lsl = *list_l;

	while (lss != NULL && loopsep)
	{
		if (datash->status == 0)
		{
			if (lss->separator == '&' || lss->separator == ';')
				loopsep = 0;
			if (lss->separator == '|')
				lsl = lsl->next, lss = lss->next;
		}
		else
		{
			if (lss->separator == '|' || lss->separator == ';')
				loopsep = 0;
			if (lss->separator == '&')
				lsl = lsl->next, lss = lss->next;
		}
		if (lss != NULL && !loopsep)
			lss = lss->next;
	}

	*list_s = lss;
	*list_l = lsl;
}

/**
 * split_commands - splits cmd lines
 * executes the separators ;, | and &
 * @datash: data struc
 * @input: str inp
 * Return: 0 to quit, 1 to proceed
 */
int split_commands(data_shell *datash, char *input)
{

	sep_list *heads, *lists;
	line_list *headl, *listl;
	int loop;

	heads = NULL;
	headl = NULL;

	add_nodes(&heads, &headl, input);

	lists = heads;
	listl = headl;

	while (listl != NULL)
	{
		datash->input = listl->line;
		datash->args = split_line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		go_next(&lists, &listl, datash);

		if (listl != NULL)
			listl = listl->next;
	}

	free_sep_list(&heads);
	free_line_list(&headl);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - inp str token
 * @input: str inp
 * Return: splitted str
 */
char **split_line(char *input)
{
	size_t bsiz;
	size_t j;
	char **tokns;
	char *tokn;

	bsiz = TOK_BUFSIZE;
	tokns = malloc(sizeof(char *) * (bsiz));
	if (tokns == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	tokn = _strtok(input, TOK_DELIM);
	tokns[0] = tokn;

	for (j = 1; tokn != NULL; j++)
	{
		if (j == bsiz)
		{
			bsiz += TOK_BUFSIZE;
			tokns = _reallocdp(tokns, j, sizeof(char *) * bsiz);
			if (tokns == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		tokn = _strtok(NULL, TOK_DELIM);
		tokns[j] = tokn;
	}

	return (tokns);
}
