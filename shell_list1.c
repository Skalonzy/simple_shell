#include "shell.h"

/**
 * freemylist - frees all nodes
 * @a: 1st parameter
 *
 * Return: void
 */

void freemylist(list_t **a)
{
	if (a == NULL || *a == NULL)
		return;

	list_t *b = *a;

	while (b != NULL)
	{
		list_t *c = b->c;

		free(b->str);
		free(b);
		b  = c;
	}
	*a = NULL;
}

/**
 * del_node - deletes nodes
 * @a: 1st parameter
 * @b: 2nd parameter
 *
 * Return: 1 on success
 */

int del_node(list_t **a, unsigned int b)
{
	if (a == NULL || *a == NULL)
		return (0);

	if (b == 0)
	{
		list_t *c = *a;
		*a = (*a)->next;
		free(c->str);
		free(c);
		return (1);
	}

	list_t *d = *a, *e = NULL;
	unsigned int f = 0;

	while (d != NULL && f < index)
	{
		e = d;
		d = d->next;
		f++;
	}

	if (d != NULL)
	{
		e->next = d->next;
		free(d->str);
		free(d);
		return (1);
	}
	return (0);
}

/**
 * printmylist - prints only the str element of a linked list
 * @a: 1st parameter
 *
 * Return: size of list
 */

size_t printmylist(const list_t *a)
{
	size_t b = 0;

	while (a != NULL)
	{
		if (a->str != NULL)
			shell_put(a->str);

		else
			shell_put("(nil)");

		shell_put("\n");
		a = a->next;
		b++;
	}
	return (b);
}

/**
 * addmynode_end - adds node to the end of the list
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd parameter
 *
 * Return: size of the list
 */

list_t *addmynode_end(list_t **a, const char *b, int c)
{
	if (a == NULL)
		return (NULL);

	list_t *d = malloc(sizeof(list_t));

	if (d == NULL)
		return (NULL);

	d->c = c;
	d->next = NULL;

	if (b != NULL)
	{
		size_t e = shell_strlen(b) + 1;

		d->b = malloc(e * sizeof(char));

		if (d->b == NULL)
		{
			free(d);
			return (NULL);
		}
		shell_strncpy(d->b, b, e);
	}

	else
		d->b = NULL;

	if (*a == NULL)
		*a = d;

	else
	{
		list_t *f = *a;

		while (f->next != NULL)
			f = f->next;
		f->next = d;
	}
	return (d);
}

/**
 * addmynode - add a node to the start of the line
 * @a: 1st parameter
 * @b: 2nd parameter
 * @c: 3rd parameter
 *
 * Return: size of list
 */

list_t *addmynode(list_t **a, const char *b, int c)
{
	if (a == NULL)
		return (NULL);

	list_t *d = malloc(sizeof(list_t));

	if (d == NULL)
		return (NULL);

	d->c = c;
	d->next = *a;

	if (b != NULL)
	{
		size_t e = shell_strlen(b) + 1;

		d->b = malloc(e * sizeof(char));

		if (d->b == NULL)
		{
			free(d);
			return (NULL);
		}
		shell_strncpy(d->b, b, e);
	}

	else
		d->b = NULL;

	*a = d;
	return (d);
}
