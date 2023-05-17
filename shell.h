#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/*shell_variable c file*/
int string(char **, char *);
int variable(info_t *);
int alias(info_t *);
int chain(info_t *, char *, size_t *);
void checkchain(info_t *, char *, size_t *, size_t, size_t);

/*shell_list1 c file*/
void freemylist(list_t **);
int del_node(list_t **, unsigned int);
size_t printmylist(const list_t *);
list_t *addmynode_end(list_t **, const char *, int);
list_t *addmynode(list_t **, const char *, int);

/*shell_list2 c file*/
ssize_t getnodeindex(list_t *, list_t *);
list_t startnode(list_t *, char *, char);
size_t printlist(const list_t *);
char **listostring(list_t *);
size_t listlength(const list_t *);

/*shell_history c file*/
int numb_history(info_t *info);
int historylist(infor_t *a, char *b, int c);
int readhistory(info_t *a);
int writehistory(info_t *a);
char retrievehistory(info_t *a);

/*shell_getenv c file*/
int shell_setenv(info_t *, char *, char *);
int shell_unsetenv(info_t *, char *);
char **shell_environ(info_t *);

/*shell_environ c file*/
int environlist(info_t *);
int shell_environ_unsetenv(info_t *);
int shell_environ_setenv(info_t *);
int shell_environ(info_t *);
char *shell_getenv(info_t *, const char *);

/*shell_info c file*/
void shell_freeinfo(info_t *, int);
void shell_setinfo(info_t *, char **);
void shell_clearinfo(info_t *);

/*shell_getline c file*/
void shell_handler(int);
int shell_getline(info_t *, char **, size_t *);
ssize_t shell_getinput(info_t *);

/*shell_builtin1 c file*/
int shell_help(info_t *);
int shell_cd(info_t *);
int shell_exit(info_t *);

/*shell_buitlin2 c file*/
int shell_history(info_t *);
int shell_alias(info_t *);

/*shell_error1 c file*/
int shell_putsfd(char *a, int b);
int shell_putfd(char a, int b);
int shell_putchar(char);
int shell_eputs(char *);

/*shell_error2 c file*/
void comments(char *);
char *numberconvert(long int, int, int);
int shell_print(int, int);
void shell_printerror(info_t *, char *);
int shell_erroratoi(char *);

/*shell_atoi c file*/
int shell_atoi(char *);
int shell_a(int);
int shell_delim(char, char *);
int shell_interactivemode(info_it *);

/*shell_mem c file*/
int memoryfreed(void **);

/*shell_reallocate c file*/
void shell_realloc(void *, unsigned int, unsigned int);
void memory_free(char **);
char *shell_memset(char *, char, unsigned int);

/*shell_token c file*/
char **shell_token1(char *, char *);
char **shell_token2(char *, char);

/*shell_exit c file*/
char *shell_strchr(char *, char);
char *shell_strncat(char *, char *, int);
char *shell_strncpy(char *, const char *, int);

/*shell_string1 c file*/
char *shell_strcat(char *, char *);
char *startstring(const char*, const char *);
int shell_strcmp(char *, char*);
int shell_strlen(char *);

/*shell_string2 c file*/
int shell_putchar(char);
void shell_put(char *);
char *shell_strdup(const char *);
char *shell_strcpy(char *, char *);

/*shell_loop1 c file*/
int shell_loop(char **);

/*shell_parse c file*/
char *shell_path(info_t *, char *, char *);
char *duplicatechar(char *, int, int);
int shell_cmd(info_t *, char *);

/*shell_loop2 c file*/
int shell_hsh(info_t *, char **);
void shell_forkcmd(info_t *);
void shell_findcmd(info_t *);
int shell_findbuiltin(info_t *);

/*MACROS for the read and write buffers*/
#define R_B_S 1024
#define W_B_S 1024
#define B_F -1

/*MACROS fo executing multiple commands in sequence*/
/*COMMAND CHAINING*/
#define COMMAND_N 0
#define COMMAND_O 1
#define COMMAND_A 2
#define COMMAND_C 3

#define LOWERCASE 1
#define UNSIGNED 2

#define GETLINE 0
#define STRTOK 0

#define SHELL_HISTORY_FILE ".simple_shell_history"
#define SHELL_HISTORY_MAX 4096

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

extern char **environ;

/**
 * struct shell_liststring - A structure that contains singly list links
 * @n: the number section
 * @str: a string
 * @n_n: next node
 */

typedef struct shell_liststring
{
	int n;
	char *str;
	struct shell_liststring n_n;
} list_t;

/**
 * struct list - arguments that are passed in functions
 * @history_count: parameter
 * @shell_readfd: parameter
 * @shell_cmd_bufftype: parameter
 * @shell_status: parameter
 * @shell_environ_changed: parameter
 * @shell_cmd_buff: parameter
 * @environ: parameter
 * @shell_alias: parameter
 * @shell_history: parameter
 * @shell_environ: parameter
 * @shell_fname: parameter
 * @shell_flaglinecount: parameter
 * @shell_error_num: parameter
 * @shell_linecount: parameter
 * @argc: parameter
 * @shell_path: parameter
 * @argv: parameter
 * @arg: paramter
 */

typedef struct list
{
	int history_count;
	int shell_readfd;
	int shell_cmd_bufftype;
	char *shell_cmd_buff;
	int shell_status;
	int shell_environ_changed;
	char **environ;
	list_t *shell_alias;
	list_t *shell_history;
	list_t *shell_environ;
	char *shell_fname;
	int shell_flaglinecount;
	int shell_error_num;
	unsigned int shell_linecount;
	int argc;
	char *shell_path;
	char **argv;
	char *arg;
} info_t;

/**
 * struct shell_builtin - This struct has a built-in string
 * @t: 1st parameter
 * @f: 2nd parameter
 */

typedef struct shell_builtin
{
	char *t;
	int (*f)(info_t *);
} builtin_table;

#endif
