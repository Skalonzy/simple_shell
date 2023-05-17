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
int varibale(info_t *);
int alias(infor_t *);
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
