#include "shell.h"

/**
* _erratoies - Converts a string to an integer, handling errors.
* @s: The string to be converted.
* Returns: The converted number if successful, or -1 on error.
*/
int _erratoies(char *s)
{
int i = 0;
unsigned long int result = 0;

if (*s == '+')
s++;
for (i = 0;  s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
result *= 10;
result += (s[i] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}

/**
* print_error - Outputs an error message based on specified error type.
* @inform: Parameter and return information struct.
* @estr: String containing the specified error type.
* Return: 0 on success, -1 on error.
*/
void print_error(inform_t *inform, char *estr)
{
_eputs(inform->fname);
_eputs(": ");
print_d(inform->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(inform->argv[0]);
_eputs(": ");
_eputs(estr);
}

/**
* print_d - Outputs a decimal (integer) number in base 10.
* @input: The input number.
* @fd: The file descriptor for output.
* Returns: The count of printed characters.
*/
int print_d(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int i, count = 0;
unsigned int _abs_, current;

if (fd == STDERR_FILENO)
__putchar = _eputchar;
if (input < 0)
{
_abs_ = -input;
__putchar('-');
count++;
}
else
_abs_ = input;
current = _abs_;
for (i = 1000000000; i > 1; i /= 10)
{
if (_abs_ / i)
{
__putchar('0' + current / i);
count++;
}
current %= i;
}
__putchar('0' + current);
count++;

return (count);
}

/**
* convert_number - Conversion function, akin to itoa.
* @num: The number to be converted.
* @base: The base for the conversion.
* @flags: Argument flags.
* Return: The resulting string.
*/
char *convert_number(long int num, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;

if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';

}
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do      {
*--ptr = array[n % base];
n /= base;
} while (n != 0);

if (sign)
*--ptr = sign;
return (ptr);
}

/**
* remove_comments - Replaces the first instance of '#' with '\0' in the string.
* @buf: The address of the string to modify.
* Return: Always 0.
*/
void remove_comments(char *buf)
{
int i;

for (i = 0; buf[i] != '\0'; i++)
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}
