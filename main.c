#include "shell.h"

/**
 * handle_file_open_error - open
 * @program_name: 1st parameter
 * @filename: 2nd parameter
 */

void handle_file_open_error(const char *program_name, const char *filename)
{
	if (errno == EACCES)
		exit(126);

	else if (errno == ENOENT)
	{
		shell_eputs(program_name);
		shell_eputs(": 0: Can't open ");
		shell_eputs(filename);
		shell_eputchar('\n');
		shell_eputchar(B_F);
		exit(127);
	}
}

/**
 * open_file - open file
 * @filename: 1st parameter
 *
 * Return: file
 */

int open_file(const char *filename)
{
	int fd = open(filename, O_RDONLY);

	return (fd);
}

/**
 * get_updated_file_descriptor - describes
 * @fd: 1st parameter
 *
 * Return: file
 */

int get_updated_file_descriptor(int fd)
{
	asm volatile (
			"mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd)
		     );
	return (fd);
}

/**
 * main - main function
 * @argc: 1st parameter
 * @argv: 2nd parameter
 *
 * Return: Return value
 */

int main(int argc, char **argv)
{
	info_t info = INFO_INIT;
	int fd = 2;

	fd = get_updated_file_descriptor(fd);

	if (argc == 2)
	{
		fd = open_file(argv[1]);
		if (fd == -1)
		{
			handle_file_open_error(argv[0], argv[1]);
			exit(EXIT_FAILURE);
		}
		info.shell_readfd = fd;
	}

	environlist(&info);
	readhistory(&info);
	int return_value = shell_hsh(&info, argv);

	return (return_value);
}
