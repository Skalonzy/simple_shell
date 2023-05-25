#include "shell.h"

/**
 * shell_handler - blocks the command "Ctrl-C"
 * @a: 1st parameter
 *
 * Return: void
 */

void shell_handler(__attribute__((unused))int a)
{
	shell_puts("\n");
	shell_puts("$ ");
	shell_putchar(B_F);
}

/**
 * shell_readbuf - reads size of buffer
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd parameter
 *
 * Return: buff size
 */

ssize_t shell_readbuf(info_t *a, char *b, size_t *c)
{
	if (*c != 0)
		return (0);

	ssize_t d = read(a->shell_readfd, b, R_B_S);

	if (d >= 0)
		c = (size_t)d;

	return (d);
}

/**
 * shell_getline - functions gets the next line
 * of input
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd parameter
 *
 * Return: a value
 */

int shell_getline(info_t *a, char **b, size_t *c)
{
	static char buf[R_B_S];
	static size_t i, len;
	ssize_t r;
	char *p = b, *new_p, *c;
	size_t s = 0, k;

	if (p && c)
		s = *c;
	if (i == len)
		i = len = 0;
	r = shell_readbuf(a, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = shell_strchr(buf + 1, '\n');
	k = c ? (size_t)(c - buf + 1) : len;
	new_p = shell_realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
	{
		if (p)
			free(p);
		return (-1);
	}
	if (s)
		shell_strncat(new_p, buf + i, k - i);
	else
	{
		shell_strncpy(new_p, buf + i, k - i);
		new_p[k - i] = '\0';
	}
	s += k - i;
	i = k;
	p = new_p;
	if (c)
		*c = s;
	*b = p;
	return (s);
}

/**
 * shell_getinputbuf - get input
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd parameter
 *
 * Return: get bytes read
 */

ssize_t shell_getinputbuf(info_t *a, char **b, size_t c)
{
	ssize_t bytesRead = 0;
	size_t tempLength = 0;

	if (!(*c))
	{
		free(*b);
		*b = NULL;
		signal(SIGINT, shell_handler);

#if GETLINE
		bytesRead = shell_getline(b, &tempLength, stdin);
#else
		bytesRead = shell_getline(a, b, &tempLength);
#endif
		if (bytesRead > 0)
		{
			if ((*b)[bytesRead - 1] == '\n')
			{
				(*b)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			a->shell_flaglinecount = 1;
			comments(*b);
			historylist(a, *b, a->history_count++);

			if (shell_strchr(*b, ';'))
			{
				*c = bytesRead;
				a->shell_cmd_buff = buffer;
			}
		}
	}
	return (bytesRead);
}

/**
 * shell_getinput - new line
 * @a: 1st parameter
 *
 * Return: bytes read
 */

ssize_t shell_getinput(info_t *a)
{
	static char *commanBuffer;
	static size_t currentIndex, commanLength;
	ssize_t bytesRead;
	char **commanPtr = &(a->arg), *currentCommand;

	shell_putchar(B_F);

	bytesRead = shell_getinputbuf(a, &commandBuffer, &commandLength);

	if (bytesRead == -1)
		return (-1);

	if (commandLength)
	{
		size_t iterator = currentIndex;

		currentCommand = commandBuffer + currentIndex;

		shell_checkchain(a, commandBuffer, &iterator, currentIndex, commandLength);

		while (iterator < commandLength)
		{
			if (shell_chain(a, commandBuffer, &iterator))
				break;
			iterator++;
		}

		currentIndex = iterator + 1;
		if (currentIndex >= commandLength)
		{
			CurrentIndex = commandLength = 0;
			a->shell_cmd_bufftype = COMMAND_N;
		}
		*commandPtr = currentCommand;
		return ((ssize_t)(shell_strlen(currentCommand)));
	}
	*commandPtr = commandBuffer;
	return (bytesRead);
}
