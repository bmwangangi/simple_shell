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
 * struct data - contains data
 * @av: arguments vector
 * @input: cmd line
 * @args: cmd lines comands
 * @status: state of shell
 * @counter: counting lines
 * @_environ: enviroment var
 * @pid:the ID
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
 * Description: storage of list
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: cmdd 
 * @next: -> node
 * Description: the store of command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - sin linked list
 * @len_var: variable len
 * @val: variable value
 * @len_val: var length
 * @next: next node
 * Description:linked list
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct 
 * @name: The name 
 * @f: pointer.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(d_shell *datashel);
} builtin_t;

sep_list *add_sep_node_end(sep_list **head, char separate);
void free_sep_list(sep_list **start);
line_list *add_line_node_end(line_list **start, char *str);
void free_line_list(line_list **str);

r_var *add_rvar_node(r_var **start, int avar, char *variable, int lowerval);
void free_rvar_list(r_var **head);

char *_strcat(char *destnation, const char *source);
char *_strcpy(char *destination, char *source);
int _strcmp(char *str1, char *str2);
char *_strchr(char *string, char character);
int _strspn(char *string, char *accepting);

void _memcpy(void *newpointer, const void *pointer, unsigned int val);
void *_realloc(void *pointer, unsigned int o_size, unsigned int n_size);
char **_reallocdp(char **pointer, unsigned int o_size, unsigned int n_size);

char *_strdup(const char *string);
int _strlen(const char *string);
int cmp_chars(char string[], const char *trab);
char *_strtok(char string[], const char *trab);
int _isdigit(const char *string);

void rev_string(char *string);

int repeated_char(char *inp, int r);
int error_sep_op(char *inp, int r, char lst);
int first_char(char *inp, int *r);
void print_syntax_error(d_shell *datashel, char *inp, int r, int bool);
int check_syntax_error(d_shell *datashel, char *inp);

char *without_comment(char *inp);
void shell_loop(d_shell *datashel);

char *read_line(int *r_lin);

char *swap_char(char *inp, int bool);
void add_nodes(sep_list **h_s, line_list **h_l, char *inp);
void go_next(sep_list **l_s, line_list **l_l, d_shell *datashel);
int split_commands(d_shell *datashel, char *inp);
char **split_line(char *inp);

void check_env(r_var **t, char *inp, d_shell *data);
int check_vars(r_var **t, char *inp, char *st, d_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, d_shell *datashel);

void bring_line(char **linepointer, size_t *b, char *buf, size_t c);
ssize_t get_line(char **linepointer, size_t *x, FILE *see);

int exec_line(d_shell *datashel);

int is_cdir(char *way, int *a);
char *_which(char *cmd, char **_environment);
int is_executable(d_shell *datashel);
int check_error_cmd(char *directory, d_shell *datashel);
int cmd_exec(d_shell *datashel);

char *_getenv(const char *joe, char **_environment);
int _env(d_shell *datashel);

char *copy_info(char *joe, char *val);
void set_env(char *joe, char *val, d_shell *datashel);
int _setenv(d_shell *datashel);
int _unsetenv(d_shell *datashel);

void cd_dot(d_shell *datashel);
void cd_to(d_shell *datashel);
void cd_previous(d_shell *datashel);
void cd_to_home(d_shell *datashel);

int cd_shell(d_shell *datashel);

int (*get_builtin(char *cmd))(d_shell *datashel);

int exit_shell(d_shell *datashel);

int get_len(int a);
char *aux_itoa(int a);
int _atoi(char *x);

char *strcat_cd(d_shell *, char *, char *, char *);
char *error_get_cd(d_shell *datashel);
char *error_not_found(d_shell *datashel);
char *error_exit_shell(d_shell *datashel);
char *error_get_alias(char **args);
char *error_env(d_shell *datashel);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(d_shell *datashel);


int get_error(d_shell *datashel, int evaluate);

void get_sigint(int signal);

void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

int get_help(d_shell *datashel);

#endif
