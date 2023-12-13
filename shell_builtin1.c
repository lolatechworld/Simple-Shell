#include "shell.h"

/**
* _ourhistory - Displays the command history with line numbers.
* @inform: Structure with potential arguments. Maintains a constant function prototype.
* Returns: Always 0.
*/

int _ourhistory(inform_t *inform)
{
print_list(inform->history);
return (0);
}

/**
* unset_alias - sets alias to string
* @inform: parameter struct
* @str: the string alias
* Return: Always 0 on success, 1 on error
*/
int unset_alias(inform_t *inform, char *str)
{
char *p, j;
int ret;

p = _strchr(str, '=');
if (!p)
return (1);
j = *p;
*p = 0;
ret = delete_node_at_index(&(inform->alias),
get_node_index(inform->alias, node_starts_with(inform->alias, str, -1)));
*p = j;
return (ret);
}

/**
* set_alias - Assigns an alias to a string.
* @inform: Parameter struct.
* @str: The string alias.
* Returns: 0 on success, 1 on error.
*/

int set_alias(inform_t *inform, char *str)
{
char *p;

p = _strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (unset_alias(inform, str));

unset_alias(inform, str);
return (add_node_end(&(inform->alias), str, 0) == NULL);
}

/**
* print_alias - prints an alias string
* @node: the alias node
* Return: Always 0 on success, 1 on error
*/
int print_alias(list_t *node)
{
char *p = NULL, *a = NULL;

if (node)
{
p = _strchr(node->str, '=');
for (a = node->str; a <= p; a++)
_putchar(*a);
_putchar('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
* _ouralias - Simulates the behavior of the alias builtin (man alias).
* @inform: Structure with potential arguments. Maintains a constant function prototype.
* Returns: Always 0.
*/

int _ouralias(inform_t *inform)
{
int i = 0;
char *p = NULL;
list_t *node = NULL;

if (inform->argc == 1)
{
node = inform->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; inform->argv[i]; i++)
{
p = _strchr(inform->argv[i], '=');
if (p)
set_alias(inform, inform->argv[i]);
else
print_alias(node_starts_with(inform->alias, inform->argv[i], '='));
}

return (0);
}
