#include "shell.h"

/**
 * is_delim - delimeter
 * @c: 1st parameter
 * @d: 2nd parameter
 *
 * Return: false
 */

bool is_delim(char c, char *d)
{
	if (!d)
		d = " ";

	size_t len = shell_strlen(d);

	for (size_t i = 0; i < len; i++)
	{
		if (c == d[i])
			return (true);
	}
	return (false);
}

/**
 * shell_token1 - splits a string into words
 * @input_str: 1st parameter
 * @delimiter: 2nd parameter
 *
 * Return: a pointer
 */

char **shell_token1(char *input_str, char *delimiter)
{
	if (input_str == NULL || input_str[0] == '\0')
		return (NULL);
	if (!delimiter)
		delimiter = " ";
	size_t i, j, k, m, num_words = 0;
	size_t str_len = strlen(input_str);

	for (i = 0; i < str_len; i++)
	{
		if (!is_delim(input_str[i], delimiter) && (is_delim(input_str[i + 1], delimiter) || input_str[i + 1] == '\0'))
			num_words++;
	}
	if (num_words == 0)
		return (NULL);
	char **result = (char **)malloc((num_words + 1) * sizeof(char *));

	if (!result)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delim(input_str[i], delimiter))
			i++;
		k = 0;
		while (!is_delim(input_str[i + k], delimiter) && input_str[i + k] != '\0')
			k++;
		result[j] = (char *)malloc((k + 1) * sizeof(char));
		if (!result[j])
		{
			for (k = 0; k < j; k++)
				free(result[k]);
			free(result);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			result[j][m] = input_str[i++];
		result[j][m] = '\0';
	}
	result[j] = NULL;
	return (result);
}

/**
 * shell_token2 - split a string into words
 * @input_str: 1st parameter
 * @delimiter: 2nd parameter
 *
 * Return: a pointer
 */

char **shell_token2(char *input_str, char delimiter)
{
	if (input_str == NULL || input_str[0] == '\0')
		return (NULL);
	int idx_i, idx_j, idx_k, idx_m, num_words = 0;
	char **result;

	for (idx_i = 0; input_str[idx_i] != '\0'; idx_i++)
	{
		if ((input_str[idx_i] != delimiter && input_str[idx_i + 1] == delimiter) || (input_str[idx_i] != delimiter && !input_str[idx_i + 1]) || input_str[idx_i + 1] == delimiter)
			num_words++;
	}
	if (num_words == 0)
		return (NULL);
	result = (char **)malloc((num_words + 1) * sizeof(char *));

	if (!result)
		return (NULL);
	for (idx_i = 0, idx_j = 0; idx_j < num_words; idx_j++)
	{
		while (input_str[idx_i] == delimiter && input_str[idx_i] != delimiter)
			idx_i++;
		idx_k = 0;
		while (input_str[idx_i + idx_k] != delimiter && input_str[idx_i + idx_k] && input_str[idx_i + idx_k] != delimiter)
			idx_k++;
		result[idx_j] = (char *)malloc((idx_k + 1) * sizeof(char));

		if (!result[idx_j])
		{
			for (idx_k = 0; idx_k < idx_j; idx_k++)
				free(result[idx_k]);
			free(result);
			return (NULL);
		}
		for (idx_m = 0; idx_m < idx_k; idx_m++)
			result[idx_j][idx_m] = input_str[idx_i++];
		result[idx_j][idx_m] = '\0';
	}
	result[idx_j] = NULL;
	return (result);
}
