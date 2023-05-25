#include "shell.h"

/**
 * shell_findbuiltin - find a builtin command
 * @a: 1st parameter
 *
 * Return: -1 if fail
 */

int shell_findbuiltin(info_t *a)
{
	int b, c = -1;
	builtin_table e[] = {
		{"exit", shell_exit},
		{"env", shell_myenviron},
		{"help", shell_help},
		{"history", shell_history},
		{"setenv", shell_environ_setenv},
		{"unsetenv", shell_environ_unsetenv},
		{"cd", shell_cd},
		{"alias", shell_myalias},
		{NULL, NULL}
	};

	for (b = 0; e[i].type; b++)
		if (shell_strcmp(a->argv[0], e[b].type) == 0)
		{
			a->shell_linecount++;
			c = e[b].func(a);
			break;
		}
	return (c);
}

/**
 * shell_hsh - main shell loop
 * @info: 1st parameter
 * @av: 2nd parameter
 *
 * Return: 0 on success
 */

int shell_hsh(info_t *info, char **av)
{
	ssize_t input_result = 0;
	int builtin_result = 0;

	while (input_result != -1 && builtin_result != -2)
	{
		shell_clearinfo(info);

		if (shell_interactivemode(info))
			shell_put("$ ");
		shell_eputchar(B_F);
		input_result = shell_getinput(info);

		if (input_result != -1)
		{
			shell_setinfo(info, av);
			builtin_result = shell_findbuiltin(info);

			if (builtin_result == -1)
				find_cmd(info);
		}

		else if (shell_interactivemode(info))
			shell_putchar('\n');
		shell_freeinfo(info, 0);
	}
	writehistory(info);
	shell_freeinfo(info, 1);
	if (!shell_interactivemode(info) && info->shell_status)
		exit(info->shell_status);
	if (builtin_result == -2)
	{
		if (info->shell_error_num == -1)
			exit(info->shell_status);
		exit(info->err_num);
	}
	return (builtin_result);
}

/**
 * shell_forkcmd - fork a thread
 * @a: 1st parameter
 */

void shell_forkcmd(info_t *a)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(a->shell_path, a->argv, shell_environ(a)) == -1)
		{
			shell_clearinfo(a, 1);

			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		perror("Error:");
		return;
	}

	else
	{
		wait(&(a->shell_status));

		if (WIFEXITED(a->shell_status))
		{
			a->shell_status = WEXITSTATUS(a->shell_status);

			if (a->shell_status == 126)
				shell_printerror(a, "Permission denied\n");
		}
	}
}

/**
 * shell_findcmd - finds a command in PATH
 * @a: 1st parameter
 *
 * Return: void
 */

void shell_findcmd(info_t *a)
{
	char *path = NULL;
	int arg_count = 0;

	a->path = a->argv[0];

	if (info->linecount_flag == 1)
	{
		a->shell_linecount++;
		a->shell_flaglinecount = 0;
	}

	for (int i = 0; a->arg[i]; i++)
	{
		if (!shell_delim(a->arg[i], " \t\n"))
			arg_count++;
	}

	if (arg_count == 0)
		return;
	path = shell_path(a, shell_getenv(a, "PATH="), a->argv[0]);

	if (path != NULL)
	{
		a->path = path;
		shell_forkcmd(a);
	}

	else
	{
		if ((shell_interactivemode(a) || shell_getenv(a, "PATH=") || a->argv[0][0] == '/') && shell_cmd(a, a->argv[0]))
			shell_forkcmd(a);

		else if (*(a->arg) != '\n')
		{
			a->shell_status = 127;
			shell_printerror(a, "not found\n");
		}
	}
}
