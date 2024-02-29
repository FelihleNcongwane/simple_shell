#include "shell.h"

/**
 * isChainDelimiter - Checks whether the current character in the buffer represents a chain delimiter
 * @info: The parameter struct containing shell information
 * @buf: The character buffer to analyze
 * @p: Address of the current position in buf
 *
 * Returns: 1 if the character is a chain delimiter, 0 otherwise
 */
int isChainDelimiter(info_t *info, char *buf, size_t *p)
{
    size_t currentPosition = *p;

    if (buf[currentPosition] == '|' && buf[currentPosition + 1] == '|')
    {
        buf[currentPosition] = 0;
        currentPosition++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buf[currentPosition] == '&' && buf[currentPosition + 1] == '&')
    {
        buf[currentPosition] = 0;
        currentPosition++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buf[currentPosition] == ';') /* Found end of this command */
    {
        buf[currentPosition] = 0; /* Replace semicolon with null */
        info->cmd_buf_type = CMD_CHAIN;
    }
    else
        return (0);

    *p = currentPosition;
    return (1);
}

/**
 * checkChainStatus - Checks whether to continue chaining based on the last command's status
 * @info: The parameter struct containing shell information
 * @buf: The character buffer
 * @p: Address of the current position in buf
 * @i: Starting position in buf
 * @len: Length of buf
 *
 * Returns: Void
 */
void checkChainStatus(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t currentPosition = *p;

    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            currentPosition = len;
        }
    }
    if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            currentPosition = len;
        }
    }

    *p = currentPosition;
}

/**
 * replaceAlias - Replaces aliases in the given tokenized string with their corresponding values
 * @info: The parameter struct containing shell information
 *
 * Returns: 1 if aliases are replaced, 0 otherwise
 */
int replaceAliases(info_t *info)
{
    int i;
    list_t *node;
    char *aliasValue;

    for (i = 0; i < 10; i++)
    {
        node = nodeStartsWith(info->alias, info->argv[0], '=');
        if (!node)
            return (0);

        free(info->argv[0]);
        aliasValue = _strchr(node->str, '=') + 1;
        info->argv[0] = _strdup(aliasValue);

        if (!info->argv[0])
            return (0);
    }
    return (1);
}

/**
 * replaceVariables - Replaces variables in the given tokenized string with their corresponding values
 * @info: The parameter struct containing shell information
 *
 * Returns: 1 if variables are replaced, 0 otherwise
 */
int replaceVariables(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (!_strcmp(info->argv[i], "$?"))
        {
            replaceString(&(info->argv[i]), _strdup(convertNumber(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->argv[i], "$$"))
        {
            replaceString(&(info->argv[i]), _strdup(convertNumber(getpid(), 10, 0)));
            continue;
        }

        node = nodeStartsWith(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replaceString(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        replaceString(&info->argv[i], _strdup(""));
    }
    return (0);
}

/**
 * replaceString - Replaces the old string with the new one
 * @old: Address of the old string
 * @new: New string
 *
 * Returns: 1 if the replacement is successful, 0 otherwise
 */
int replaceString(char **old, char *new)
{
    free(*old);
    *old = new;
    return (1);
}
