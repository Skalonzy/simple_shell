#include "shell.h"

/**
 * shell_freeinfo - frees structures
 * @a: 1st parameter
 * @b: 2nd parameter
 */

void shell_freeinfo(info_t *a, int b)
{
	memory_free(a->argv);
	a->argv = NULL;
	a->shell_path;

	if (b)
	{
		if (!a->shell_cmd_buff)
			free(a->arg);
		freemylist(&(a->shell_environ));
		freemylist(&(a->shell_history));
		freemylist(&(a->shell_alias));
		freemylist(a->environ);
		a->environ = NULL;
		memoryfreed((void **)a->shell_cmd_buff);

		if (a->shell_readfd > 2)
			close(a->shell_readfd);

		shell_putchar(B_F);
}

/**
 * count_elements - count number of elements
 * @a: 1st parameter
 * Return: number of count
 */

int count_elements(char **a)
{
	int b = 0;

	while (a && a[b] != NULL)
		b++;

	return (b);
}

/**
 * shell_clearinfo - clears the structure for new elements
 * @a: 1st parameter
 */

void shell_clearinfo(info_t *a)
{
	a->argc = 0;
	a->argv = NULL;
	a->arg = NULL;
	a->path = NULL;
}

/**
 * shell_setinfo - sets the structure
 * @a: 1st parameter
 * @b: 2nd parameter
 */

void shell_setinfo(info_t *a, char **b)
{
	a->shell_fname = b[0];

	if (a->arg)
	{
		a->argv = shell_token1(a->arg, " \t");

		if (!a->argv)
		{
			a->argv = malloc(2 * sizeof(char *));

			if (a->argv)
			{
				a->argv[0] = shell_strdup(a->arg);
				a->argv[1] = NULL;
			}
		}
		a->argc = (a->argv) ? count_elements(a->argv) : 0;

		shell_alias(a);
		shell_variable(a);
	}
}
