This project is to ode and implement the simple shell

/*SHELL_ATOI C FILE*/

int shell_atoi(char *) - function converts a string to an integer. The function takes a pointer to the string as its only argument. The function first iterates over the string, skipping any white space characters. If the function encounters a '-' character, it sets the sign variable to -1. Otherwise, if the function encounters a digit character, it multiplies the result variable by 10 and adds the digit character to the result variable. The function terminates the loop when it encounters a non-digit character. If the sign variable is -1, the function returns the negative value of the result variable. Otherwise, the function returns the positive value of the result variable.

int shell_a(int) - The function checks whether the character passed to it is an alphabetic character. It takes a single argument, c, which is an integer representing the ASCII value of the character. The function first checks if c is greater than or equal to 97 (the ASCII value of 'a') and less than or equal to 122 (the ASCII value of 'z'). If it is, then the function returns 1. Otherwise, the function checks if c is greater than or equal to 65 (the ASCII value of 'A') and less than or equal to 90 (the ASCII value of 'Z'). If it is, then the function returns 1. Otherwise, the function returns 0.

int shell_delim(char, char *) - checks whether the character passed to it is a delimiter. It takes two arguments, c and delim, where c is the character to be checked and delim is a pointer to a string of delimiter characters. The function works by iterating over the string delim and comparing each character to c. If a match is found, the function returns 1. Otherwise, the function returns 0.

int shell_interactivemode(info_t *) - checks whether the program is running in an interactive mode. It takes a single argument, info, which is a pointer to a structure that contains information about the program's environment. The function works by checking two conditions:
The file descriptor for standard input (STDIN_FILENO) must be a terminal device.
The file descriptor for standard input must be less than or equal to 2.
If both of these conditions are met, then the function returns 1. Otherwise, the function returns 0.



/*SHELL_BUILTIN1 C FILE*/
int shell_exit(info_t *) - used to exit the program. It takes a single argument, info, which is a pointer to a structure that contains information about the program's environment. The function works by checking if there is an exit argument passed to the program. If there is, then the function calls the function _erratoi() to convert the exit argument to an integer. If the conversion is successful, then the function sets the info->err_num variable to the converted value and returns -2. Otherwise, the function sets the info->status variable to 2, prints an error message, and returns 1.

If there is no exit argument passed to the program, then the function sets the info->err_num variable to -1 and returns -2.

int shell_help(info_t *) - function that prints a message to the console indicating that the help function has been called, but that the function itself is not yet implemented. The function takes a single argument, a pointer to a structure of type info_t. The info_t structure contains information about the program, such as its name and version number.

The _myhelp function first gets the address of the argv array from the info structure. The argv array contains the command-line arguments that were passed to the program. The function then prints a message to the console indicating that the help function has been called. The function then checks to see if the argv array is empty. If the array is empty, the function does nothing. Otherwise, the function prints the first element of the argv array to the console.

int shell_cd(info_t *) - function that changes the current working directory. The function takes a single argument, a pointer to a structure of type info_t. The info_t structure contains information about the program, such as its name and version number.

The _mycd function first gets the current working directory. The function then checks to see if the user has specified a new directory. If the user has not specified a new directory, the function changes the current working directory to the user's home directory. If the user has specified a new directory, the function changes the current working directory to the specified directory.

The _mycd function returns the value 0 if the change was successful. The function returns the value 1 if the change was not successful.



/*SHELL_EXIT C FILE*/
char *shell_strchr(char *, char) - used to find the first occurrence of the character c in the string s. It returns a pointer to the first occurrence of c in s, or NULL if c is not found in s.

The function works by iterating over the string s and comparing each character to c. If a match is found, the function returns a pointer to the current character. Otherwise, the function continues iterating until the end of the string is reached. If the end of the string is reached and c is not found, the function returns NULL.

char *shell_strncat(char *, char *, int) - is used to concatenate the string pointed to by src to the end of the string pointed to by dest. The function takes three arguments: dest, src, and n. The dest argument is a pointer to the destination string. The src argument is a pointer to the source string. The n argument is the maximum number of characters to concatenate from src to dest.

The function works by first iterating over the destination string until the null character (\0) is reached. This ensures that the destination string is terminated correctly. The function then iterates over the source string, copying each character to the destination string until either the end of the source string is reached or the n characters have been copied. If the end of the source string is reached before the n characters have been copied, the null character is copied to the destination string to terminate it.

char *shell_strncpy(char *, char *, int) - used to copy the first n characters from the string pointed to by src to the string pointed to by dest. The function takes three arguments: dest, src, and n. The dest argument is a pointer to the destination string. The src argument is a pointer to the source string. The n argument is the maximum number of characters to copy from src to dest.

The function works by first iterating over the source string until the null character (\0) is reached or the n characters have been copied. The function then iterates over the destination string, copying each character from the source string to the destination string. If the end of the source string is reached before the n characters have been copied, the null character is copied to the destination string to terminate it.



/*SHELL_GETENV C FILE*/
int shell_setenv(info_t *, char *, char *) - used to set an environment variable. The function takes three arguments, info, var, and value. The info argument is a pointer to a structure that contains information about the process's environment. The var argument is a pointer to the name of the environment variable to set. The value argument is a pointer to the value of the environment variable to set.

The function works by first checking if the info->env pointer is null or if the var pointer is null. If either of these conditions are met, then the function returns 0.

If the function does not find an environment variable with the name var, then the function calls the function add_node_end() to add the new environment variable to the end of the environment list. The function then sets the info->env_changed flag to 1.

The function then returns 0.

int shell_unsetenv(info_t *, char *) -  used to unset an environment variable. The function takes two arguments, info and var. The info argument is a pointer to a structure that contains information about the process's environment. The var argument is a pointer to the name of the environment variable to unset.

The function works by first checking if the info->env pointer is null or if the var pointer is null. If either of these conditions are met, then the function returns 0.

Otherwise, the function iterates over the process's environment list, looking for an environment variable with the name var. If the function finds an environment variable with the name var, then the function calls the function delete_node_at_index() to delete the environment variable from the list. The function then sets the info->env_changed flag to 1.

The function then returns the info->env_changed flag.

char **shell_environ(info_t *) - used to get the environment variables for the process. The function takes a single argument, info, which is a pointer to a structure that contains information about the process's environment.

The function works by first checking if the info->environ pointer is null or if the info->env_changed flag is set. If either of these conditions are met, then the function calls the function list_to_strings() to convert the process's environment list to an array of strings. The function then sets the info->environ pointer to the array of strings and clears the info->env_changed flag.

The function then returns the info->environ pointer.



/*SHELL_VARIABLE C FILE*/
int string(char **, char *) - The function works by first freeing the old string pointed to by the *old pointer. Then, the function sets the *old pointer to the new string. Finally, the function returns 1.

int varibale(info_t *) - The function works by first iterating over the info->argv array. For each element in the array, the function checks if the element starts with a <span class="math-inline">\ character. If it does, then the function checks if the element is one of the special variables `?or$. If it is, then the function replaces the element with the corresponding value. If the element is not one of the special variables, then the function checks if the element is a variable name. If it is, then the function looks up the value of the variable in theinfo->env` list. If the variable is found, then the function replaces the element with the value of the variable. If the variable is not found, then the function replaces the element with an empty string.

int alias(infor_t *) - The function works by first iterating over the info->alias list. For each node in the list, the function checks if the node's string starts with the info->argv[0] string. If it does, then the function frees the info->argv[0] string, copies the string after the first = character from the node's string to a new string, and sets the info->argv[0] string to the new string. If the node's string does not start with the info->argv[0] string, then the function continues to the next node.

int chain(info_t *, char *, size_t *) - The function works by first checking if the current character in the buffer is a semicolon. If it is, then the function returns 1 and sets the info->cmd_buf_type to CMD_CHAIN. Otherwise, the function checks if the current two characters in the buffer are | and |. If they are, then the function returns 1 and sets the info->cmd_buf_type to CMD_OR. Similarly, the function checks if the current two characters in the buffer are & and &. If they are, then the function returns 1 and sets the info->cmd_buf_type to CMD_AND. If none of these conditions are met, then the function returns 0.

void checkchain(info_t *, char *, size_t *, size_t, size_t) - The function works by first checking the info->cmd_buf_type variable. If the type is CMD_AND, then the function checks if the info->status variable is set to 1. If it is, then the function sets the buf[i] character to 0 and the j variable to the len value. This effectively removes the next command from the buffer. If the type is CMD_OR, then the function checks if the info->status variable is set to 0. If it is, then the function sets the buf[i] character to 0 and the j variable to the len value. This effectively removes the next command from the buffer.

