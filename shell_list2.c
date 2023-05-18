#include "shell.h"

/**
 * getnodeindex - Function gets the index of a node
 * @a: 1st parameter
 * @b: 2nd parameter
 *
 * Return: -1 on Success
 */

ssize_t getnodeindex(list_t *a, list_t *b)
{
	for (size_t c = 0; a != NULL; c++)
	{
		if (a == b)
			return ((ssize_t)c);
		a = a->next;
	}
	return (-1);
}

/**
 * startnode - start node
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd parameter
 *
 * Return: NULL
 */

list_t startnode(list_t *a, char *b, char c)
{
	while (a != NULL)
	{
		if (startstring(a->str, b) && (c == -1 || a->str[0] == c))
			return (a);
		a = a->next;
	}
	return (NULL);
}

/**
 * printlist - print lists of arguments of a linked list
 * @a: 1st parameter
 *
 * Return: size of list
 */

size_t printlist(const list_t *a)
{
	for (size_t b = 0; a != NULL; a = a->next, b++)
	{
		shell_put(numberconvert(a->num, 10, 0));
		shell_putchar(':');
		shell_putchar(' ');
		shell_put(a->str ? a->str : "(nil)");
		shell_put("\n");
		a = a->next;
		b++;
	}
	return (b);
}

/**
 * listlength - list the length of strings in a linked list
 * @a: 1st parameter
 *
 * Return: length of list
 */

size_t listlength(const list_t *a)
{
	size_t b = 0;

	for (; a != NULL; a = a->next)
		b++;

	return (b);
}

/**
 * listostring - lists the string of a linked list
 * @a: 1st parameter
 *
 * Return: array of strings
 */

char **listostring(list_t *a)
{
	size_t b = listlength(a);

	if (!a || b == 0)
		return (NULL);

	char **c = malloc(sizeof(char *) * (b + 1));

	if (!c)
		return (NULL);

	size_t d = 0;

	while (a != NULL)
	{
		size_t e = shell_strlen(a->str);

		c[d] = malloc(sizeof(char) * (e + 1));

		if  (!c[d])
		{
			for (size_t f = 0; f < d; f++)
				free(c[f]);
			free(c);
			return (NULL);
		}

		shell_strcpy(c[d], a->str);
		a = a->next;
		d++;
	}

	c[d] = NULL;
	return (c);
}
