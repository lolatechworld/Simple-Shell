#include "shell.h"

/**
* interactive - Determines if the shell is in interactive mode.
* @inform:Struct holding relevant information.
* Return: 1 if in interactive mode, 0 otherwise
*/
int interactive(inform_t *inform)
{
        return (isatty(STDIN_FILENO) && inform->readfd <= 2);
}

/**
* is_delimet - function that checks if a character is a delimiter.
* @j: the character to check.
* @delimet: the delimiter string.
* Return: 1 if true, 0 if false
*/
int is_delimet(char j, char *delimet)
{
        while (*delimet)
                if (*delimet++ == j)
                        return (1);
        return (0);
}

/**
 *_isalpha - function that checks for alphabetic character
 *@j: The character to check.
 *Return: 1 if j is alphabetic, 0 otherwise
 */

int _isalpha(int j)
{
        if ((j >= 'a' && j <= 'z') || (j >= 'A' && j <= 'Z'))
                return (1);
        else
                return (0);
}

/**
*_atoies - this function converts a string to an integer
*@s: the string to be converted
*Return: 0 if no numbers in string, converted number otherwise
*/

int _atoies(char *s)
{
 int i, sign = 1, flag = 0, output;
unsigned int result = 0;

for (i = 0;  s[i] != '\0' && flag != 2; i++)
{
if (s[i] == '-')
sign *= -1;

if (s[i] >= '0' && s[i] <= '9')
{
flag = 1;
result *= 10;
result += (s[i] - '0');
}
else if (flag == 1)
flag = 2;
}

if (sign == -1)
output = -result;
else
output = result;

return (output);
}
