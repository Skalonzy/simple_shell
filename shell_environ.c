#include "shell.h"

/**
 * environlist - this function populates a given linked list
 * @a: 1st parameter
 *
 * Return: 0 on success
 */

int environlist(info_t *a)
{
	list_t *node = NULL;
	size_t b = 0;

	while (environ[b])
	{
		addmynode_end(&node, environ[b], 0);
		b++;
	}
	a->shell_environ = node;
	return (0);
}

/**
 * shell_environ_unsetenv - remove an environment variable
 * @a: 1st parameter
 *
 * Return: 0 on success
 */

int shell_environ_unsetenv(info_t *a)
{
	int b;

	if (a->argc <= 1)
	{
		shell_eputs("Not enough arguments.\n");
		return (1);
	}

	for (b = 1; b < a->argc; b++)
		shell_unsetenv(a, a->argv[b]);
	return (0);
}

/**
 * shell_environ_setenv - function initializes a new envrionment
 * variable
 * @a: 1st parameter
 *
 * Return: 1 on success
 */

int shell_environ_setenv(info_t *a)
{
	if (a->argc != 3)
	{
		shell_eputs("Wrong number of arguments\n");
		return (1);
	}

	int b = shell_setenv(a, a->argv[1], a->argv[2]);

	return (b ? 0 : 1);
}

/**
 * shell_myenviron - prints current environment
 * @a: 1st parameter
 *
 * Return: 0 on success
 */

int shell_myenviron(info_t *a)
{
	list_t *node = a->shell_environ;

	while (node != NULL)
	{
		size_t len = shell_strlen(node->str);

		write(STDOUT_FILENO, node->str, len);
		write(STDOUT_FILENO, "\n", 1);
		node = node->next;
	}
	return (0);
}

/**
 * shell_getenv - function gets the value of an environ variable
 * @a: 1st parameter
 * @b: 2nd parameter
 *
 * Return: NULL
 */

char *shell_getenv(info_t *a, const char *b)
{
	list_t *c = a->shell_environ;

	while (c != NULL)
	{
		if (startstring(c->str, b) == 0)
			return (c->str);
		c = c->next;
	}
	return (NULL);
}
