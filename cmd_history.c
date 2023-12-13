#include "shell.h"

/**
* get_history_file - Acquires the history file.
* @inform: Parameter struct.
* Returns: Allocated string that holds the history file.
*/
char *get_history_file(inform_t *inform)
{
char *buf, *dir;

dir = _getenv(inform, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HIST_FILE);
return (buf);
}

/**
* write_history - Generates a new file or appends to an existing one.
* @inform: Struct containing relevant parameters.
* Return: 1 on success, -1 on failure.
*/
int write_history(inform_t *inform)
{
ssize_t fd;
char *filename = get_history_file(inform);
list_t *node = NULL;

if (!filename)
return (-1);

fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = inform->history; node; node = node->next)
{
_putsfd(node->str, fd);
_putfd('\n', fd);
}
_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}

/**
* read_history - Retrieves history from a file.
* @inform: The parameter struct.
* Returns: The histcount if successful, 0 otherwise.
*/
int read_history(inform_t *inform)
{
int i, last = 0, linecount = 0;
size_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = get_history_file(inform);

if (!filename)
return (0);

fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
build_history_list(inform, buf + last, linecount++);
last = i + 1;
}
if (last != i)
build_history_list(inform, buf + last, linecount++);
free(buf);
inform->histcount = linecount;
while (inform->histcount-- >= HIST_MAX)
delete_node_at_index(&(inform->history), 0);
renumber_history(inform);
return (inform->histcount);
}

/**
* build_history_list - Appends an entry to a history linked list.
* @inform: Structure for potential argument maintenance.
* @buf: Buffer containing the history entry.
* @linecount: Number of lines in the history.
* Return: Always returns 0.
*/
int build_history_list(inform_t *inform, char *buf, int linecount)
{
list_t *node = NULL;

if (inform->history)
node = inform->history;
add_node_end(&node, buf, linecount);

if (!inform->history)
inform->history = node;
return (0);
}

/**
* renumber_history - Renews the history linked list after modifications.
* @inform: Structure with potential arguments, used for maintenance.
* Return: The updated histcount.
*/
int renumber_history(inform_t *inform)
{
list_t *node = inform->history;
int i = 0;

while (node)
{
node->num = i++;
node = node->next;
}
return (inform->histcount = i);
}
