#include "minishell.h"

int	ft_cd(char *str)
{
	if (!str)
		return (-1);
	if (!*str)
		chdir("/");
	else
		chdir(str);
	return (0);
}
