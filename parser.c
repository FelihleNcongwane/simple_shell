#include "shell.h"

/**
 * Determines if a file is an executable command.
 * 
 * @param info: The info struct.
 * @param path: Path to the file.
 * @return: 1 if true, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
    struct stat st;

    (void)info;  // Ignore the info struct
    if (!path || stat(path, &st))
        return (0);

    if (st.st_mode & S_IFREG)  // Check if the file is a regular file
    {
        return (1);
    }
    return (0);
}

/**
 * Duplicates characters from a specified range.
 * 
 * @param pathstr: The PATH string.
 * @param start: Starting index.
 * @param stop: Stopping index.
 * @return: Pointer to a new buffer containing the duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];
    buf[k] = 0;
    return (buf);
}

/**
 * Finds the full path of a command in the PATH string.
 * 
 * @param info: The info struct.
 * @param pathstr: The PATH string.
 * @param cmd: The command to find.
 * @return: Full path of the command if found, or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return (NULL);
    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (is_cmd(info, cmd))
            return (cmd);  // Return the command as it is already a full path
    }
    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = dup_chars(pathstr, curr_pos, i);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (is_cmd(info, path))
                return (path);  // Return the full path if the command is found
            if (!pathstr[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return (NULL);  // Return NULL if the command is not found in the PATH
}
