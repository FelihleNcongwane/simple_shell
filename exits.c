#include "shell.h"

/**
 * Copies a string up to a specified number of characters.
 * 
 * @param dest: The destination string to be copied to.
 * @param src: The source string.
 * @param n: The number of characters to be copied.
 * @return: The concatenated string.
 */
char *_strncpy(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    i = 0;
    while (src[i] != '\0' && i < n - 1)
    {
        dest[i] = src[i];
        i++;
    }
    if (i < n)
    {
        j = i;
        while (j < n)
        {
            dest[j] = '\0';
            j++;
        }
    }
    return (s);
}

/**
 * Concatenates two strings up to a specified number of bytes.
 * 
 * @param dest: The first string.
 * @param src: The second string.
 * @param n: The number of bytes to be maximally used.
 * @return: The concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    i = 0;
    j = 0;
    while (dest[i] != '\0')
        i++;
    while (src[j] != '\0' && j < n)
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    if (j < n)
        dest[i] = '\0';
    return (s);
}

/**
 * Locates a character in a string.
 * 
 * @param s: The string to be parsed.
 * @param c: The character to look for.
 * @return: A pointer to the memory area in the string.
 */
char *_strchr(char *s, char c)
{
    do
    {
        if (*s == c)
            return (s);
    } while (*s++ != '\0');

    return (NULL);
}

