/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_meta_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 12:41:39 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/13 15:01:40 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	which_meta_char(t_token *token, int i, int i_str)
{
	if (token[i].elem[i_str] == '<' && token[i].elem[i_str + 1] != '<')
		return (1);
	else if (token[i].elem[i_str] == '>' && token[i].elem[i_str + 1] != '>')
		return (2);
	else if (token[i].elem[i_str] == '|')
		return (3);
	else if (token[i].elem[i_str] == '<' && token[i].elem[i_str + 1] == '<')
		return (4);
	else if (token[i].elem[i_str] == '>' && token[i].elem[i_str + 1] == '>')
		return (5);
	else
		return (0);
} 

void	display_which_meta(int ret)
{
	if (ret == 1)
		printf("seek_meta: ret value is %d -> redirection input meta char found\n", ret);
	else if (ret == 2)
		printf("seek_meta: ret value is %d -> redirection output meta char found\n", ret);
	else if (ret == 3)
		printf("seek_meta: ret value is %d -> pipe meta char found\n", ret);
	else if (ret == 4)
		printf("seek_meta: ret value is %d -> here_doc meta char found\n", ret);
	else if (ret == 5)
		printf("seek_meta: ret value is %d -> append output meta char found\n", ret);
}

int	seek_meta_char(t_token *token, int i)
{
	int	i_str;
	int	ret;

	i_str = 0;
	ret = 0;
	while (token[i].elem[i_str])
	{
		ret = which_meta_char(token, i, i_str);
		if (ret == 4 || ret == 5)
			i_str = i_str + 2;
		if (ret != 0)
			return (ret);
		i_str++;
	}
	return (0);
}
