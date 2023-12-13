#include "shell.h"

/**
* input_buf - Buffers chained commands for processing.
* @inform: Parameter struct.
* @buf: Address of the buffer.
* @len: Address of the length variable.
* Return: The number of bytes read.
*/
ssize_t input_buf(inform_t *inform, char **buf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;

if (!*len) /* if nothing left in the buffer, fill it */
{
/*bfree((void **)inform->cmd_buf);*/
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
r = getline(buf, &len_p, stdin);
#else
r = _getline(inform, buf, &len_p);
#endif
if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0'; /* remove trailing newline */
r--;
}
inform->linecount_flag = 1;
remove_comments(*buf);
build_history_list(inform, *buf, inform->histcount++);
/* if (_strchr(*buf, ';')) is this a command chain? */
{
*len = r;
inform->cmd_buf = buf;
}
}
}
return (r);
}

/**
* get_input - Reads a line excluding the newline character.
* @inform: Parameter struct.
* Return: The number of bytes read.
*/

ssize_t get_input(inform_t *inform)
{
static char *buf;
static size_t i, j, len;
ssize_t r = 0;
char **buf_p = &(inform->arg), *p;

_putchar(BUF_FLUSH);
r = input_buf(inform, &buf, &len);
if (r == -1) /* EOF */
return (-1);
if (len)
{
j = i;
p = buf + i;

check_chain(inform, buf, &j, i, len);
while (j < len)
{
if (is_chain(inform, buf, &j))
break;
j++;
}

i = j + 1;
if (i >= len)
{
i = len = 0;
inform->cmd_buf_type = CMD_NORM;
}

*buf_p = p;
return (_strlen(p));
}

*buf_p = buf;
return (r);
}

/**
* read_buf - Reads a buffer and returns the result.
* @inform: Parameter struct.
* @buf: The buffer to be read.
* @i: The size of the buffer.
* Return: The value 'r'.
*/
ssize_t read_buf(inform_t *inform, char *buf, size_t *i)
{
ssize_t r = 0;

if (*i)
return (0);
r = read(inform->readfd, buf, READ_BUF_SIZE);
if (r >= 0)
*i = r;
return (r);
}

/**
* _getline - Fetches the next line of input from STDIN.
* @inform: Parameter struct.
* @ptr: Address of the pointer to the buffer, which can be preallocated or NULL.
* @length: Size of the preallocated 'ptr' buffer if it is not NULL.
* Return: The string 's'.
*/
int _getline(inform_t *inform, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;

p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;

r = read_buf(inform, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);

c = _strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);

if (s)
_strncat(new_p, buf + i, k - i);
else
_strncpy(new_p, buf + i, k - i + 1);

s += k - i;
i = k;
p = new_p;

if (length)
*length = s;
 *ptr = p;
return (s);
}

/**
* sigintHandler - Handles the blocking of Ctrl-C signals.
* @sig_num: Signal number corresponding to Ctrl-C.
* Returns: No specific value.
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
