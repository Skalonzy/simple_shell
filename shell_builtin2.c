#include "shell.h"

/**
 * shell_history - function shows function list
 * @a: 1st parameter
 *
 * Return: 0 on success
 */

int shell_history(info_t *a)
{
	printmylist(a->shell_history);
	return (0);
}

/**
 * shell_unsetalias - function sets alias to string
 * @a: 1st parameter
 * @b: 2nd parameter
 *
 * Return: 0 on success
 */

int shell_unsetalias(info_t *a, char *b)
{
	char *equal_pos, c;
	int ret;

	equal_pos = shell_strchr(b, '=');

	if (!equal_pos)
		return (1);

	c = *equal_pos;
	*equal_pos = '\0';

	size_t key_length = equal_pos - b;
	char *key = malloc((key_length + 1) * sizeof(char));

	shell_strncpy(key, b, key_length);

	key[key_length] = '\0';

	ret = del_node(&(a->shell_alias), getnodeindex(a->shell_alias, /
				startnode(a->shell_alias, key, -1)));

	*equal_pos = c;

	free(key);

	return (ret);
}

/**
 * shell_setalias - set alias to string
 * @a: 1st parameter
 * @b: 2nd parameter
 *
 * Return: 0 on success
 */

int shell_setalias(info_t *a, char *b)
{
	char *equal_sign = shell_strchr(b, '=');

	if (!equal_sign)
		return (1);

	if (!*(equal_sign + 1))
		return (shell_unsetalias(a, b));

	shell_unsetalias(a, b);
	return (addmynode_end(&(a->shell_alias), b, 0) == NULL);
}

/**
 * shell_printalias - function prints an alias string
 * @a: 1st parameter
 *
 * Return: 0 on success
 */

int shell_printalias(list_t *a)
{
	if (a)
	{
		char *equal_sign = shell_strchr(a->str, '=');

		if (equal_sign)
		{
			char *p = NULL, *b = NULL;

			p = equal_sign;

			for (b = a->str; b <= p; b++)
				shell_putchar(*b);

			shell_putchar('\'');
			shell_put(p + 1);
			shell_put("'\n");
			return (0);
		}
	}
	return (1);
}

/**
 * shell_myalias - man alias
 * @a: 1st parameter
 *
 * Return: Always 0
 */

int shell_myalias(info_t *a)
{
	if (a->argc == 1)
	{
		list_t *node = a->shell_alias;

		while (node)
		{
			shell_printalias(node);
			node = node->next;
		}
		return (0);
	}

	for (int i = 1; a->argv[i]; i++)
	{
		char *equal_sign = shell_strchr(a->argv[i], '=');

		if (equal_sign)
			shell_setalias(a, a->argv[i]);

		else
		{
			list_t *filtered_node = startnode(a->shell_alias, a->argv[i], '=');

			shell_printalias(filtered_node);
		}
	}
	return (0);
}
