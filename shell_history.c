#include "shell.h"

/**
 * retrievehistory - function gets the file history
 * @a: 1st parameter
 *
 * Return: string containing history of the file
 */

char *retrievehistory(info_t *a)
{
	char *b = shell_getenv(a, "HOME=");

	if (!b)
		return (NULL);

	size_t c = shell_strlen(b);
	size_t d = shell_strlen(SHELL_HISTORY_FILE);

	char *e = malloc(sizeof(char) * (c + d + 2));

	if (!e)
		return (NULL);

	shell_strcpy(e, b);
	e[c] = '/';
	shell_strcpy(e + c + 1, SHELL_HISTORY_FILE);
	return (e);
}

/**
 * numb_history - renumbers the linked list
 * @a: 1st parameter
 *
 * Return: the new count
 */

int numb_history(info_t *a)
{
	int b = 0;

	for (list_t *c = a->shell_history; c; c = c->next)
		c->num = b++;

	a->history_count = b;
	return (b);
}

/**
 * history_list - history of the built linked list
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd parameter
 *
 * Return : 0 on success
 */

int historylist(infor_t *a, char *b, int c)
{
	list_t d = addmynode_end(&(a->shell_history), b, c);

	if (!d)
		return (-1);
	return (0);
}

/**
 * readhistory - reads history of files
 * @a: 1st parameter
 *
 * Return: 0 on failure
 */

int readhistory(info_t *a)
{
	char *b = retrievehistory(a);

	if (!b)
		return (0);

	int c = open(b, O_RDONLY);

	free(b);
	if (c == -1)
		return (0);
	struct stat st;

	if (fstat(c, &st != 0 || st.st_size < 2))
	{
		close(c);
		return (0);
	}
	char *d = malloc(st.st_size + 1);

	if (!d)
	{
		close(c);
		return (0);
	}
	ssize_t e = read(c, d, st.st_size);

	close(c);

	if (e <= 0)
	{
		free(d);
		return (0);
	}
	d[e] = '\0';

	int f = 0;

	for (int g = 0, h = 0; g < e; g++)
	{
		if (d[g] == '\n')
		{
			d[g] = '\0';
			historylist(a, d + h, f++);
			h = g + 1;
		}
	}
	free(d);
	a->hsitory_count = f;

	while (a->history_count >= SHELL_HISTORY_MAX)
	{
		del_node(&(a->shell_history), 0);
		a->history_count--;
	}
	numb_history(a);
	return (a->history_count);
}

/**
 * writehistory - writes the history of file
 * @a: 1st parameter
 *
 * Return: 1 on success
 */

int writehistory(info_t *a)
{
	char *b = retrievehistory(a);

	if (!b)
		return (-1);
	int c = open(b, O_CREAT | O_TRUNC | O_RDWR, 0644);

	free(b);

	if (c == -1)
		return (-1);

	list_t *d = a->shell_history;
	ssize_t e = 0;

	while (d)
	{
		size_t f = shell_strlen(d->str);
		ssize_t g = write(c, d->str, f);

		if (g == -1)
		{
			close(c);
			return (-1);
		}
		e += g;

		g = write(c, "\n", 1);

		if (g == -1)
		{
			close(c);
			return (-1);
		}
		e += g;
		d = d->next;
	}
	fsync(c);
	close(c);
	return ((e > 0) ? 1 : 0);
}
