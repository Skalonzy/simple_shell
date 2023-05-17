#include "shell.h"

/**
 * shell_strchr - Function to locate a single character
 * in a string
 * @a: 1st parameter
 * @b: 2nd parameter
 *
 * Return: a pointer
 */

char *shell_strchr(char *a, char b)
{
	while (*a != '\0')
	{
		if (*a == c)
			return (a);
		a++;
	}
	return (NULL);
}

/**
 * shell_strncat - This function concantenates 2 strings
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd parameter
 *
 * Return: the concatenated string
 */

char *shell_strncat(char *a, char *b, int c)
{
	int d, e;
	char *f = a;

	d = 0;

	while (a[d] != '\0')
		d++;

	e = 0;

	while (b[e] != '\0' && e < c)
	{
		a[d] = b[e];
		d++;
		e++;
	}

	if (e < c)
		a[d] = '\0';

	return (f);
}

/**
 * shell_strncpy - This function is to copy a string to use
 * @a: 1st paramater
 * @b: 2nd parameter
 * @c: 3rd parameter
 *
 * Return: the string
 */

char *shell_strncpy(char *a, const char *b, int c);
{
	char *d = a;
	int e;

	for (e = 0; e < c && b[e] != '\0'; e++)
		a[e] = b[e];

	for (; e < c; e++)
		a[e] = '\0';

	return (d);
}
