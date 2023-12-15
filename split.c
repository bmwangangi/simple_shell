#include "main.h"

/**
 * swap_char - | and & swaps for non-prnted char
 * @inp: string inp
 * @bool: swap type
 * Return: str swapped
 */
char *swap_char(char *inp, int bool)
{
	int j;

	if (bool == 0)
	{
		for (j = 0; inp[j]; j++)
		{
			if (inp[j] == '|')
			{
				if (inp[j + 1] != '|')
					inp[j] = 16;
				else
					j++;
			}

			if (inp[j] == '&')
			{
				if (inp[j + 1] != '&')
					inp[j] = 12;
				else
					j++;
			}
		}
	}
	else
	{
		for (j = 0; inp[j]; j++)
		{
			inp[j] = (inp[j] == 16 ? '|' : inp[j]);
			inp[j] = (inp[j] == 12 ? '&' : inp[j]);
		}
	}
	return (inp);
}

/**
 * add_nodes - add separators $ command lines
 * @h_s: sep list head
 * @h_l: cmd lines inp head
 * @inp: str inp
 * Return: return 0
 */
void add_nodes(sep_list **h_s, line_list **h_l, char *inp)
{
	int j;
	char *lin;

	inp = swap_char(inp, 0);

	for (j = 0; inp[j]; j++)
	{
		if (inp[j] == ';')
			add_sep_node_end(h_s, inp[j]);

		if (inp[j] == '|' || inp[j] == '&')
		{
			add_sep_node_end(h_s, inp[j]);
			j++;
		}
	}

	lin = _strtok(inp, ";|&");
	do {
		lin = swap_char(lin, 1);
		add_line_node_end(h_l, lin);
		lin = _strtok(NULL, ";|&");
	} while (lin != NULL);

}

/**
 * go_next - go to stored next cmd line
 * @l_s: sep list
 * @l_l: cmd line lst
 * @datashel: data struc
 * Return: return 0
 */
void go_next(sep_list **l_s, line_list **l_l, d_shell *datashel)
{
	int loopsep;
	sep_list *lss;
	line_list *lsl;

	loopsep = 1;
	lss = *l_s;
	lsl = *l_l;

	while (lss != NULL && loopsep)
	{
		if (datashel->status == 0)
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

	*l_s = lss;
	*l_l = lsl;
}

/**
 * split_commands - splits cmd lines
 * executes the separators ;, | and &
 * @datashel: data struc
 * @inp: str inp
 * Return: 0 to quit, 1 to proceed
 */
int split_commands(d_shell *datashel, char *inp)
{

	sep_list *heads, *lists;
	line_list *headl, *listl;
	int loop;

	heads = NULL;
	headl = NULL;

	add_nodes(&heads, &headl, inp);

	lists = heads;
	listl = headl;

	while (listl != NULL)
	{
		datashel->input = listl->line;
		datashel->args = split_line(datashel->input);
		loop = exec_line(datashel);
		free(datashel->args);

		if (loop == 0)
			break;

		go_next(&lists, &listl, datashel);

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
 * @inp: str inp
 * Return: splitted str
 */
char **split_line(char *inp)
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

	tokn = _strtok(inp, TOK_DELIM);
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
