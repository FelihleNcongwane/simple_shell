#include "shell.h"

/**
 **_strncpy - copies a str
 *@dest: destination str
 *@src: str
 *@n: # chars 
 *Return: + str
 */
char *_strncpy(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (y < n)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenating 2strs
 *@dest: 1st str
 *@src: 2nd str
 *@n: nytes used in max
 *Return: the str
 */
char *_strncat(char *dest, char *src, int n)
{
	int y, z;
	char *s = dest;

	y = 0;
	z = 0;
	while (dest[y] != '\0')
		y++;
	while (src[z] != '\0' && j < n)
	{
		dest[y] = src[z];
		y++;
		z++;
	}
	if (z < n)
		dest[y] = '\0';
	return (s);
}

/**
 **_strchr - loc char in str
 *@s: str
 *@c: char to search
 *Return: pointer
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
