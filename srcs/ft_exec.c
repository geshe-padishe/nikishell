#include "minishell.h"

char	*ft_check_bin_path(char *bin, char *paths)
{
	char	*bin_path;

	bin_path = malloc(ft_strlen(bin) + ft_ch_bef_col(paths) + 2);
	if (bin_path == NULL)
		return (3);
	bin_path[0] = '/';
	ft_strncpy(paths, bin_path + 1, ft_ch_bef_col(paths));
	ft_strcpy(bin, bin_path + 1 + ft_ch_bef_col(paths));
	if (access(bin_path, X_OK))
		return (bin_path);
	return (NULL);
}

int	ft_ch_bef_col(char *paths)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == ':')
			return (i - 1);
		i++;
	}
	return (i - 1);
}

int	ft_find_bin(char *bin, char *paths)
{
	char *bin_path;
	while (*paths)
	{
		bin_path = ft_check_bin_path(bin, paths);
		if (bin_path == 3)
			return (-1);
		if (bin_path)
		{
			execve(bin_path, "..", NULL);
			break;
		}
		paths += ft_ch_bef_col(paths);
	}
}
