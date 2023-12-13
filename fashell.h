#ifndef FASHELL_H
#define FASHELL_H

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
#define FBUF_SIZE 1024
#define FWBUF_SIZE 1024
#define FBUF_FLUSH -1

/* for command chaining */
#define FMD_N		0
#define FMD_OR		1
#define FMD_AND		2
#define FMD_CHAIN	3


/* for convert_number() */
#define FCONV_LOW	1
#define FCONV_UNS	2

/* 1 for default system getline() else use the custom _fgetline */
#define FUSE_GET 1

#define FHIST_FILE	".simple_shell_fhistory"
#define FHIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @fstr: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *fstr;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@falias: the falias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
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
	list_t *falias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} finfo_a17;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(finfo_a17 *);
} builtin_table;


/* fshell_start.c */
int shell(finfo_a17 *, char **);
int find_builtin(finfo_a17 *);
void find_cmd(finfo_a17 *);
void fork_cmd(finfo_a17 *);

/* fmem-parse.c */
int fcmd(finfo_a17 *, char *);
char *fdup_chars(char *, int, int);
char *find_fpath(finfo_a17 *, char *, char *);
int bfree(void **);

/* ferr.c */
void _fputs(char *);
int _fputchar(char);
int _fputfd(char c, int fd);
int _fputsfd(char *fstr, int fd);
int _ferratoi(char *);

/* fstr.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *fstarts_with(const char *, const char *);
char *_strcat(char *, char *);

/* fstr2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char **strtow(char *, char *);

/* fexit.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* ffree.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int interact(finfo_a17 *);
int fdelim(char, char *);

/* ferr2.c */
void print_error(finfo_a17 *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* fcusbuilt.c */
int _fexit(finfo_a17 *);
int _fcd(finfo_a17 *);
int _fhelp(finfo_a17 *);
int _myfalias(finfo_a17 *);

/* fbuilt.c */
int _fhistory(finfo_a17 *);
int print_falias(list_t *node);
int set_falias(finfo_a17 *finfo, char *fstr);

/* fgetline.c */
ssize_t get_input(finfo_a17 *);
int _fgetline(finfo_a17 *, char **, size_t *);


/* fainfo.c */
void sigintHandler(int);
void clear_finfo(finfo_a17 *);
void set_finfo(finfo_a17 *, char **);
void free_finfo(finfo_a17 *, int);

/* fenv.c */
char *_fgetenv(finfo_a17 *, const char *);
int _fenv(finfo_a17 *);
int _fmsetenv(finfo_a17 *);
int _funsetenv(finfo_a17 *);
int fpop_env_list(finfo_a17 *);

/* fgetenv.c */
char **fget_env(finfo_a17 *);
int f_unsetenv(finfo_a17 *, char *);
int _fsetenv(finfo_a17 *, char *, char *);

/* fhist.c */
char *get_fhistory_file(finfo_a17 *finfo);
int write_fhistory(finfo_a17 *finfo);
int read_fhistory(finfo_a17 *finfo);
int build_fhistory_list(finfo_a17 *finfo, char *buf, int linecount);
int renumber_history(finfo_a17 *finfo);

/* flist.c */
list_t *fadd_node(list_t **, const char *, int);
list_t *fadd_node_end(list_t **, const char *, int);
size_t fprint_list_str(const list_t *);
int fdelete_node_at_ind(list_t **, unsigned int);
void free_flist(list_t **);

/* flists2.c */
size_t flist_len(const list_t *);
char **flist_to_strings(list_t *);
size_t _fprintlist(const list_t *);
list_t *fnode_starts_with(list_t *, char *, char);
ssize_t get_node_ind(list_t *, list_t *);

/* fchain.c */
int fchain(finfo_a17 *, char *, size_t *);
void check_fchain(finfo_a17 *, char *, size_t *, size_t, size_t);
int replace_falias(finfo_a17 *);
int replace_fvars(finfo_a17 *);
int replace_fstring(char **, char *);

#endif /* FASHELL_H */
