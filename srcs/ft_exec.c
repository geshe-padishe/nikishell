#include "minishell.h"

int	ft_check_bin_path(char *bin, char *paths)
{
	char	*bin_path;

	bin_path = malloc(ft_strlen(bin) + ft_ch_bef_col(paths) + 1);
	ft_strncpy(paths, bin_path, ft_ch_bef_col(paths));
	ft_strcpy(bin, bin_path + ft_ch_bef_col(paths));
	if (access(bin_path, X_OK);
}

int	ft_ch_bef_col(char *paths)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == ':')
			return (i);
		i++;
	}
	return (0);
}
