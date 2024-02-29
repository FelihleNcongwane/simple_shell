#include "shell.h"

/**
 * Gets the path of the history file.
 * 
 * @param info: The parameter struct.
 * @return: Allocated string containing the history file path.
 */
char *get_history_file(info_t *info)
{
    char *buf, *dir;

    // Get the HOME directory from the environment variables
    dir = _getenv(info, "HOME=");
    if (!dir)
        return (NULL);

    // Allocate memory for the history file path
    buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
    if (!buf)
        return (NULL);

    // Concatenate the HOME directory and history file name to form the full path
    buf[0] = 0;
    _strcpy(buf, dir);
    _strcat(buf, "/");
    _strcat(buf, HIST_FILE);

    return (buf);
}

/**
 * Writes the history to a file, creating the file if it doesn't exist.
 * 
 * @param info: The parameter struct.
 * @return: 1 on success, else -1.
 */
int write_history(info_t *info)
{
    ssize_t fd;
    char *filename = get_history_file(info);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    // Open or create the history file
    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (fd == -1)
        return (-1);

    // Write each history entry to the file
    for (node = info->history; node; node = node->next)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }

    // Flush the buffer and close the file
    _putfd(BUF_FLUSH, fd);
    close(fd);

    return (1);
}

/**
 * Reads the history from a file and updates the history linked list.
 * 
 * @param info: The parameter struct.
 * @return: The new histcount on success, 0 otherwise.
 */
int read_history(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = get_history_file(info);

    if (!filename)
        return (0);

    // Open the history file
    fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return (0);

    // Get the size of the history file
    if (!fstat(fd, &st))
        fsize = st.st_size;

    // If the file size is less than 2, return 0
    if (fsize < 2)
        return (0);

    // Allocate memory for reading the file
    buf = malloc(sizeof(char) * (fsize + 1));
    if (!buf)
        return (0);

    // Read the content of the history file
    rdlen = read(fd, buf, fsize);
    buf[fsize] = 0;
    if (rdlen <= 0)
        return (free(buf), 0);

    // Close the history file
    close(fd);

    // Parse the file content and build the history linked list
    for (i = 0; i < fsize; i++)
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            build_history_list(info, buf + last, linecount++);
            last = i + 1;
        }

    // If there's a partial line at the end, add it to the history
    if (last != i)
        build_history_list(info, buf + last, linecount++);

    free(buf);

    // Limit the history size and renumber the entries
    info->histcount = linecount;
    while (info->histcount-- >= HIST_MAX)
        delete_node_at_index(&(info->history), 0);

    renumber_history(info);

    return (info->histcount);
}

/**
 * Adds an entry to the history linked list.
 * 
 * @param info: The parameter struct.
 * @param buf: The buffer containing the history entry.
 * @param linecount: The history line count.
 * @return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    // If the history list is not empty, traverse to the end
    if (info->history)
        node = info->history;

    // Add the new entry to the end of the history list
    add_node_end(&node, buf, linecount);

    // Update the history list in the parameter struct
    if (!info->history)
        info->history = node;

    return (0);
}

/**
 * Renumbers the history linked list entries after changes.
 * 
 * @param info: The parameter struct.
 * @return: The new histcount.
 */
int renumber_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    // Traverse the history list and update the entry numbers
    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return (info->histcount = i);
}
