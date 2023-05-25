#include "shell.h"

/**
 * shell_strcpy - copies a string
 * @destination: 1st parameter
 * @source: 2nd parameter
 *
 * Return: pointer
 */

char *shell_strcpy(char *destination, char *source)
{
	if (destination == source || source == NULL)
		return (destination);

	char *dest_start = destination;

	while ((*destination++ = *source++))
		;

	return (dest_start);
}

/**
 * shell_strdup - duplicates a string
 * @a: 1st parameter
 *
 * Return: pointer
 */

char *shell_strdup(const char *a)
{
	if (a == NULL)
		return (NULL);

	size_t length = shell_strlen(a);
	char *ret = (char *)malloc((length + 1) * sizeof(char));

	if (ret == NULL)
		return (NULL);

	shell_strcpy(ret, a);
	return (ret);
}

/**
 * shell_putchar - write the char to stdout
 * @a: 1st parameter
 *
 * Return: 1 on success
 */

int shell_putchar(char a)
{
	static char buf[W_B_S];
	static int i;

	if (a == B_F || i >= W_B_S - 1)
	{
		buf[i] = '\0';
		write(1, buf, i);
		i = 0;
	}

	if (a != B_F)
		buf[i++] = a;
	return (1);
}

/**
 * shell_put - writes the character c to stdout
 * @a: 1st parameter
 *
 * Return: nothing
 */

void shell_put(char *a)
{
	int b = 0;

	if (!a)
		return;

	while (a[b] != '\0')
	{
		shell_putchar(a[b]);
		b++;
	}
}

