#include "shell.h"

/**
* _strcpy - copies a string
* @destination: the destination
* @source: the source
* Return: pointer to destination
*/
char *_strcpy(char *destination, char *source)
{
int index = 0;
if (destination == source || source == NULL)
return (destination);
while (source[index])
{
destination[index] = source[index];
index++;
}
destination[index] = '\0';
return (destination);
}

/**
* _strdup - duplicates a string
* @str: the string to duplicate
* Return: pointer to the duplicated string
*/
char *_strdup(const char *str)
{
int length = 0;
char *result;
if (str == NULL)
return (NULL);
while (*str++)
length++;
result = malloc(sizeof(char) * (length + 1));
if (!result)
return (NULL);
for (length++; length--;)
result[length] = *--str;
return (result);
}

/**
* _puts - prints an input string
* @str: the string to be printed
* Return: Nothing
*/
void _puts(char *str)
{
int index = 0;

if (!str)
return;
while (str[index] != '\0')
{
_putchar(str[index]);
index++;
}
}

/**
* _putchar - writes the character c to stdout
* @c: The character to print
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putchar(char c)
{
static int index;
static char buffer[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
{
write(1, buffer, index);
index = 0;
}
if (c != BUF_FLUSH)
buffer[index++] = c;
return (1);
}
