#include "shell.h"

/**
 * Copies a string from source to destination.
 * 
 * @param dest: The destination string.
 * @param src: The source string.
 * @return: A pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
{
    int i = 0;

    // Check for self-copy or null source
    if (dest == src || src == 0)
        return (dest);

    // Copy characters from source to destination
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;  // Null-terminate the destination string
    return (dest);
}

/**
 * Duplicates a given string.
 * 
 * @param str: The string to be duplicated.
 * @return: A pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
    int length = 0;
    char *ret;

    // Check for null input string
    if (str == NULL)
        return (NULL);

    // Calculate the length of the input string
    while (*str++)
        length++;

    // Allocate memory for the duplicated string
    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return (NULL);

    // Copy characters from input string to duplicated string
    for (length++; length--;)
        ret[length] = *--str;
    return (ret);
}

/**
 * Prints an input string to the standard output.
 * 
 * @param str: The string to be printed.
 * @return: Nothing.
 */
void _puts(char *str)
{
    int i = 0;

    // Check for null input string
    if (!str)
        return;

    // Print each character of the string
    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
}

/**
 * Writes the character 'c' to the standard output.
 * 
 * @param c: The character to print.
 * @return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    // Flush buffer or write character to buffer
    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}
