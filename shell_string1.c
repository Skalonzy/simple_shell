#include "shell.h"

/**
 * shell_strlen - returns the length of a string
 * @a: 1st parameter
 *
 * Return: integer of length
 */

int shell_strlen(char *a)
{
	if (s == NULL)
		return (0);

	size_t length = 0;

	while (*(a + length) != '\0')
		length++;

	return (length);
}

/**
 * shell_strcmp - comparisons
 * @s1: 1st parameter
 * @s2: 2nd parameter
 *
 * Return: 1 on success
 */

int shell_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);

	else if (*s1 < *s2)
		return (-1);

	else
		return (1);
}

/**
 * startstring - starts string
 * @a: 1st parameter
 * @b: 2nd parameter
 *
 * Return: address
 */

char *startstring(const char *a, const char *b)
{
	while (*b)
		if (*b++ != *a++)
			return (NULL);
	return ((char *)a);
}

/**
 * shell_strcat - concatenates strings
 * @a: 1st parameter
 * @b: 2nd parameter
 *
 * Return: pointer
 */

char *shell_strcat(char *a, char *b)
{
	char *c = a;

	while (*a)
		a++;

	while (*b)
		*a++ = *b++;
	*a = *b;
	return (c);
}
