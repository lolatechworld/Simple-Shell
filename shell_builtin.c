#include "shell.h"

/**
* _ourexit - Exits the shell based on the specified exit status.
* @inform: Structure containing potential arguments. Maintains a constant function prototype.
* Returns: Exits with a given exit status (0) if inform.argv[0] is not "exit".
*/
int _ourexit(inform_t *inform)
{
int exit_check;

if (inform->argv[1])
{
exit_check = _atoies(inform->argv[1]);
if (exit_check == -1)
{
inform->status = 2;
print_error(inform, "Illegal number: ");
_eputs(inform->argv[1]);
_eputchar('\n');
return (1);
}
inform->err_num = _atoies(inform->argv[1]);
return (-2);
}
inform->err_num = -1;
return (-2);
}

/**
* _ourcd - Changes the current directory of the process.
* @inform: Structure containing potential arguments. Maintains a constant function prototype.
* Returns: Always 0.
*/
int _ourcd(inform_t *inform)
{
char *current_dir, *target_dir, buffer[1024];
int chdir_ret;

current_dir = getcwd(buffer, 1024);
if (!current_dir)
_puts("TODO: >>getcwd failure emsg here<<\n");

if (!inform->argv[1])
{
target_dir = _getenv(inform, "HOME=");
if (!target_dir)
chdir_ret = /* TODO: What should this be? */
chdir((target_dir = _getenv(inform, "PWD=")) ? target_dir : "/");
else
chdir_ret = chdir(target_dir);
}
else if (_strcmp(inform->argv[1], "-") == 0)
{
if (!_getenv(inform, "OLDPWD="))
{
_puts(current_dir);
_putchar('\n');
return (1);
}
_puts(_getenv(inform, "OLDPWD=")), _putchar('\n');
chdir_ret = /* TODO: What should this be? */
chdir((target_dir = _getenv(inform, "OLDPWD=")) ? target_dir : "/");
}
else
chdir_ret = chdir(inform->argv[1]);

if (chdir_ret == -1)
{
print_error(inform, "can't cd to ");
_eputs(inform->argv[1]), _eputchar('\n');
}
else
{
_setenv(inform, "OLDPWD", _getenv(inform, "PWD="));
_setenv(inform, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
* _ourhelp - Displays help information for the shell.
* @inform: Structure containing potential arguments. Maintains a constant function prototype.
* Returns: Always 0.
*/
int _ourhelp(inform_t *inform)
{
char **arg_array;

arg_array = inform->argv;
_puts("Help call works. Function not yet implemented.\n");
if (0)
_puts(*arg_array);
return (0);
}
