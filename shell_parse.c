#include "shell.h"

/**
 * shell_cmd - determines if a file is an executable command
 * @command_info: 1st parameter
 * @file_path: 2nd parameter
 *
 * Return: 0 on success
 */

int shell_cmd(info_t *command_info, char *file_path)
{
	struct stat file_stats;

	if (!file_path || stat(file_path, &file_stats) != 0)
		return (0);

	if (S_ISREG(file_stats.st_mode))
		return (1);

	return (0);
}

/**
 * duplicatechar - duplicates characters
 * @input_str: 1st parameter
 * @start_index: 2nd parameter
 * @stop_index: 3rd parameter
 *
 * Return: pointer to a new buffer
 */

char *duplicatechar(char *input_str, int start_index, int stop_index)
{
	int length = stop_index - start_index;
	char *result_str = (char *)malloc((length + 1) * sizeof(char));

	if (result_str == NULL)
		return (NULL);

	int result_index = 0;

	for (int i = start_index; i < stop_index; i++)
	{
		if (input_str[i] != ':')
			result_str[result_index++] = input_str[i];
	}

	result_str[result_index] = '\0';
	return (result_str);
}

/**
 * shell_path - find this cmd in the path string
 * @info: 1st parameter
 * @pathstr: 2nd parameter
 * @cmd: 3rd parameter
 *
 * Return: path of cmd
 */

char *shell_path(info_t *info, char *pathstr, char *cmd)
{
	if (!pathstr)
		return (NULL);

	size_t path_len = shell_strlen(pathstr), cmd_len = shell_strlen(cmd);

	if (cmd_len > 2 && shell_strncmp(cmd, "./", 2) == 0)
	{
		if (shell_cmd(info, cmd))
			return (cmd);
	}
	size_t curr_pos = 0;

	for (size_t i = 0; i <= path_len; i++)
	{
		if (pathstr[i] == ':' || pathstr[i] == '\0')
		{
			size_t substring_len = i - curr_pos;
			char *path = duplicatechar(pathstr, curr_pos, i);
			size_t path_len = shell_strlen(path);

			if (path_len == 0)
			{
				path = (char *)malloc((cmd_len + 1) * sizeof(char));
				shell_strcpy(path, cmd);
			}

			else
			{
				path = (char *)shell_realloc(path, (path_len + cmd_len + 2) * sizeof(char));
				shell_strcat(path, "/");
				shell_strcat(path, cmd);
			}

			if (shell_cmd(info, path))
				return (path);
			curr_pos = i + 1;
			free(path);
		}
	}
	return (NULL)
}
