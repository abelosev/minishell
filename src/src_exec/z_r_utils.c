#include "../../inc/exec.h"

int	open_file(char *file, int std_no)
{
	int	opnd_fd;

	if (std_no == 0)
		opnd_fd = open(file, O_RDONLY, 0644);
	if (std_no == 1)
		opnd_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (opnd_fd == -1)
		exit(0);
	return (opnd_fd);
}
