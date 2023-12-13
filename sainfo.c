#include "fashell.h"

/**
 * clear_finfo - initializes finfo_a17 struct
 * @finfo: struct address
 */
void clear_finfo(finfo_a17 *finfo)
{
	(*finfo).arg = NULL;
	(*finfo).argv = NULL;
	(*finfo).path = NULL;
	(*finfo).argc = 0;
}

/**
 * set_finfo - initializes finfo_a17 struct
 * @finfo: struct address
 * @av: argument vector
 */
void set_finfo(finfo_a17 *finfo, char **av)
{
	int i = 0;

	(*finfo).fname = av[0];
	if ((*finfo).arg)
	{
		(*finfo).argv = strtow((*finfo).arg, " \t");
		if (!(*finfo).argv)
		{

			(*finfo).argv = malloc(sizeof(char *) * 2);
			if ((*finfo).argv)
			{
				(*finfo).argv[0] = _strdup((*finfo).arg);
				(*finfo).argv[1] = NULL;
			}
		}
		for (i = 0; (*finfo).argv && (*finfo).argv[i]; i++)
			;
		(*finfo).argc = i;

		replace_falias(finfo);
		replace_fvars(finfo);
	}
}

/**
 * free_finfo - frees finfo_a17 struct fields
 * @finfo: struct address
 * @all: true if freeing all fields
 */
void free_finfo(finfo_a17 *finfo, int all)
{
	ffree((*finfo).argv);
	(*finfo).argv = NULL;
	(*finfo).path = NULL;
	if (all)
	{
		if (!(*finfo).cmd_buf)
			free((*finfo).arg);
		if ((*finfo).env)
			free_flist(&((*finfo).env));
		if ((*finfo).history)
			free_flist(&((*finfo).history));
		if ((*finfo).falias)
			free_flist(&((*finfo).falias));
		ffree((*finfo).environ);
			(*finfo).environ = NULL;
		bfree((void **)(*finfo).cmd_buf);
		if ((*finfo).readfd > 2)
			close((*finfo).readfd);
		_putchar(FBUF_FLUSH);
	}
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FBUF_FLUSH);
}
