#include "shell.h"

/**
 * shell_setenv - set an environment variable
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd parameter
 *
 * Return: 0 on success
 */

int shell_setenv(info_t *a, char *b, char *c)
{
	if (!b || !c)
		return (0);

	size_t var_len = shell_strlen(b);
	size_t value_len = shell_strlen(c);
	size_t total_len = var_len + value_len + 1;

	char *buf = (char *)malloc(total_len + 1);

	if (!buf)
		return (1);

	shell_strcpy(buf, b);
	buf[var_len] = '=';
	buf[var_len + 1] = '\0';
	shell_strcat(buf, c);
	list_t *node = a->shell_environ;

	while (node != NULL)
	{
		char *d = startstring(node->str, b);

		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			a->shell_environ_changed = 1;
			return (0);
		}
		node = node->next;
	}

	addmynode_end(&(a->shell_environ), buf, 0);
	free(buf);
	a->shell_environ_changed = 1;
	return (0);
}

/**
 * shell_unsetenv - unset an environment variable
 * @a: 1st parameter
 * @b: 2nd parameter
 *
 * Return: 0 on failure
 */

int shell_unsetenv(info_t *a, char *b)
{
	if (!a->shell_environ || !b)
		return (0);

	list_t *c = a->shell_environ, *d = NULL;
	int e = 0;

	while (c != NULL)
	{
		char *f = startstring(c->str, b);

		if (f && *f == '=')
		{
			if (d == NULL)
				a->shell_ennviron = c->next;

			else
				d->next = c->next;
			free(c->str);
			free(c);
			c = d ? d->next : a->shell_environ;
			e = 1;
		}

		else
		{
			d = c;
			c = c->next;
		}
	}
	a->e = e;
	return (e);
}

/**
 * shell_environ - return the copied string array of the environ
 * @a: 1st parameter
 *
 * Return: 0 on success
 */

char **shell_environ(info_t *a)
{
	if (!a->environ || a->shell_environ_changed)
	{
		if (a->environ)
			free(a->environ);

		int b = 0;
		env_t *c = a->env;

		while (c != NULL)
		{
			b++;
			c = c->next;
		}

		a->environ = (char **)malloc((b + 1) * sizeof(char *));

		if (!a->environ)
			return (NULL);
		c = a->env;
		int d = 0;

		while (c != NULL)
		{
			a->environ[d] = shell_strdup(c->value);

			if (!a->environ[d])
			{
				for (int e = 0; e < d; e++)
					free(a->environ[e]);
				free(a->environ);
				a->environ = NULL;
				return (NULL);
			}
			d++;
			c = c->next;
		}
		a->environ[d] = NULL;
		a->shell_environ_changed = 0;
	}
	return (a->environ);
}
