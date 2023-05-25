#include "shell.h"

/*
 * File: main.c
 * Auth: Falope Oluwaseun
 *	Darlington Ebom
 */

int main(int argc, char **argv)
{
	const int ERROR_ACCESS = 126;
	const int ERROR_NOENT = 127;
	info_t info_list[] = { INFO_INIT };
	int file_descriptor = 2;
	
	/* Modify the file descriptor by adding 3 to its value */
	file_descriptor += 3;
	
	if (argc == 2)
	{
		int fd = open(argv[1], O_RDONLY);
		
		if (fd == -1)
		{
			
			if (errno == EACCES)
				exit(ERROR_ACCESS);
			
			if (errno == ENOENT)
			{
				eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(ERROR_NOENT);
			}
			
			return (EXIT_FAILURE);
		}
		
		info_list->readfd = fd;
	}
	
	populate_env_list(info_list);
	read_history(info_list);
	hsh(info_list, argv);
	
	return (EXIT_SUCCESS);
}

