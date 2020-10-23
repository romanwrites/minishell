
#include "minishell.h"

void 		reset_newlines(char *str)
{
	int 	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = ' ';
		}
		i++;
	}
}