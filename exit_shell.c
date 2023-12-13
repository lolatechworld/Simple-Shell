#include "shell.h"

/**
* _strncpy - Copies a string up to a specified number of characters.
* @dest: The destination string for copying.
* @src: The source string.
* @n: The maximum number of characters to copy.
* Return: The resulting concatenated string.
*/
char *_strncpy(char *dest, char *src, int n)
{
int i, j;
char *s = dest;

i = 0;
while (src[i] != '\0' && i < n - 1)
{
dest[i] = src[i];
i++;
}
if (i < n)
{
j = i;
while (j < n)
{
dest[j] = '\0';
j++;
}
}
return (s);
}

/**
* _strncat - Concatenates two strings, using up to a specified number of bytes.
* @dest: The first string.
* @src: The second string.
* @n: The maximum number of bytes to be used.
* Return: The resulting concatenated string.
*/
char *_strncat(char *dest, char *src, int n)
{
int i, j;
char *s = dest;

i = 0;
j = 0;
while (dest[i] != '\0')
i++;
while (src[j] != '\0' && j < n)
{
dest[i] = src[j];
i++;
j++;
}
if (j < n)
dest[i] = '\0';
return (s);
}

/**
* _strchr - Finds the first occurrence of a character in a string.
* @s: The string to be searched.
* @c: The character to locate.
* Return: A pointer to the memory area in 's' containing the character,
*         or NULL if the character is not found.
*/
char *_strchr(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');

return (NULL);
}
