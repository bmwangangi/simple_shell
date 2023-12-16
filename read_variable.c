#include "main.h"

/**
 * check_env - is typed variable an env var
 * @h: header
 * @in: string input
 * @data: d struc
 * Return: return 0
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int rw, ch, k, lvl;
	char **_envr;

	_envr = data->_environ;
	for (rw = 0; _envr[rw]; rw++)
	{
		for (k = 1, ch = 0; _envr[rw][ch]; ch++)
		{
			if (_envr[rw][ch] == '=')
			{
				lvl = _strlen(_envr[rw] + ch + 1);
				add_rvar_node(h, k, _envr[rw] + ch + 1, lvl);
				return;
			}

			if (in[k] == _envr[rw][ch])
				k++;
			else
				break;
		}
	}

	for (k = 0; in[k]; k++)
	{
		if (in[k] == ' ' || in[k] == '\t' || in[k] == ';' || in[k] == '\n')
			break;
	}

	add_rvar_node(h, k, NULL, 0);
}

/**
 * check_vars - is typed variable $$ or $?
 * @h: linked list header
 * @in: string inp
 * @st: last status of Shell
 * @data: data struc
 * Return: return 0
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int j, list, lpid;

	list = _strlen(st);
	lpid = _strlen(data->pid);

	for (j = 0; in[j]; j++)
	{
		if (in[j] == '$')
		{
			if (in[j + 1] == '?')
				add_rvar_node(h, 2, st, list), j++;
			else if (in[j + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpid), j++;
			else if (in[j + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[j + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[j + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[j + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[j + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + j, data);
		}
	}

	return (j);
}

/**
 * replaced_input - string change to variables
 * @head: lin lists head
 * @input: string inp
 * @new_input: new str inp i.e, replaced one
 * @nlen: fresh length
 * Return: str replaced
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int j, k, i;

	indx = *head;
	for (k = j = 0; j < nlen; j++)
	{
		if (input[k] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[j] = input[k];
				k++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (i = 0; i < indx->len_var; i++)
					k++;
				j--;
			}
			else
			{
				for (i = 0; i < indx->len_val; i++)
				{
					new_input[j] = indx->val[i];
					j++;
				}
				k += (indx->len_var);
				j--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[j] = input[k];
			k++;
		}
	}

	return (new_input);
}

/**
 * rep_var - function for replacement
 * @input: str inp
 * @datash: data struc
 * Return: str replaced
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *state, *new_inp;
	int olen, nlen;

	state = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, state, datash);

	if (head == NULL)
	{
		free(state);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_inp = malloc(sizeof(char) * (nlen + 1));
	new_inp[nlen] = '\0';

	new_inp = replaced_input(&head, input, new_inp, nlen);

	free(input);
	free(state);
	free_rvar_list(&head);

	return (new_inp);
}