#include "shell.h"

/**
 * shell_memset - memeory set allocation
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd paramater
 *
 * Return: a pointer
 */

char *shell_memset(char *a, char b, unsigned int c)
{
	unsigned int d;

	for (d = 0; d < c; d++)
		a[d] = b;
	return (a);
}

/**
 * memory_free - frees a strings
 * @a: 1st parameter
 */

void memory_free(char **a)
{
	if (!a)
		return;

	char **ptr = a;

	while (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		ptr++;
	}
	free(a);
}

/**
 * shell_memcpy - sets the first count bytes of the memory pointed to
 * @dest: 1st parameter
 * @src: 2nd parameter
 * @n: 3rd parameter
 */

void shell_memcpy(void *dest, const void *src, size_t n)
{
	char *destination = (char *)dest;
	const char *source = (const char *)src;

	for (size_t i = 0; i < n; i++)
		destination[i] = source[i];
}

/**
 * shell_realloc - reallocates memory blocks
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd parameter
 *
 * Return: pointer
 */

void *shell_realloc(void *a, unsigned int b, unsigned int c)
{
	if (!a)
		return (malloc(c));

	if (!c)
	{
		free(a);
		return (NULL);
	}

	if (c == b)
		return (a);

	void *d = malloc(c);

	if (!d)
		return (NULL);

	size_t e = b < c ? b : c;

	shell_memcpy(d, a, e);
	free(a);

	return (d);
}
