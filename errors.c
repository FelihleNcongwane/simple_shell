#include "shell.h"

/**
 * _eputs - displays input string
 * @str: String to be displayed
 *
 * Return: Null
 */
void _eputs(char *str)
{
	int z = 0;

	if (!str)
		return;
	while (str[z] != '\0')
	{
		_eputchar(str[z]);
		z++;
	}
}

/**
 * _eputchar - writing Char c
 * @c: Character to be displayed
 *
 * Return: 1 if successful
 */
int _eputchar(char c)
{
	static int z;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(2, buf, z);
		z = 0;
	}
	if (c != BUF_FLUSH)
		buf[z++] = c;
	return (1);
}

/**
 * _putfd - Write Char c
 * @c: Characterto be displayed
 * @fd: fd to write to
 *
 * Return: 1 when successful
 */
int _putfd(char c, int fd)
{
	static int z;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(fd, buf, z);
		z = 0;
	}
	if (c != BUF_FLUSH)
		buf[z++] = c;
	return (1);
}

/**
 * _putsfd - input string printed
 * @str: String to display
 * @fd: fd to write to
 *
 * Return: # of character
 */
int _putsfd(char *str, int fd)
{
	int z = 0;

	if (!str)
		return (0);
	while (*str)
	{
		z += _putfd(*str++, fd);
	}
	return (z);
}
