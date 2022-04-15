/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:00:34 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/15 13:46:43 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_is_null(t_split *split)
{
	perror("parse(): Error during split");
	free(split->split);
	free(split);
}

void	parse_split_ret_error(t_split *split, int i)
{
	perror("parse(): Error encountered, freeing and exiting");
	while (split->split[i] != NULL)
		free(split->split[i++]);
	free(split->split);
	free(split);
}


 
void	display_token_properties(t_token *token, int i)
{
	if (token[i].is_redirection_input == 1)
		printf("token %d is redirection input\n", token[i].id_token);
	if (token[i].is_redirection_output == 1)
		printf("token %d is redirection output\n", token[i].id_token);
	if (token[i].is_here_doc == 1)
		printf("token %d is here documents\n", token[i].id_token);
	if (token[i].is_append_output == 1)
		printf("token %d is append output\n", token[i].id_token);
	if (token[i].is_cmd == 1)
		printf("token %d is command\n", token[i].id_token);
	if (token[i].is_arg == 1)
		printf("token %d is argument\n", token[i].id_token);
	if (token[i].is_single_quoted == 1)
		printf("token %d is single quoted\n", token[i].id_token);
	if (token[i].is_double_quoted == 1)
		printf("token %d is double quoted TODO isolate quoted env variable\n",
			token[i].id_token);
	if (token[i].is_pipe == 1)
		printf("token %d is pipe\n", token[i].id_token);
	if (token[i].is_env_variable == 1)
		printf("token %d is env variable\n", token[i].id_token);
}

void	display_sub_token_properties(t_token *token, int i_tok, int i_subtok)
{
	if (token[i_tok].subtoken[i_subtok].is_redirection_input == 1)
		printf("subtoken %d is redirection input\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_redirection_output == 1)
		printf("subtoken %d is redirection output\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_here_doc == 1)
		printf("subtoken %d is here documents\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_append_output == 1)
		printf("subtoken %d is append output\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_cmd == 1)
		printf("subtoken %d is command\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_arg == 1)
		printf("subtoken %d is argument\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_single_quoted == 1)
		printf("subtoken %d is single quoted\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_double_quoted == 1)
		printf("token %d is double quoted TODO isolate quoted env variable\n",
			i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_pipe == 1)
		printf("subtoken %d is pipe\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_env_variable == 1)
		printf("subtoken %d is env variable\n", i_subtok);
}

int	is_there_wrong_token(t_token *token)
{
	int	i;

	i = 0;
	while (token[i].elem != NULL)
	{
		if (token[i].is_wrong == 1)
			return (-1);
		i++;
	}
	return (0);
}

void	display_subtoken(t_token *token, int i_tok)
{
	int	i_subtok;

	i_subtok = 0;
	while (i_subtok < token[i_tok].nb_subtoken)
	{
		printf("token[%d]->subtoken[%d] = %s\n", i_tok, i_subtok,
				token[i_tok].subtoken[i_subtok].sub_elem);
		which_sub_is(token, i_tok, i_subtok);
		display_sub_token_properties(token, i_tok, i_subtok);
		i_subtok++;
	}
}

void	process_split(t_split *split, int i)
{
	t_token	*token;
	int		err;

	token = ft_token(split);
	if (token == NULL)
	{
		perror("process_split(): token scuffed");
		return ;
	}
	while (token[i].elem != NULL)
	{
		which_is(token, i);
		err = is_there_wrong_token(token);
		if (err != 0)
		{
			perror("process_split(): syntax error");
			unload(split, token);
			return ;
		}
		printf("token[%d] = %s\n", token[i].id_token, token[i].elem);
		display_token_properties(token, i);
		if (token[i].is_arg == 1 && seek_meta_char(token, i) != 0)
		{
			subtokenize(token, i);
			display_subtoken(token, i);
		}
		i++;
	}
	unload(split, token);
}

void	parse(char *line_buffer)
{
	t_split	*split;
	int		i;

	i = 0;
	split = (t_split *)malloc(sizeof(t_split));
	if (split == NULL)
	{
		perror("parse(): Error allocating split structure");
		return ;
	}
	ft_memset((void *)split, 0, sizeof(t_split));
	count_quotes(line_buffer, split);
	if (redo_split(line_buffer, split) == -1)
		parse_split_ret_error(split, i);
	else
	{
		if (split->split[i] == NULL && line_buffer == NULL)
			split_is_null(split);
		else
			process_split(split, i);
	}
}
