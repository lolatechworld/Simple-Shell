#include "shell.h"

/**
* _eputs - Displays the provided string.
* @str: The string to be printed.
* Returns: Nothing.
*/
void _eputs(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_eputchar(str[i]);
i++;
}
}

/**
* _eputchar - Outputs the character 'c' to stderr.
* @c: The character to be printed.
* Return: Returns 1 on success.
* On error, returns -1, and sets errno appropriately.
*/
int _eputchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(2, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
* _putfd - Outputs the character 'c' to the specified file descriptor.
* @c: The character to be written.
* @fd: The file descriptor to write to.
* Return: Returns 1 on success.
* On error, returns -1 and sets errno appropriately.
*/

int _putfd(char c, int fd)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fd, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
* _putsfd - Outputs the given string to the specified file descriptor.
* @str: The string to be printed.
* @fd: The file descriptor to write to.
* Return: The number of characters written.
*/
int _putsfd(char *str, int fd)
{
int i = 0;

if (!str)
return (0);
while (*str)
{
i += _putfd(*str++, fd);
}
return (i);
}
