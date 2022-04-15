/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_is.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:54:14 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/15 14:08:32 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sub_defined(t_token *token, int i_tok, int i_subtok)
{
	if (token[i_tok].subtoken[i_subtok].is_redirection_input == 1
		|| token[i_tok].subtoken[i_subtok].is_redirection_output == 1
		|| token[i_tok].subtoken[i_subtok].is_here_doc == 1
		|| token[i_tok].subtoken[i_subtok].is_append_output == 1
		|| token[i_tok].subtoken[i_subtok].is_cmd == 1
		|| token[i_tok].subtoken[i_subtok].is_arg == 1
		|| token[i_tok].subtoken[i_subtok].is_single_quoted == 1
		|| token[i_tok].subtoken[i_subtok].is_double_quoted == 1
		|| token[i_tok].subtoken[i_subtok].is_pipe == 1)
		return (1);
	else
		return (0);
}

int	is_sub_meta_char(t_token *token, int i_tok, int i_subtok)
{
	if (token[i_tok].subtoken[i_subtok].sub_elem[0] == '<'
		&& token[i_tok].subtoken[i_subtok].sub_elem[1] == 0)
		return (token[i_tok].subtoken[i_subtok].is_redirection_input = 1);
	else if (token[i_tok].subtoken[i_subtok].sub_elem[0] == '>'
		&& token[i_tok].subtoken[i_subtok].sub_elem[1] == 0)
		return (token[i_tok].subtoken[i_subtok].is_redirection_output = 1);
	else if (token[i_tok].subtoken[i_subtok].sub_elem[0] == '|'
		&& token[i_tok].subtoken[i_subtok].sub_elem[1] == 0)
		return (token[i_tok].subtoken[i_subtok].is_pipe = 1);
	else if (token[i_tok].subtoken[i_subtok].sub_elem[0] == '<'
		&& token[i_tok].subtoken[i_subtok].sub_elem[1] == '<'
		&& token[i_tok].subtoken[i_subtok].sub_elem[2] == 0)
		return (token[i_tok].subtoken[i_subtok].is_here_doc = 1);
	else if (token[i_tok].subtoken[i_subtok].sub_elem[0] == '>'
		&& token[i_tok].subtoken[i_subtok].sub_elem[1] == '>'
		&& token[i_tok].subtoken[i_subtok].sub_elem[2] == 0)
		return (token[i_tok].subtoken[i_subtok].is_append_output = 1);
	else
		return (0);
}

void	if_prev_tok_has_subtok(t_token *token, int i_tok, int i_subtok)
{
	if (is_sub_meta_char(token, i_tok - 1,
			token[i_tok - 1].nb_subtoken - 1) == 1)
	{
		if (token[i_tok - 1].subtoken[token[i_tok - 1].nb_subtoken - 1].is_append_output == 1
			|| token[i_tok - 1].subtoken[token[i_tok - 1].nb_subtoken - 1].is_redirection_output == 1)
			token[i_tok].subtoken[i_subtok].is_arg = 1;
		else
			token[i_tok].subtoken[i_subtok].is_cmd = 1;
	}
}

void	if_prev_tok_has_no_subtok(t_token *token, int i_tok, int i_subtok)
{
	if (is_meta_char(token, i_tok - 1) == 1)
	{
		if ((i_tok > 0 && token[i_tok - 1].is_append_output == 1)
			|| (i_tok > 0 && token[i_tok - 1].is_redirection_output == 1))
			token[i_tok].subtoken[i_subtok].is_arg = 1;
		else
			token[i_tok].subtoken[i_subtok].is_cmd = 1;
	}
	else
	{
		if (i_tok > 0 && token[i_tok - 1].is_cmd == 1)
			token[i_tok].subtoken[i_subtok].is_arg = 1;
	}
}

void	is_sub_command(t_token *token, int i_tok, int i_subtok)
{
	if (i_subtok == 0)
	{
		if (i_tok > 0 && token[i_tok - 1].nb_subtoken > 0)
			if_prev_tok_has_subtok(token, i_tok, i_subtok);
		else
			if_prev_tok_has_no_subtok(token, i_tok, i_subtok);
	}
	else
	{
		if (is_sub_meta_char(token, i_tok, i_subtok - 1) == 1)
		{
			if (token[i_tok].subtoken[i_subtok - 1].is_append_output == 1
				|| token[i_tok].subtoken[i_subtok - 1].is_redirection_output == 1)
				token[i_tok].subtoken[i_subtok].is_arg = 1;
			else
				token[i_tok].subtoken[i_subtok].is_cmd = 1;
		}
		else
			token[i_tok].subtoken[i_subtok].is_arg = 1;
	}
}

/*
 *			INVALIDE AU CINQUIEME POINT DE LA PARTIE OBLIGATOIRE DU SUJET
 void	is_env_variable(t_token *token, int i)
 {
 	int	i_str;
 
 	i_str = 0;
 	while (token[i].elem[i_str] != 0)
 	{
 		if (i_str > 0 && token[i].elem[i_str - 1] != '\\'
 			&& token[i].elem[i_str] == '$' && token[i].elem[i_str + 1])
 			token[i].is_env_variable = 1;
 		i_str++;
  	}
 }
 *
 */

void	is_sub_quoted(t_token *token, int i_tok, int i_subtok)
{
	if (token[i_tok].subtoken[i_subtok].sub_elem[0] == '\"')
	{
		if (is_quoted_good(token[i_tok].subtoken[i_subtok].sub_elem) == 0)
			token[i_tok].subtoken[i_subtok].is_double_quoted = 1;
		else
			token[i_tok].subtoken[i_subtok].is_wrong = 1;
	}
	else if (token[i_tok].subtoken[i_subtok].sub_elem[0] == '\'')
	{
		if (is_quoted_good(token[i_tok].subtoken[i_subtok].sub_elem) == 0)
			token[i_tok].subtoken[i_subtok].is_single_quoted = 1;
		else
			token[i_tok].subtoken[i_subtok].is_wrong = 1;
	}
}

void	which_sub_is(t_token *token, int i_tok, int i_subtok)
{
	if (is_sub_meta_char(token, i_tok, i_subtok) == 0)
	{
		if (token[i_tok].subtoken[i_subtok].sub_elem[0] == '$'
			&& token[i_tok].subtoken[i_subtok].sub_elem[1] != 0)
			token[i_tok].subtoken[i_subtok].is_env_variable = 1;
		else if (token[i_tok].subtoken[i_subtok].sub_elem[0] == '\"'
			|| token[i_tok].subtoken[i_subtok].sub_elem[0] == '\'')
			is_sub_quoted(token, i_tok, i_subtok);
		else
			is_sub_command(token, i_tok, i_subtok);
	}
}
