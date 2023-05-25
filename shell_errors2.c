#include "shell.h"

/**
 * comments - replaces
 * @a: 1st parameter
 */

void comments(char *a)
{
	char *commentStart = shell_strchr(a, '#');

	if (commentStart != NULL && (commentStart == a || *(commentStart - 1) == ' '))
		*commentStart = '\0';
}

/**
 * numberconvert - converts numbers
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd parameter
 *
 * Return: A string
 */

char *numberconvert(long int a, int b, int c)
{
	static char buffer[50];
	char sign = 0, *resultPtr;
	unsigned long absNum  = a;

	if (!(c & UNSIGNED) && a < 0)
		absNum = labs(a);
	sign = '-';

	const char *digitArray = c & LOWERCASE ? "0123456789abcdef" : "0123456789abcdef";

	resultPtr = &buffer[49];
	*resultPtr = '\0';

	do {
		*--resultPtr = digitArray[absNum % b];
		absNum /= b;
	} while (absNum != 0);

	if (sign)
		*--resultPtr = sign;
	return (resultPtr);
}

/**
 * shell_print - function prints a decimal
 * @a: 1st parameter
 * @b: 2nd parameter
 *
 * Return: no of characters
 */

int shell_print(int a, int b)
{
	int (*_shell_putchar)(char) = b == STDERR_FILENO ? shell_eputchar : shell_putchar;
	int count = 0;

	if (a < 0)
	{
		_shell_putchar('0');
		count++;
		a = -a;
	}

	if (a == 0)
	{
		_shell_putchar('0');
		count++;
		return (count);
	}

	int magnitude = 1;
	int temp = a;

	while (temp > 9)
	{
		magnitude *= 10;
		temp /= 10;
	}

	while (magnitude > 0)
	{
		int digit = a / magnitude;

		_shell_putchar('0' + digit);
		count++;
		a -= digit * magnitude;
		magnitude /= 10;
	}
	return (count);
}

/**
 * shell_printerror - prints an error message
 * @a: 1st parameter
 * @b: 2nd parameter
 */

void shell_printerror(info_t *a, char *b)
{
	shell_eputs(a->shell_fname);
	shell_eputs(":");
	shell_print(a->shell_linecount, STDERR_FILENO);
	shell_eputs(":");
	shell_eputs(a->argv[0]);
	shell_eputs(":");
	shell_eputs(b);
}

/**
 * shell_erroratoi - converts string into integer
 * @a: 1st parameter
 *
 * Return: 0 if no numbers
 */

int shell_erroratoi(char *a)
{
	int i = 0, sign = 1;
	unsigned long int  result = 0;
	bool valid = true;

	if (*a == '+')
		a++;

	else if (*a == '-')
	{
		sign = -1;
		a++;
	}

	while (a[i] != '\0')
	{
		if (a[i] >= '0' && a[i] <= '9')
		{
			result = result * 10 + (a[i] - '0');

			if (result > INT_MAX)
			{
				valid = false;
				break;
			}
		}

		else
		{
			valid = false;
			break;
		}
		i++;
	}
	if (valid)
		return (sign * (int)result);
	else
		return (-1);
}
