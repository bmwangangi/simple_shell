#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array */
extern char **environ;


/**
 * struct data - contains all relevant data
 * @av: arguments
 * @input: cmd line written by the user
 * @args: cmd comd lines
 * @status: state of shell
 * @counter: count lines
 * @_environ: env var
 * @pid: shell ID
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} d_shell;

/**
 * struct sep_list_s - only listed list
 * @separator: ; | &
 * @next: -> node
 * Description: linked lists storage
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: cmdd line
 * @next: -> node
 * Description: store cmd lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - sin linked list
 * @len_var: var len
 * @val: var value
 * @len_val: var len
 * @next: next node
 * Description:linked list. var storage
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(d_shell *datashel);
} builtin_t;

/* aux_lists.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* aux_lists2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* aux_str functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* aux_mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* aux_str3.c */
void rev_string(char *s);

/* check_syntax_error.c */
int repeated_char(char *inp, int r);
int error_sep_op(char *inp, int r, char lst);
int first_char(char *inp, int *r);
void print_syntax_error(d_shell *datashel, char *inp, int r, int bool);
int check_syntax_error(d_shell *datashel, char *inp);

/* shell_loop.c */
char *without_comment(char *inp);
void shell_loop(d_shell *datashel);

/* read_line.c */
char *read_line(int *i_eof);

/* split.c */
char *swap_char(char *inp, int bool);
void add_nodes(sep_list **h_s, line_list **h_l, char *inp);
void go_next(sep_list **l_s, line_list **l_l, d_shell *datashel);
int split_commands(d_shell *datashel, char *inp);
char **split_line(char *inp);

/* read_variable.c */
void check_env(r_var **t, char *inp, d_shell *data);
int check_vars(r_var **t, char *inp, char *st, d_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, d_shell *datashel);

/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exec_line(d_shell *datashel);

/* cmd_exec.c */
int is_cdir(char *way, int *a);
char *_which(char *cmd, char **_environment);
int is_executable(d_shell *datashel);
int check_error_cmd(char *directory, d_shell *datashel);
int cmd_exec(d_shell *datashel);

/* env1.c */
char *_getenv(const char *joe, char **_environment);
int _env(d_shell *datashel);

/* env2.c */
char *copy_info(char *joe, char *val);
void set_env(char *joe, char *val, d_shell *datashel);
int _setenv(d_shell *datashel);
int _unsetenv(d_shell *datashel);

/* cd.c */
void cd_dot(d_shell *datashel);
void cd_to(d_shell *datashel);
void cd_previous(d_shell *datashel);
void cd_to_home(d_shell *datashel);

/* cd_shell.c */
int cd_shell(d_shell *datashel);

/* get_builtin */
int (*get_builtin(char *cmd))(d_shell *datashel);

/* _exit.c */
int exit_shell(d_shell *datashel);

/* aux_stdlib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* aux_error1.c */
char *strcat_cd(d_shell *, char *, char *, char *);
char *error_get_cd(d_shell *datashel);
char *error_not_found(d_shell *datashel);
char *error_exit_shell(d_shell *datashel);

/* aux_error2.c */
char *error_get_alias(char **args);
char *error_env(d_shell *datashel);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(d_shell *datashel);


/* get_error.c */
int get_error(d_shell *datashel, int evaluate);

/* get_sigint.c */
void get_sigint(int sig);

/* aux_help.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* aux_help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* get_help.c */
int get_help(d_shell *datashel);

#endif
