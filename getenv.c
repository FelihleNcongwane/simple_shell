#include "shell.h"

/**
 * Returns a copy of the environment variables as a string array.
 * If the environment has changed, it updates the cached copy.
 * 
 * @param info: Structure containing potential arguments.
 * @return: String array copy of the environment variables.
 */
char **get_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * Removes an environment variable.
 * 
 * @param info: Structure containing potential arguments.
 * @param var: The environment variable to remove.
 * @return: 1 on success (delete), 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return (info->env_changed);
}

/**
 * Initializes or modifies an environment variable.
 * 
 * @param info: Structure containing potential arguments.
 * @param var: The environment variable to initialize or modify.
 * @param value: The value to set for the environment variable.
 * @return: 0 on success, 1 on failure.
 */
int _setenv(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return (1);

    buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return (1);
    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info->env;
    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return (0);
}
