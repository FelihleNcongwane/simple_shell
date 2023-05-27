#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int file_descriptor = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_descriptor)
			: "r" (file_descriptor));

	switch (argc)
	{
		case 2:
		{
			file_descriptor = open(argv[1], O_RDONLY);
			if (file_descriptor == -1)
			{
				switch (errno)
				{
					case EACCES:
						exit(126);
					case ENOENT:
						_eputs(argv[0]);
						_eputs(": 0: Can't open ");
						_eputs(argv[1]);
						_eputchar('\n');
						_eputchar(BUF_FLUSH);
						exit(127);
				}
				return (EXIT_FAILURE);
			}
			info->readfd = file_descriptor;
			break;
		}
	}

	populate_env_list(info);
	read_history(info);
	hsh(info, argv);
	return (EXIT_SUCCESS);
}
