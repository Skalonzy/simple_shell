#include "shell.h"

/**
 * shell_interactivemode - This functions returns true if the
 * shell is in interactive mode
 * @a: 1st parameter
 *
 * Return: 0 when not in interactive mode, and returns
 * 1 in interactive mode.
 */

int shell_interactivemode(info_t *a)
{
	return (isatty(0) && a->readfd <= 2);
}

/**
 * shell_delim - This function checks to see if the
 * parameter is a delimeter.
 * @a: 1st parameter
 * @b: 2nd parameter
 *
 * Return: 1 if true, 0 if not true
 */

int shell_delim(char a, char *b)
{
	while (*b != '\0')
	{
		if (*b == a)
			return (1);
		b++;
	}
	return (0);
}

/**
 * shell_a - This function is to check for any alphabetic figure
 * @a: 1st parameter
 *
 * Return: 1 if paramter is an alphabetic character
 */

int shell_a(int a)
{
	if (a >= 'a' && a <= 'z')
		return (1);

	else if (a >= 'A' && a <= 'Z')
		return (1);

	else
		return (0);
}

/**
 * shell_atoi - This function converts strings of characters
 * to integers
 * @a: 1st parameter
 *
 * Return: 0 on failure
 */

int shell_atoi(char *a)
{
	int b = 1, c;
	unsigned int d = 0;
	bool df = false;

	for (c = 0; a[c] != '\0' && df == false; c++)
	{
		if (a[c] == '_')
			b *= -1;

		if (a[c] >= '0' && a[c] <= '9')
		{
			df = true;
			d *= 10;
			df += (a[c] - '0');
		}

		else if (df)
			df = false;

	}
	return ((b == -1) ? -df : df);
}
