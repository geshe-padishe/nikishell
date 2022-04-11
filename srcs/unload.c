/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:26:23 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/08 18:32:27 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unload(t_split *split, t_token *token)
{
	int	i;

	i = 0;
	while (split->split[i] != NULL)
		free(split->split[i++]);
	free(split->split);
	free(split);
	free(token);
}
