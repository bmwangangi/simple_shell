#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type; 
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* team__shloop.c */
void forking_cmd(info_t *infomation);
void finding_cmd(info_t *infomation);
int find_the_builtin(info_t *infomation);
int hsh(info_t *infomation, char **ar);

/* toem_parser.c */
char *finding_the_path(info_t *infomation, char *pathstring, char *cmd);
char *duplicate_chars(char *pathstring, int start, int stop);
int it_is_cmd(info_t *infomation, char *way);

/* team _atoi.c*/
int interactive(info_t *trab);
int is_delim(char t, char *delimiter);
int _isalphabhet(int t);
int _atoi(char *t);

/* team errors1.c */
int _stringatoi(char *a);
void printing_error(info_t *trab, char *string);
int print_decimal(int user, int filed);
char *converting_no(long int number, int bs, int flag);
void removing_comments(char *buffer);

/* team info.c */
char *get_histo_file(info_t *infomation);
int writing_history(info_t *infomation);
int reading_history(info_t *infomation);
int building_history_list(info_t *infomation, char *buffer, int linecount);
int renumbered_history(info_t *infomation);

/* team errors.c */
void _inputs(char *str);
int _inputchar(char a);
int _putfd(char a, int fd);
int _putsfd(char *str, int fd);

/* team list0.c */
list_t *adding_node(list_t **start, const char *str, int number);
list_t *adding_node_end(list_t **start, const char *str, int number);
size_t printing_list_str(const list_t *a);
int deleting_node(list_t **start, unsigned int index);
void free_list(list_t **head_p);

/* team tokenization.c */
char **stringtow(char *string, char *x);
char **strtow2(char *string, char d);

/* team builtin1.c */
int _myhisto(info_t *trab);
int unset_alias(info_t *trab, char *str);
int set_alias(info_t *trab, char *str);
int print_alias(list_t *node);
int _myalias(info_t *trab);

/* string1.c */
void _inputs(char *string);
int _putchar(char a);
char *_stringdup(const char *string);
char *_stringcpy(char *destination, char *source);

/* exit.c */
char *_strchra(char *a, char b);
char *_strngcat(char *destination, char *source, int a);
char *_strcpy(char *destination, char *source, int a);

/* list2.c */
ssize_t get_index(list_t *start, list_t *node);
list_t *node_start(list_t *node, char *prx, char a);
size_t printing_list(const list_t *a);
char **list_to_the_strings(list_t *start);
size_t listing_len(const list_t *a);

/* bultin.c */
int _myexit(info_t *trab);
int _myowncd(info_t *trab);
int _help(info_t *trab);

/* getenviroment.c */
int _setenviroment(info_t *trab, char *variable, char *valu);
int _unsetenviroment(info_t *trab, char *variable);
char **get_environment(info_t *trab);

/* realocation.c */
void *_reallocation(void *ptr, unsigned int old_size, unsigned int new_size);
void for_free(char **p);
char *_memoryset(char *c, char d, unsigned int e);

/* vars.c */
int replacing_string(char **old, char *new);
int replacing_vars(info_t *infomation);
int replacing_alias(info_t *infomation);
void check_the_chain(info_t *infomation, char *buffer, size_t *a, size_t b, size_t length);
int it_is_chain(info_t *infomation, char *buffer, size_t *a);

/* getinformation.c */
void free_infomation(info_t *infomation, int fully);
void setting_info(info_t *infomation, char **ar);
void clearing_info(info_t *infomation);

/* enviroment.c */
int _myenviroment(info_t *trab);
char *_getenvroment(info_t *trab, const char *sharon);
int _myunsetenviroment(info_t *trab);
int populate_enviroment_list(info_t *trab);

/* getline.c */
void sigalHandler(__attribute__((unused))int signal_num);
int _gettingline(info_t *trab, char **ptr, size_t *len);
ssize_t read_buffer(info_t *trab, char *buffer, size_t *a);
ssize_t getting_input(info_t *trab);
ssize_t input_buffer(info_t *trab, char **buffer, size_t *length);

/* memory.c */
int befree(void **pointer);



#endif
