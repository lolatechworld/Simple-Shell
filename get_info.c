#include "shell.h"

/**
* clear_inform - Initializes the info_t struct.
* @inform: Address of the struct to be initialized.
*/
void clear_inform(inform_t *inform)
{
inform->arg = NULL;
inform->argv = NULL;
inform->path = NULL;
inform->argc = 0;
}

/**
* set_inform - Initializes the inform_t struct.
* @inform: Address of the struct.
* @av: Argument vector.
*/
void set_inform(inform_t *inform, char **av)
{
int i = 0;

inform->fname = av[0];
if (inform->arg)
{
inform->argv = strtow(inform->arg, " \t");
if (!inform->argv)
{

inform->argv = malloc(sizeof(char *) * 2);
if (inform->argv)
{
inform->argv[0] = _strdup(inform->arg);
inform->argv[1] = NULL;
}
}
for (i = 0; inform->argv && inform->argv[i]; i++)
                        ;
inform->argc = i;

replace_alias(inform);
replace_vars(inform);
}
}

/**
* free_inform - Frees fields within the inform_t struct.
* @inform: Address of the struct.
* @all: True if freeing all fields.
*/
void free_inform(inform_t *inform, int all)
{
ffree(inform->argv);
inform->argv = NULL;
inform->path = NULL;
if (all)
{
if (!inform->cmd_buf)
free(inform->arg);
if (inform->env)
free_list(&(inform->env));
if (inform->history)
free_list(&(inform->history));
if (inform->alias)
free_list(&(inform->alias));
ffree(inform->environ);
inform->environ = NULL;
bfree((void **)inform->cmd_buf);
if (inform->readfd > 2)
close(inform->readfd);
_putchar(BUF_FLUSH);
}
}
