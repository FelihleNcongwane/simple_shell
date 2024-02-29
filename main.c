#include "shell.h"

/**
 * The main entry point of the program.
 * 
 * @param ac: The argument count.
 * @param av: The argument vector.
 * @return: 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
    info_t info[] = { INFO_INIT };  // Initialize the info struct
    int fd = 2;  // Initialize the file descriptor

    // Inline assembly to increment the file descriptor value
    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd));

    if (ac == 2)
    {
        // Attempt to open the file specified in the command-line argument
        fd = open(av[1], O_RDONLY);
        if (fd == -1)
        {
            if (errno == EACCES)
                exit(126);  // Exit with status 126 if permission is denied
            if (errno == ENOENT)
            {
                // Print an error message and exit with status 127 if the file cannot be found
                _eputs(av[0]);
                _eputs(": 0: Can't open ");
                _eputs(av[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return (EXIT_FAILURE);  // Return EXIT_FAILURE on general failure
        }
        info->readfd = fd;  // Set the read file descriptor in the info struct
    }
    populate_env_list(info);  // Populate the environment list in the info struct
    read_history(info);  // Read the command history from the file
    hsh(info, av);  // Call the main shell loop function
    return (EXIT_SUCCESS);  // Return EXIT_SUCCESS on successful execution
}
