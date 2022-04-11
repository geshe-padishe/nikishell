/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:59:31 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/11 15:40:29 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	convert_env_var(t_token *token, int i)
{
	char	*convert;

	convert = ft_strdup(getenv(token[i].elem));
	if (convert == NULL)
	{
		perror("convert_env_var(): error allocating convert string");
		return ;
	}
	printf("convert is %s\n", convert);
	free(token[i].elem);
	token[i].elem = ft_strdup(convert);
	free(convert);
}
