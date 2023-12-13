#include "shell.h"

/**
* _ourenv - Prints the current environment.
* @inform: Structure with potential arguments.
* Returns: Always 0.
*/

int _ourenv(inform_t *inform)
{
print_list_str(inform->env);
return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @inform: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(inform_t *inform, const char *name)
{
list_t *node = inform->env;
char *p;

while (node)
{
p = starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
* _oursetenv - Initializes a new environment variable or modifies an existing one.
* @inform: Structure with potential arguments. Maintains a constant function prototype.
* Returns: Always 0.
*/

int _oursetenv(inform_t *inform)
{
if (inform->argc != 3)
{
_eputs("Incorrect number of arguments\n");
return (1);
}
if (_setenv(inform, inform->argv[1], inform->argv[2]))
return (0);
return (1);
}

/**
* _ourunsetenv - Deletes an environment variable.
* @inform: Structure with potential arguments. Maintains a constant function prototype.
* Returns: Always 0.
*/

int _ourunsetenv(inform_t *inform)
{
int i;

if (inform->argc == 1)
{
_eputs("Too few arguements.\n");
return (1);
}
for (i = 1; i <= inform->argc; i++)
_unsetenv(inform, inform->argv[i]);

return (0);
}

/**
* populate_env_list - Fills the environment linked list.
* @inform: Structure with potential arguments. Maintains a constant function prototype.
* Returns: Always 0.
*/
int populate_env_list(inform_t *inform)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
inform->env = node;
return (0);
}
