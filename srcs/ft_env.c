#include "minishell.h"

int	init_dyn_env(char **envp, t_dynarray *darr)
{
	int		i;
	char	*str;

	i = 0;
	while (envp[i])
		i++;
	init_dynarray(darr, i, sizeof(char*)); // A SECURE
	i = 0;
	while (envp[i])
	{
		str = malloc(ft_strlen(envp[i]) + 1);
		ft_strcpy(envp[i], str);
		push_dynarray(darr, &str, 1, 0);
		i++;
	}
	return (0);
}

int	ft_getenv_index(char **envp, uint64_t len, char *str)
{
	uint64_t	i;
	int			cmp;

	i = 0;
	while (i < len)
	{
		cmp = ft_envcmp(envp[i], str);
		if (cmp == -1)
			i++;
		else if (cmp == -2)
			return (-2);
		else
			return (i);
	}
	return (-1);
}

int	ft_export(t_dynarray *darr, char *str)
{
	int	index;
	char	**envp;
	char	*envpi;

	envp = darr->list;
	index = ft_getenv_index(envp, darr->nb_cells, str);
	printf("index = %d\n", index);
	if (index >= 0)
	{
		envpi = malloc(ft_strlen(str) + 1);
		ft_strcpy(str, envpi);
		free(envp[index]);
		envp[index] = envpi;
	}
	else if (index == -1)
	{
		envpi = malloc(ft_strlen(str) + 1);
		ft_strcpy(str, envpi);
		push_dynarray(darr, &envpi, 1, 0);
	}
	return (0);
}

int	ft_unset(t_dynarray *darr, char *str)
{
	int	index;
	char	**envp;

	envp = darr->list;
	index = ft_getenv_index(envp, darr->nb_cells, str);
	if (index != -1)
	{
		free(envp[index]);
		dynarray_extract(darr, index, 1);
	}
	else
		return (-1);
	return (0);
}


