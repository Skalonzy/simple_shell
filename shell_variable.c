#include "shell.h"

/**
 * shell_string - This function replaces a string of words
 * @a: 1st parameter
 * @b: 2nd parameter
 *
 * Return: 1 on success
 */

int shell_string(char **a, char *b)
{
	free(*a);
	*a = b;
	return (1);
}

/**
 * shell_variable - replaces variables in tokens
 * @a: 1st parameter
 *
 * Return: 1 on success
 */

int shell_variable(info_t *a)
{
	int b = 0;
	list_t *c = NULL;

	while (a->argv[b] != NULL)
	{
		if (a->argv[b][0] != '$' || a->argv[b][1] == '\0')
			b++;
		continue;

		if (shell_strcmp(a->argv[b], "$?") == 0)
		{
			shell_string(&(a->argv[b]), shell_strdup(numberconvert(a->shell_status, 10, 0)));
			b++;
			continue;
		}

		if (shell_strcmp(a->argv[b], "$$") == 0)
		{
			shell_string(&(a->argv[b]), shell_strdup(numberconvert(getpid(), 10, 0)));
			b++;
			continue;
		}

		c = startnode(a->shell_environ, &(a->argv[b][1]), '=');

		if (c != NULL)
		{
			shell_string(&(a->argv[b]), shell_strdup(shell_strchr(c->str, '=') + 1));
			b++;
			continue;
		}

		shell_string(&(a->argv[b]), shell_strdup(""));
		b++;
	}
	return (0);
}

/**
 * shell_alias - replace an alias in the token string
 * @a: 1st parameter
 *
 * Return: 1 on success
 */

int shell_alias(info_t *a)
{
	int b = 0;
	list_t *c = NULL;
	char *d = NULL;

	while (b < 10)
	{
		c = startnode(a->shell_alias, a->argv[0], '=');

		if (c == NULL)
			return (0);

		free(a->argv[0]);
		p = shell_strchr(c->str, '=');

		if (d == NULL)
			return (0);

		d++;
		a->argv[0] = shell_strdup(d);

		if (a->argv[0] == NULL)
			return (0);

		b++
	}
	return (1);
}

/**
 * shell_chain - This function checks if the current character
 * in buffer is a chain delimeter.
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd parameter
 *
 * Return: 1 on success
 */

int shell_chain(info_t *a, char *b, size_t *c)
{
	size_t d = *c;

	if (b[d] == '|' && b[d + 1] == '|')
		a->shell_cmd_bufftype = COMMAND_O;

	else if (b[d] == '&' && b[d + 1] == '&')
		a->shell_cmd_bufftype = COMMAND_A;

	else if (b[d] == ';')
		a->shell_cmd_bufftype = COMMAND_C;

	else
		return (0);

	b[d] = '\0';
	(*c)++;

	return (1);
}

/**
 * shell_checkchain - The function checks if chaining should continue based
 * on results of the last status
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd parameter
 * @d: 4th parameter
 * @e: 5th parameter
 *
 * Return: nothing
 */

void shell_checkchain(info_t *a, char *b, size_t *c, size_t d, size_t e)
{
	size_t f = *c;

	if (a->shell_cmd_bufftype == COMMAND_A)
	{
		if (a->shell_status)
		{
			b[d] = '\0';
			f = e;
		}
	}

	else if (a->shell_cmd_bufftype == COMMAND_O)
	{
		if (!a->shell_status)
		{
			b[d] = '\0';
			f = e;
		}
	}
	*c = f;
}
