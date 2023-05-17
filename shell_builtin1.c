#include "shell.h"

/**
 * shell_exit - This function is to make shell exit
 * @a: 1st parameter
 *
 * Return: exit with a status
 */

int shell_exit(info_t *a)
{
	if (a->argv[1])
	{
		int b = shell_erroratoi(a->argv[1]);

		if (b == -1)
		{
			a->shell_status = 2;
			shell_printerror(a, "The wrong number is %s\n", a->argv[1]);
			return (1);
		}

		a->shell_error_num = b;
	}

	else
		a->shell_error_num = -1;

	return (-2);
}

/**
 * shell_help - This function helps to change the current
 * working directory to another
 * @a: 1st parameter
 *
 * Return: 0 on success
 */

int shell_help(info_t *a)
{
	char **b = a->argv;

	shell_put("Function not implemented yet. Help call initiated");

	if (0)
	{
		shell_put("%s", *b);
		shell_putchar('\n');
	}
	return (0);
}

/**
 * shell_cd - This function changes the current wd
 * @a: 1st parameter
 *
 * Return: 0 on success
 */

int shell_cd(info_t *a)
{
	char b[1024], *c, *d = getcwd(b, sizeof(b));
	int e;

	if (!d)
		shell_put("Get current working directory failure\n");

	if (!a->argv[1])
	{
		c = shell_getenv(a, "MY_HOME=");

		if (!c)
			c = (shell_getenv(a, "PWD=")) ? shell_getenv(a, "PWD=") : "/";
		e = chdir(c);
	}

	else if (shell_strcmp(a->argv[1], "-") == 0)
	{
		c = shell_getenv(a, "OLDPWD=");

		if (!c)
		{
			shell_put("%s", d);
			shell_putchar('\n');
		}
		shell_put("%s", c);
		shell_putchar('\n');
		e = chdir(c ? c : "/");
	}

	else
		e = chdir(a->argv[1]);
	if (e == -1)
		shell_printerror("can't cd to %s\n", a->argv[1]);
	else
	{
		int shell_setenv(info_t *, char *, char *);
		shell_setenv(a, "OLDPWD", shell_getenv(a, "PWD="));
		shell_setenv(a, "PWD", getcwd(b, sizeof(b)));
	}
	return (0)
}
