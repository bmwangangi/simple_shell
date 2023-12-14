#include "shell.h"

/**
 * input_buffer - buffers commands
 * @trab: the struct
 * @buffer: the buffer address
 * @length: the address of the length
 *
 * Return: bytes
 */
ssize_t input_buffer(info_t *trab, char **buffer, size_t *length)
{
	ssize_t a = 0;
	size_t len_pip = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buffer, &len_pip, stdin);
#else
		a = _getline(trab, buffer, &len_pip);
#endif
		if (a > 0)
		{
			if ((*buffer)[a - 1] == '\n')
			{
				(*buffer)[a - 1] = '\0';
				a--;
			}
			trab->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(trab, *buffer, trab->histcount++);
			{
				*length = a;
				trab->cmd_buf = buffer;
			}
		}
	}
	return (a);
}

/**
 * getting_input - gets a new line
 * @trab: the struct of the parameter
 *
 * Return: bytes available
 */
ssize_t getting_input(info_t *trab)
{
	static char *buffer;
	static size_t a, b, length;
	ssize_t s = 0;
	char **buf_pip = &(trab->arg), *p;

	_putchar(BUF_FLUSH);
	s = input_buffer(trab, &buffer, &length);
	if (s == -1)
		return (-1);
	if (length)
	{
		b = a;
		p = buffer + a;

		check_chain(trab, buffer, &b, a, length);
		while (b < length)
		{
			if (is_chain(trab, buffer, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= length)
		{
			a = length = 0;
			trab->cmd_buf_type = CMD_NORM;
		}

		*buf_pip = p;
		return (_strlen(p));
	}

	*buf_pip = buffer;
	return (s);
}

/**
 * read_buffer - reads the buffer
 * @trab: thestruct
 * @buffer: buffer
 * @a: the size
 *
 * Return: b
 */
ssize_t read_buffer(info_t *trab, char *buffer, size_t *a)
{
	ssize_t b = 0;

	if (*a)
		return (0);
	b = read(trab->readfd, buffer, READ_BUF_SIZE);
	if (b >= 0)
		*a = b;
	return (b);
}

/**
 * _gettingline - gets the next line from standard input
 * @trab: the struct
 * @ptr: address of a pointer
 * @len: size of preallocated ptr
 *
 * Return: a
 */
int _gettingline(info_t *trab, char **ptr, size_t *len)
{
	static char buf[READ_BUF_SIZE];
	static size_t b, length;
	size_t x;
	ssize_t d = 0, e = 0;
	char *f = NULL, *new_p = NULL, *c;

	f = *ptr;
	if (f && len)
		e = *len;
	if (b == length)
		b = length = 0;

	d = read_buffer(trab, buf, &length);
	if (d == -1 || (d == 0 && length == 0))
		return (-1);

	c = _strchr(buf + b, '\n');
	x = c ? 1 + (unsigned int)(c - buf) : length;
	new_p = _realloc(f, e, e ? e + x : x + 1);
	if (!new_p)
		return (f ? free(f), -1 : -1);

	if (e)
		_strncat(new_p, buf + b, x - b);
	else
		_strncpy(new_p, buf + b, x - b + 1);

	e += x - b;
	b = x;
	f = new_p;

	if (len)
		*len = e;
	*ptr = f;
	return (e);
}

/**
 * signalHandler - blocks ctrl-C
 * @signal_num: the sig  number
 *
 * Return: void
 */
void sigalHandler(__attribute__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
