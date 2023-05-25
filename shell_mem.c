#include "shell.h"

/**
 * write_buffer_fd - writes to buffer
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd parameter
 */

void write_buffer_fd(int a, char *b, int c)
{
	write(a, b, c);
}

/**
 * memoryfreed - free apointer
 * @a: 1st parameter
 *
 * Return: 0 on success
 */

int memoryfreed(void **a)
{
	if (a != NULL && *a != NULL)
	{
		free(*a);
		*a = NULL;
		return (1);
	}

	else
		return (0);
}
