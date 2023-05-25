#include "shell.h"

/**
 * write_buffer - writes buffer
 * @a: 1st parameter
 * @b: 2nd parameter
 */

void write_buffer(char *a, int b)
{
	write(2, a, b);
}

/**
 * shell_putfd - writes the character to a given fd
 * @a: 1st parameter
 * @b: 2nd parameter
 *
 * Return: 1 on success
 */

int shell_putfd(char a, int b)
{
	static char buf[W_B_S];
	static int buf_index;

	if (buf_index >= W_B_S || a == B_F)
	{
		write_buffer_fd(b, buf, buf_index);
		buf_index = 0;
	}

	if (a != B_F)
		buf[buf_index++] = a;

	return (1);
}

/**
 * shell_putsfd - print and input string
 * @a: 1st parameter
 * @b: 2nd parameter
 *
 * Return: no of characters
 */

int shell_putsfd(char *a, int b)
{
	if (!a)
		return (0);

	int c = 0;
	char *d = a;

	while (*d != '\0')
	{
		c += shell_putfd(*d, b);
		d++;
	}
	return (c);
}

/**
 * shell_eputchar - writes character to stderr
 * @a: 1stparameter
 *
 * Return: 1 on success
 */

int shell_eputchar(char a)
{
	static char buf[W_B_S];
	static int buf_index;

	if (buf_index >= W_B_S || a == B_F)
	{
		write_buffer(buf, buf_index);
		buf_index = 0;
	}

	if (c != B_F)
		buf[buf_index++] = a;

	return (1);
}

/**
 * shell_eputs - prints an input string
 * @a: 1st parameter
 *
 * Return: nothing
 */

void shell_eputs(char *a)
{
	if (!a)
		return;

	for (int b = 0; a[b] != '\0'; b++)
		shell_eputchar(a[b]);
}
