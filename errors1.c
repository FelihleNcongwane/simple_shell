#include "shell.h"

/**
 * _erratoi - changess a str to an int
 * @s: str to be changed
 * Return: 0
 */
int _erratoi(char *s)
{
	int z = 0;
	unsigned long int results = 0;

	if (*s == '+')
		s++;
	for (z = 0;  s[z] != '\0'; z++)
	{
		if (s[z] >= '0' && s[z] <= '9')
		{
			results *= 10;
			results += (s[z] - '0');
			if (results > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (results);
}

/**
 * print_error - Displaying error message
 * @info: param
 * Return: 0 
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - funct displaying a dec
 * @input: raw inp
 * @fd: fd to write to
 *
 * Return: # of chars displayed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int z, counts = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counts++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (z = 1000000000; z > 1; z /= 10)
	{
		if (_abs_ / z)
		{
			__putchar('0' + current / z);
			counts++;
		}
		current %= z;
	}
	__putchar('0' + current);
	counts++;

	return (counts);
}

/**
 * convert_number - function changer
 * @num: #
 * @base: _
 * @flags: arg flg
 *
 * Return: <str>
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sin = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sin = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sin)
		*--ptr = sin;
	return (ptr);
}

/**
 * remove_comments - fuct replace 1st instance
 * @buf: location of str to modify
 * Return: 0 All the time
 */
void remove_comments(char *buf)
{
	int z;

	for (z = 0; buf[z] != '\0'; z++)
		if (buf[z] == '#' && (!z || buf[z - 1] == ' '))
		{
			buf[z] = '\0';
			break;
		}
}
