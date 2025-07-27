/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:12:10 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/27 11:10:06 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pipe_errors(t_token *token)
{
	if (token->type == PIPE)
	{
		if (!token->next || token->next->type == PIPE)
		{
			ft_putstr_fd("Syntax error: unexpected token `|'\n", 2);
			return (258);
		}
	}
	return (0);
}

int	check_redirection_errors(t_token *token)
{
	if (is_redirection(token))
	{
		if (!token->next || !is_word_token(token->next))
		{
			ft_putstr_fd("Syntax error: expected filename after redirection\n", 2);
			return (258);
		}
	}
	return (0);
}

static int	check_first_token(t_token *cur, t_data *data)
{
	if (cur->type == PIPE)
	{
		ft_putstr_fd("Syntax error: unexpected token `|'\n", 2);
		data->exit_status = 258;
		return (1);
	}
	return (0);
}

static int	check_last_token(t_token *cur, t_data *data)
{
	if (cur && cur->type == PIPE)
	{
		ft_putstr_fd("Syntax error: unexpected end after `|'\n", 2);
		data->exit_status = 258;
		return (1);
	}
	return (0);
}

int	check_syntax_errors(t_data *data)
{
	t_token	*cur;

	cur = data->token_list;
	if (!cur)
		return (0);
	if (check_first_token(cur, data))
		return (1);
	while (cur)
	{
		if (check_pipe_errors(cur) || check_redirection_errors(cur))
		{
			data->exit_status = 258;
			return (1);
		}
		cur = cur->next;
	}
	cur = data->token_list;
	while (cur && cur->next)
		cur = cur->next;
	if (check_last_token(cur, data))
		return (1);
	return (0);
}
