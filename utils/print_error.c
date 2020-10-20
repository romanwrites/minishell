#include "minishell.h"

void		print_error(char *str)
{
	ft_putendl_fd(str, PRINT_ERROR_FD);
}