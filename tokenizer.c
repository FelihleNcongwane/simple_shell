#include "shell.h"

/**
 * Splits a given string into words based on a specified delimiter string.
 * Repeated delimiters are ignored.
 * 
 * @param str: The input string to be split.
 * @param d: The delimiter string.
 * @return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *str, char *d)
{
    int i, j, k, m, numwords = 0;
    char **s;

    // Check for null or empty input string
    if (str == NULL || str[0] == 0)
        return (NULL);

    // Set default delimiter to space if not provided
    if (!d)
        d = " ";

    // Count the number of words in the input string
    for (i = 0; str[i] != '\0'; i++)
        if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
            numwords++;

    // Return NULL if no words found
    if (numwords == 0)
        return (NULL);

    // Allocate memory for array of strings
    s = malloc((1 + numwords) * sizeof(char *));
    if (!s)
        return (NULL);

    // Populate the array of strings with individual words
    for (i = 0, j = 0; j < numwords; j++)
    {
        while (is_delim(str[i], d))
            i++;
        k = 0;
        while (!is_delim(str[i + k], d) && str[i + k])
            k++;

        // Allocate memory for each word
        s[j] = malloc((k + 1) * sizeof(char));
        if (!s[j])
        {
            // Free previously allocated memory and return NULL on failure
            for (k = 0; k < j; k++)
                free(s[k]);
            free(s);
            return (NULL);
        }

        // Copy the characters of the word into the allocated memory
        for (m = 0; m < k; m++)
            s[j][m] = str[i++];
        s[j][m] = 0;  // Null-terminate the word
    }

    s[j] = NULL;  // Null-terminate the array of strings
    return (s);
}

/**
 * Splits a given string into words based on a specified delimiter character.
 * 
 * @param str: The input string to be split.
 * @param d: The delimiter character.
 * @return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow2(char *str, char d)
{
    int i, j, k, m, numwords = 0;
    char **s;

    // Check for null or empty input string
    if (str == NULL || str[0] == 0)
        return (NULL);

    // Count the number of words in the input string
    for (i = 0; str[i] != '\0'; i++)
        if ((str[i] != d && str[i + 1] == d) ||
            (str[i] != d && !str[i + 1]) || str[i + 1] == d)
            numwords++;

    // Return NULL if no words found
    if (numwords == 0)
        return (NULL);

    // Allocate memory for array of strings
    s = malloc((1 + numwords) * sizeof(char *));
    if (!s)
        return (NULL);

    // Populate the array of strings with individual words
    for (i = 0, j = 0; j < numwords; j++)
    {
        while (str[i] == d && str[i] != d)
            i++;
        k = 0;
        while (str[i + k] != d && str[i + k] && str[i + k] != d)
            k++;

        // Allocate memory for each word
        s[j] = malloc((k + 1) * sizeof(char));
        if (!s[j])
        {
            // Free previously allocated memory and return NULL on failure
            for (k = 0; k < j; k++)
                free(s[k]);
            free(s);
            return (NULL);
        }

        // Copy the characters of the word into the allocated memory
        for (m = 0; m < k; m++)
            s[j][m] = str[i++];
        s[j][m] = 0;  // Null-terminate the word
    }

    s[j] = NULL;  // Null-terminate the array of strings
    return (s);
}
