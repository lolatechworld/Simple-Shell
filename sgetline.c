#include "fashell.h"

/**
 * input_buf - buffers chained commands
 * @finfo: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(finfo_a17 *finfo, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)(*finfo).cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

#if FUSE_GET
			r = getline(buf, &len_p, stdin);
#else
			r = _fgetline(finfo, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			(*finfo).linecount_flag = 1;
			remove_comments(*buf);
			build_fhistory_list(finfo, *buf, (*finfo).histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				(*finfo).cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @finfo: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(finfo_a17 *finfo)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &((*finfo).arg), *f;

	_putchar(FBUF_FLUSH);
	r = input_buf(finfo, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		f = buf + i; /* get pointer for return */

		check_fchain(finfo, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (fchain(finfo, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			(*finfo).cmd_buf_type = FMD_N;
		}

		*buf_p = f; /* pass back pointer to current command position */
		return (_strlen(f)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _fgetline() */
	return (r); /* return length of buffer from _fgetline() */
}

/**
 * read_buf - reads a buffer
 * @finfo: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(finfo_a17 *finfo, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read((*finfo).readfd, buf, FBUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _fgetline - gets the next line of input from STDIN
 * @finfo: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _fgetline(finfo_a17 *finfo, char **ptr, size_t *length)
{
	static char buf[FBUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *f = NULL, *new_p = NULL, *c;

	f = *ptr;
	if (f && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(finfo, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(f, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (f ? free(f), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	f = new_p;

	if (length)
		*length = s;
	*ptr = f;
	return (s);
}
