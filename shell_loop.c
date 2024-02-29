#include "shell.h"

/**
 * The main function for the shell, responsible for the continuous execution of commands.
 * 
 * @param info: The information structure that stores parameters and return values.
 * @param av: The argument vector from the main function.
 * @return: 0 on success, 1 on error, or error code.
 */
int hsh(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    while (r != -1 && builtin_ret != -2)
    {
        clear_info(info);
        if (interactive(info))
            _puts("$ ");  // Display the shell prompt
        _eputchar(BUF_FLUSH);
        r = get_input(info);  // Get user input
        if (r != -1)
        {
            set_info(info, av);  // Set up information for command execution
            builtin_ret = find_builtin(info);  // Check if the command is a built-in
            if (builtin_ret == -1)
                find_cmd(info);  // If not built-in, find and execute the command
        }
        else if (interactive(info))
            _putchar('\n');  // Print a new line for better user experience
        free_info(info, 0);
    }
    write_history(info);  // Save command history
    free_info(info, 1);
    if (!interactive(info) && info->status)
        exit(info->status);  // Exit with the status of the last command
    if (builtin_ret == -2)
    {
        if (info->err_num == -1)
            exit(info->status);  // Exit with the status of the last command if no error
        exit(info->err_num);  // Exit with the specified error code
    }
    return (builtin_ret);
}

/**
 * Finds a built-in command and executes it if found.
 * 
 * @param info: The information structure that stores parameters and return values.
 * @return: -1 if built-in not found, 0 if built-in executed successfully,
 *          1 if built-in found but not successful, -2 if built-in signals exit().
 */
int find_builtin(info_t *info)
{
    int i, built_in_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].type; i++)
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    return (built_in_ret);
}

/**
 * Finds and executes a command in the PATH.
 * 
 * @param info: The information structure that stores parameters and return values.
 * @return: void
 */
void find_cmd(info_t *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
        if (!is_delim(info->arg[i], " \t\n"))
            k++;
    if (!k)
        return;

    path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        fork_cmd(info);
    }
    else
    {
        if ((interactive(info) || _getenv(info, "PATH=")
            || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
            fork_cmd(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

/**
 * Forks an exec thread to run a command.
 * 
 * @param info: The information structure that stores parameters and return values.
 * @return: void
 */
void fork_cmd(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");  // Display an error message
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_environ(info)) == -1)
        {
            free_info(info, 1);
            if (errno == EACCES)
                exit(126);  // Exit with a specific status for permission denied
            exit(1);  // Exit with status 1 for general execution error
        }
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}
