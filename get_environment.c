#include "shell.h"

/**
* get_environ - Retrieves a copy of the string array from our environ.
* @inform: Structure with potential arguments. Maintains a constant function prototype.
* Return: Always 0.
*/
char **get_environ(inform_t *inform)
{
if (!inform->environ || inform->env_changed)
{
inform->environ = list_to_strings(inform->env);
inform->env_changed = 0;
}

return (inform->environ);
}

/**
* _unsetenv - Deletes an environment variable.
* @inform: Structure with potential arguments. Maintains a constant function prototype.
* @var: The string representing the environment variable property.
* Return: 1 on successful deletion, 0 otherwise.
*/
int _unsetenv(inform_t *inform, char *var)
{
list_t *node = inform->env;
size_t i = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
inform->env_changed = delete_node_at_index(&(inform->env), i);
i = 0;
node = inform->env;
continue;
}
node = node->next;
i++;
}
return (inform->env_changed);
}

/**
* _setenv - Initializes a new environment variable or modifies an existing one.
* @inform: Structure with potential arguments. Maintains a constant function prototype.
* @var: The string representing the environment variable property.
* @value: The string representing the environment variable value.
* Return: Always 0.
*/
int _setenv(inform_t *inform, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);
node = inform->env;
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
inform->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(inform->env), buf, 0);
free(buf);
inform->env_changed = 1;
return (0);
}
