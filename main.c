#include "shell.h"

/**
* shell_entry - entry point for the custom shell
* @argument_count: argument count
* @argument_vector: argument vector
* Return: 0 on success, 1 on error
*/
int shell_entry(int argument_count, char **argument_vector)
{
info_t shell_info[] = { SHELL_INFO_INIT };
int file_descriptor = 2;

asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (file_descriptor)
: "r" (file_descriptor));

if (argument_count == 2)
{
file_descriptor = open(argument_vector[1], O_RDONLY);
if (file_descriptor == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
print_error_string(argument_vector[0]);
print_error_string(": 0: Can't open ");
print_error_string(argument_vector[1]);
print_error_char('\n');
print_error_char(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
shell_info->readfd = file_descriptor;
}
populate_environment_list(shell_info);
load_history(shell_info);
shell_loop(shell_info, argument_vector);
return (EXIT_SUCCESS);
}

/**
* main - entry point to the program
* @argc: argument count
* @argv: argument vector
* Return: 0 on success, 1 on error
*/
int main(int argc, char **argv)
{
return (shell_entry(argc, argv));
}