#include "minishell.h"

char	*ft_make_prompt(char *dir)
{
	char	*str;

	str = malloc(ft_strlen(dir) + 2);
	ft_strcpy(dir, str);
	ft_strcpy(" ", str + ft_strlen(dir));
	return (str);
}

char	*ft_get_dir(char *path)
{
	int	i;

	i = 0;
	if (!path)
		return (NULL);
	while (path[i])
		i++;
	i--;
	if (path[i] == '/' && path[i + 1] == '\0')
		return ("/");
	while (i > 0)
	{
		if (path[i] == '/')
			return (path + i + 1);
		i--;
	}
	return (NULL);
}

int	main(int ac, char **argv, char **envp)
{
	char		*line;
	char		*prompt;
	char		pwd[100];
	t_dynarray	darr;

	(void)ac;
	(void)argv;

	printf("pwd = %s\n", getcwd(pwd, 100));
	prompt = ft_make_prompt(ft_get_dir(getcwd(pwd, 100)));
	if (!prompt)
		return (printf("getcwd fail\n"), -1);
	init_dyn_env(envp, &darr);
	ft_export(&darr, "NIKI");
	//ft_dyn_env(&darr);
//	ft_unset(&darr, "NIKI");
//	ft_dyn_env(&darr);

	while (1)
	{
		line = readline(prompt);
		printf("line = %s\n", line);
		if (line && *line)
			add_history(line);
		else
			break;
	}
	free(line);
	return (0);
}
