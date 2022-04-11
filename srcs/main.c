/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:15:54 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/12 01:54:35 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_dynarray	darr;
	char	*line_buffer;

	if (ac != 1)
		return (-1);
	init_dyn_env(envp, &darr); //Copier le envp dans notre env darr.list
	ft_dyn_env(&darr); //Afficher notre env
	ft_export(&darr, "NIKI=BOSS"); //Ajouter dans notre env
	ft_unset(&darr, "NIKI"); //Enlever de notre env
	while (1)
	{
		line_buffer = readline("$>");
		if (line_buffer == NULL)
			return (0);
		parse(line_buffer);
		free(line_buffer);
	}
	printf("arg[%d] = %s\n", 0, av[0]);
	return (0);
}
